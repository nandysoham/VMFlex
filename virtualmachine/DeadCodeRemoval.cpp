#include "DeadCodeRemoval.h"
#include "Structure.h"
using namespace std;

vector <string> processWords(string line){
    vector <string> words;
    string word;
    for(int i =0; i < line.length(); i++){
        if(line[i] == ' '){
            if(word.length() > 0)
                words.push_back(word);

            word.clear();
        }
        else{
            word.push_back(line[i]);
        }
    }
    if(word.size() > 0)
        words.push_back(word);
    
    return words;
}


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


void createDeadCodeOptimize(vector <string> &inputStream){
    vector <string> optimizedStream;
    for(auto bb : basicBlockCollection){
        if(bb.isRequired){
            for(int line = bb.startLine ; line <= bb.endLine; line++){
                optimizedStream.push_back(inputStream[line]);
            }
        }
    }

    ofstream optimizedFile("optimizedcode.tac");
    if (!optimizedFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    for (const string& line : optimizedStream) {
        optimizedFile << line << endl;
    }
    optimizedFile.close();
}

/**
 * Builds the Basic blocks and the adjaceny list for the basic blocks
*/
void getBasicBlocks(vector <string> &inputStream){

   
    struct BasicBlock _block = BasicBlock();
    for(int i = 0; i < inputStream.size() ; i++){
        if(i == 0){
            // start the _block
            _block.startLine = 0;
        }

        string line = inputStream[i];
        vector <string> words = processWords(line);

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


void deadCodeRemoval(vector <string> &inputStream){
    getBasicBlocks(inputStream);
    blockReachability();
    createDeadCodeOptimize(inputStream);
    printBasicBlocks();
};
