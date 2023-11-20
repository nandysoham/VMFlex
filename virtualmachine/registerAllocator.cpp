#include <iostream>
#include "Structure.h"
#include "registerAllocator.h"
#include "memHelper.h"
map <string,struct Variable> variableInfoMap;
/**
 * @brief Initializes the register contents
 * 
 */
void intializeReg(){
    vector <string> TempStorage = {
         "x7", "x18", "x19", "x20",
        "x21", "x22", "x23", "x24", "x25", "x26", "x27",
        "x28", "x29", "x30", "x31"
        };

    vector <string> TempCal = {
        "x4", "x5", "x6" 
    };
    vector <string> Arg = {
        "x12", "x13", "x14", "x15", "x16", "x17"
    };

    // return values are stored in
    vector <string> RetValue = {
        "x9"
    };

    // return addresses are stored in
    vector <string> Ra= {
        "x1"
    };

    // All arguments are stored in memory

    RISCVReg["TEMPSTORAGE"]  = TempStorage;
    RISCVReg["TEMPCAL"] = TempCal;
    RISCVReg["ARG"] =  Arg;
    RISCVReg["RETVALUE"] = RetValue;
    RISCVReg["RETADDRESS"] = Ra;
}


/**
 * @brief Debugs the contents of a variable going by name
 * 
 * @param name 
 */
void printVariableMap(string name){
    cout<<"FUNCTION "<<name<<endl<<endl;
    

    for(auto [x,y] : variableInfoMap){
        cout<<"Name : "<< x<<endl;
        cout<<"startLine : "<<y.startLine<<endl;
        cout<<"endLine : "<<y.endLine<<endl;
        cout<<"frequency : "<<y.freq<<endl;
        cout<<"register : "<<y.reg<<endl;
        cout<<"\n ---------------------------------------------- \n";
    }
}

/**
 * @brief Pring All details of all the variables present in the function
 * 
 * @param _variableTableMap Map of Info of variable stored against name
 */
void printVariableTable(map <string, VariableInfo> _variableTableMap){
    cout<<"Registers allocated "<<endl;
    for(auto [_name, _info] : _variableTableMap){
        cout<<"Name"<<" : "<<_name<<endl;
        cout<<"Type"<<" : "<<_info.type<<endl;
        cout<<"Allocated Register : "<<_info.regAllocated<<endl;
        cout<<"Mem initialized :"<<_info.memLocOffset<<endl;
        cout<<"Starts :" <<variableInfoMap[_name].startLine<<endl;
        cout<<"Ends :" <<variableInfoMap[_name].endLine<<endl;
        cout<<endl;
    }
}


/**
 * @brief Allocate registers for the variables in the function
 * 
 */
