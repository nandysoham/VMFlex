#include "DeadCodeRemoval.h"
#include "Structure.h"
using namespace std;



/**
 * @brief Printing Basic Blocks
 * 
 */
void printBasicBlocks(){

    for(auto [x,y] : labelsToColMap){
        cout<<x<<" --> "<<y<<endl;
    }

    for(int i = 0; i < basicBlockCollection.size(); i++){
        cout<<"Block #"<<i<<endl;
        cout<<"Starts : "<<basicBlockCollection[i].startLine<<endl;
        cout<<"Ends : "<<basicBlockCollection[i].endLine<<endl;
        cout<<"gotoLabel : "<<basicBlockCollection[i].gotoLabel<<endl;
        cout<<"isRequired : "<<basicBlockCollection[i].isRequired<<endl; 
        cout<<"Successor Blocks : ";
        for(auto j : basicBlockCollection[i].successorBlock)
            cout<<j<<" ";

        cout<<endl;
        cout<<"-------------------------------------------------------------\n\n";

    }
}

/**
 * @brief Graph function to calculate reachability
 * 
 */
void blockReachability(){
    int n = basicBlockCollection.size();
    vector <int> visited(n, false);
    visited[0] = true;
    queue <int> bfsQueue;
    bfsQueue.push(0);
    while(bfsQueue.size() > 0){
        int currElement = bfsQueue.front();
        bfsQueue.pop();
        basicBlockCollection[currElement].isRequired = true;
        for(int i : basicBlockCollection[currElement].successorBlock){
            if(!visited[i]){
                visited[i] = true;
                bfsQueue.push(i);
            }
        }
    }
}


/**
 * @brief Create a Dead Code Optimize object
 * 
 * @param inputStream 
 * @param name 
 */
void createDeadCodeOptimize(vector <string> &inputStream, string name){
    vector <string> optimizedStream;
    for(auto bb : basicBlockCollection){
        if(bb.isRequired){
            for(int line = bb.startLine ; line <= bb.endLine; line++){
                optimizedStream.push_back(inputStream[line]);
            }
        }
    }

    // write the optimized code
    functionDetailsMap[name].optCode = optimizedStream;

    


    // ofstream optimizedFile("optimizedcode.tac");
    // if (!optimizedFile.is_open()) {
    //     cout << "Error opening file." << endl;
    //     return;
    // }

    // for (const string& line : optimizedStream) {
    //     optimizedFile << line << endl;
    // }
    // optimizedFile.close();
}