void allocateRegister(string functionName, string regType){
    cout<<"here"<<regType<<endl;
    const int STORAGE_REG_COUNT = RISCVReg[regType].size();
    // create a graph
   


    int variableCnt = 0;
    for(auto [_varName, _varDetails] : variableInfoMap){
        if(_varDetails.type == regType)
            variableCnt++;
    }


    vector <int> adj[variableCnt];
    vector <int> degree(variableCnt);
    map <string, int> varToIntMap;
    vector <string> intToVarMap;
    int cnt = 0;
    for(auto [_varName, _varDetails] : variableInfoMap ){
        if(_varDetails.type != regType) continue;


        varToIntMap[_varName] = cnt++;
        intToVarMap.push_back(_varName);
    }
    // Heuristic algo to allocate
    for(auto [_varName, _varDetails] : variableInfoMap ){
        for(auto [_nVarName, _nVarDetails] : variableInfoMap){
            if(_nVarName != _varName && _nVarDetails.type == regType && _varDetails.type == regType){
                if((_nVarDetails.endLine >= _varDetails.startLine && _nVarDetails.startLine <= _varDetails.startLine)
                || (_nVarDetails.startLine <= _varDetails.endLine && _nVarDetails.endLine >= _varDetails.endLine)){
                    adj[varToIntMap[_varName]].push_back(varToIntMap[_nVarName]);
                    degree[varToIntMap[_nVarName]]++;
                }
                 
            }
        }
    }
    map <string, VariableInfo> _variableTableMap;
    queue <int> processQueue;
    set <int> yetToProcess;
    for(int i = 0; i < variableCnt; i++){
        yetToProcess.insert(i);
    }

    cout<<"Total reg available "<<STORAGE_REG_COUNT<<endl; 
    cout<<"Degrees "<<endl;
    for(auto i : degree){
        cout<<i<<" ";
    }

    cout<<endl;

    int memOffset =0;
    while(yetToProcess.size() > 0){
        for(int i =0; i < variableCnt; i++){
            if(degree[i] < STORAGE_REG_COUNT){
                processQueue.push(i);
            }
        }


        while(processQueue.size() > 0){
            int ele = processQueue.front();
            processQueue.pop();
            yetToProcess.erase(ele);

            set <string> allReg;
            for(auto i : RISCVReg[regType]){
                allReg.insert(i);
            }

            // assigning a register
            for(auto _nReg : adj[ele]){
                if(_variableTableMap.find(intToVarMap[_nReg]) != _variableTableMap.end()){
                    allReg.erase(_variableTableMap[intToVarMap[_nReg]].regAllocated);
                }

                degree[_nReg]--;
                if(degree[_nReg] < STORAGE_REG_COUNT && yetToProcess.count(_nReg) > 0){
                    processQueue.push(_nReg);
                }
            }

            struct VariableInfo _variableInfo = VariableInfo();
            _variableInfo.regAllocated = *(allReg.begin());         // This should be rightly executed;
            _variableInfo.presentInReg = true;
            _variableInfo.type = variableInfoMap[intToVarMap[ele]].type;
            _variableTableMap[intToVarMap[ele]] = _variableInfo;

        }

        // now allocate the other vertices
        // spill the first register
        if(yetToProcess.size() > 0){
            int ele = *yetToProcess.begin();
            yetToProcess.erase(ele);
            struct VariableInfo _variableInfo = VariableInfo();
            _variableInfo.memLocOffset = memOffset;
            _variableInfo.type = variableInfoMap[intToVarMap[ele]].type;
            for(auto _nReg : adj[ele]){
                degree[_nReg]--;
            }
            memOffset+=4;
            _variableTableMap[intToVarMap[ele]] = _variableInfo;

        }
        
    }
    for(auto [_varName, _varDetails] : _variableTableMap)
        functionDetailsMap[functionName].variableTable[_varName] = _varDetails;
    printVariableTable( functionDetailsMap[functionName].variableTable);


}


/**
 * @brief Driver Function for register allocation
 * 
 * @param functionName Function name whose allocation needs to be done
 */