/**
 * Builds the Basic blocks and the adjaceny list for the basic blocks
*/
void getBasicBlocks(vector <string> &inputStream, string name){

   
    struct BasicBlock _block = BasicBlock();
    for(int i = 0; i < inputStream.size() ; i++){
        if(i == 0){
            // start the _block
            _block.startLine = 0;
        }

        string line = inputStream[i];
        vector <string> words = processWords(line);

        // check which of the functions are begin called from here
        if(find(words.begin(), words.end(), "FunctionCall") != words.end()){
            int idx = find(words.begin(), words.end(), "FunctionCall") - words.begin();
            string calleeFunction = words[idx + 1];
            functionCalleeMap[calleeFunction].push_back(name);
        }



        if(find(words.begin(), words.end(), "goto") != words.end()){
            
            int idx = find(words.begin(), words.end(), "goto") - words.begin();
            _block.endLine = i;

            string nextLabel = words[idx + 1];
            _block.gotoLabel = nextLabel;

            if(find(words.begin(), words.end(), "if") != words.end()){
                // there is a if condition
                _block.successorBlock.push_back(basicBlockCollection.size() + 1);       // Next block will be successor
            }

            basicBlockCollection.push_back(_block);
            
            // always intialize the next block no matter what
            _block = BasicBlock();
            _block.startLine = i + 1;
            
        }
       
        else if(find(words.begin(), words.end(), "call") != words.end()){
            int idx = find(words.begin(), words.end(), "call") - words.begin();
            _block.endLine = i;

            string nextLabel = words[idx + 1];
            _block.gotoLabel = nextLabel;
            _block.successorBlock.push_back(basicBlockCollection.size() + 1);

            basicBlockCollection.push_back(_block);

            // always intialize the next block no matter what
            _block = BasicBlock();
            _block.startLine = i + 1;
        }
        else if(words.size() > 0 && words[0] == "Return"){
            _block.endLine= i;
            
            // no connections.. Just end it here
            basicBlockCollection.push_back(_block);
            _block = BasicBlock();
            _block.startLine = i + 1;
        }
        
        else{
            // label in the line --> this is a leader
            for(auto word : words){
                if(word.substr(0,5) == "label"){
                    if(_block.startLine != i){
                        // close the previous block if not closed
                        _block.endLine = i - 1;
                        _block.successorBlock.push_back(basicBlockCollection.size() + 1);
                        basicBlockCollection.push_back(_block);
                        _block = BasicBlock();
                    }
                    _block.startLine = i;


                    int idx = find(words.begin(), words.end(), word) - words.end();
                    string thisLabel = words[idx + 1];
                    if(thisLabel.back() == ':')
                        thisLabel = thisLabel.substr(0, thisLabel.length() - 1);
                    labelsToColMap[thisLabel] = basicBlockCollection.size();    


                    break;

                }
            }
        }

        
    }

    // closing the last block
    if(_block.startLine != inputStream.size()){
        _block.endLine = inputStream.size() - 1;
        basicBlockCollection.push_back(_block);
    }

    _block = BasicBlock();



    // now put in the dependencies
    for(int i =0; i < basicBlockCollection.size(); i++){
        if(basicBlockCollection[i].gotoLabel.size() > 0){
            string nextLabel =  basicBlockCollection[i].gotoLabel;
            basicBlockCollection[i].successorBlock.push_back(labelsToColMap[nextLabel]);
        }
    }

    

}
/**
 * @brief Shows caller and callee
 * 
 */
void showCallerCalllee(){
    for(auto [calledFunction, callerFunctionVec] : functionCalleeMap ){
        cout<<calledFunction <<" is called by ";
        for(auto i : callerFunctionVec)
            cout<<i<<", ";
        cout<<endl;
    }
}

/**
 * @brief Removes useless functions
 * 
 */
void removeUnessentialFunction(){
    vector <string> removeFunctionsVec;
    for(auto [_functionName, _functionDetails] : functionDetailsMap){
        if(_functionName == "main") continue;
        bool removeFunction = true;
        for(auto calleeFunction : functionCalleeMap[_functionName]){
            if(calleeFunction != _functionName){
                removeFunction = false;
                break;
            }
        }

        if(removeFunction){
            removeFunctionsVec.push_back(_functionName);
        }
    }
    cout<<"Functions that need to be removed "<<endl;
    for(auto i : removeFunctionsVec)    
        cout<<i<<" ";

    cout<<endl;

    for(auto i : removeFunctionsVec){
        functionDetailsMap.erase(i);
        functionCalleeMap.erase(i);
    }
}

/**
 * @brief Printing function details
 * 
 */
void printFunctionDetails(){
    ofstream file("OptimizedCode.txt");
    for(auto [_functionName, _functionDetails] : functionDetailsMap){
        file<<_functionName<<" : "<<endl;
        file<<"Org code"<<endl<<endl;
        for(auto i : _functionDetails.code)
            file<<i<<endl;

        file<<"Opt code"<<endl<<endl<<endl;
        for(auto i : _functionDetails.optCode)
            file<<i<<endl;
    }
    file.close();
}



// will not work for function overloading
void deadCodeRemoval(vector <string> &inputStream, string name){
    basicBlockCollection.clear();
    getBasicBlocks(inputStream, name);
    blockReachability();
    createDeadCodeOptimize(inputStream, name);
    printBasicBlocks();
};