void registerAllocator(string functionName){
    cout<<"Generating code for "<<functionName<<endl;
    intializeReg();
    
    FunctionDetailsTable funcTable = functionDetailsMap[functionName];
    vector <string> optimizedStream = funcTable.optCode;

    variableInfoMap.clear();
    // set <string> params;
    // for searching out all params
    // for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
    //     string line = optimizedStream[wordIndex];
    //     vector <string> words = processWords(line);
    //     if(find(words.begin(), words.end(), "param") != words.end()){
    //         int idx = find(words.begin(), words.end(), "param") - words.begin();
    //         string word = words[idx + 1];
    //         params.insert(word);
    //     }
    // }


    for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
         string line = optimizedStream[wordIndex];
        vector <string> words = processWords(line);
        
        // Syntax yet to be verified
        // Syntax : Memory x #size
        // Assumption : Memory cannot be allocated to a *
        if(find(words.begin(), words.end(), "Memory") != words.end()){
            int idx = find(words.begin(), words.end(), "Memory") - words.begin();
            string declared = words[idx + 1];
            
            if(variableInfoMap.count(declared) == 0){
                Variable newvar = Variable();
                newvar.startLine = wordIndex;
                newvar.endLine = wordIndex;
                variableInfoMap[declared] = newvar;
            }
            else{
                variableInfoMap[declared].endLine = wordIndex;
            }

            continue;
        }


        // Syntax if ( ) goto
        if(find(words.begin(), words.end(), "if") != words.end()){
            int idx = find(words.begin(), words.end(), "if") - words.begin();
            vector <string> identifiers;
            for(int i = idx +1 ; i < words.size(); i++){
                string token = words[i];
                if(token.substr(0,4) == "goto")
                    break;
                if(token[0] != '#' && token != "(" && token != ")" && operators.count(token) == 0){
                    identifiers.push_back(token);
                }
            }
            for(auto _identifier : identifiers){
                if(_identifier[0] == '*') 
                    _identifier = extractNameFromPointer(_identifier);

                if(variableInfoMap.count(_identifier) == 0){
                    Variable newvar = Variable();
                    newvar.startLine = wordIndex;
                    newvar.endLine = wordIndex;
                    variableInfoMap[_identifier] = newvar;
                }
                else{
                    variableInfoMap[_identifier].endLine = wordIndex;
                }
            }

            continue;

        }

        // Syntax : Return var
        if(find(words.begin(), words.end(), "Return") != words.end()){
            int idx = find(words.begin(), words.end(), "Return") - words.begin();
            // a = b op c
            string declared = words[idx + 1];

            //  ASSUMPTION: CANNOT RETURN A NUMBER
            if(declared[0] == '*')
                declared = extractNameFromPointer(declared);
            

            // now check
            if(variableInfoMap.count(declared) == 0){
                Variable newvar = Variable();
                newvar.startLine = wordIndex;
                newvar.endLine = wordIndex;
                variableInfoMap[declared] = newvar;
            }
            else{
                variableInfoMap[declared].endLine = wordIndex;
            }

            continue;
        }


        // Syntax: Assignment or Operation
        if(find(words.begin(), words.end(), "=") != words.end()){
            int idx = find(words.begin(), words.end(), "=") - words.begin();
            // a = b op c
            string declared = words[idx - 1];
            if(declared[0] == '*') 
                declared = extractNameFromPointer(declared);


            vector <string> identifiers;
            vector <string> constants;
            for(int i = idx + 1; i< words.size(); i++){
                if(operators.count(words[i]) == 0){
                    
                    if(words[i][0] != '#'){
                        if(words[i][0] == '*'){
                            identifiers.push_back(extractNameFromPointer(words[i]));
                        }
                        else
                            identifiers.push_back(words[i]);
                    }
                    else{
                        constants.push_back(words[i].substr(1));
                    }
                }
            }
            

            // now check
            if(variableInfoMap.count(declared) == 0){
                Variable newvar = Variable();
                newvar.startLine = wordIndex;
                newvar.endLine = wordIndex;
                // if(params.count(declared))
                //     newvar.type = "ARG";
                variableInfoMap[declared] = newvar;
            }
            else{
                variableInfoMap[declared].endLine = wordIndex;
            }

            for(auto _operand : identifiers){

                if(variableInfoMap.find(_operand) == variableInfoMap.end()){
                    Variable newvar = Variable();
                    newvar.startLine = wordIndex;
                    newvar.endLine = wordIndex;
                    // if(params.count(_operand))
                    //     newvar.type = "ARG";

                    variableInfoMap[_operand] = newvar;
                    cout<<"!Warning Variable "<<_operand<<" not declared \n\n";
                }
                else{
                    variableInfoMap[_operand].endLine = wordIndex;
                    // variableInfoMap[_operand].freq++;
                }
            }

        }
        

    }

    //  Syntax if (     )   goto 
    //  Syntax Memory x #v
    

    

    // cout<<"Params"<<endl;
    // for(auto i : params)
    //     cout<<i<<" ";
    // cout<<endl;
    cout<<"Variables"<<endl;
    for(auto [x,y] : variableInfoMap)
        cout<<x<<" ";

    cout<<endl;
    for(auto i : optimizedStream)
        cout<<i<<endl;

    cout<<endl<<endl;
    // printVariableMap(functionName);
    for(auto regType : {"TEMPSTORAGE"})
        allocateRegister(functionName, regType);

}
