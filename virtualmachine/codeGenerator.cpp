#include <iostream>
#include "Structure.h"
#include "codeGenerator.h"

map <string,struct Variable> variableInfoMap;

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

    RISCVReg["TEMPSTORAGE"]  = TempStorage;
    RISCVReg["TEMPCAL"] = TempCal;
    RISCVReg["ARG"] =  Arg;
}


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


void printVariableTable(map <string, VariableInfo> _variableTableMap){
    cout<<"Registers allocated "<<endl;
    for(auto [_name, _info] : _variableTableMap){
        cout<<"Name"<<" : "<<_name<<endl;
        cout<<"Type"<<" : "<<_info.type<<endl;
        cout<<"Allocated Register : "<<_info.regAllocated<<endl;
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
            memOffset+=4;
            _variableTableMap[intToVarMap[ele]] = _variableInfo;

        }
        
    }
    functionDetailsMap[functionName].variableTable = _variableTableMap;
    printVariableTable(_variableTableMap);


}

void codeGenerator(string functionName){
    cout<<"Generating code for "<<functionName<<endl;
    intializeReg();
    
    FunctionDetailsTable funcTable = functionDetailsMap[functionName];
    vector <string> optimizedStream = funcTable.optCode;

    variableInfoMap.clear();
    set <string> params;
    // for searching out all params
    for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
        string line = optimizedStream[wordIndex];
        vector <string> words = processWords(line);
        if(find(words.begin(), words.end(), "param") != words.end()){
            int idx = find(words.begin(), words.end(), "param") - words.begin();
            string word = words[idx + 1];
            params.insert(word);
        }
    }


    for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
         string line = optimizedStream[wordIndex];
        vector <string> words = processWords(line);
        
        if(find(words.begin(), words.end(), "=") != words.end()){
            int idx = find(words.begin(), words.end(), "=") - words.begin();
            // a = b op c
            string declared = words[idx - 1];
            if(declared[0] == '*') declared = declared.substr(1);
            vector <string> operands;
            vector <string> constants;
            for(int i = idx + 1; i< words.size(); i++){
                if(operators.count(words[i]) == 0){
                    
                    if(words[i][0] != '#'){
                        if(words[i][0] == '*'){
                            operands.push_back(words[i].substr(1));
                        }
                        operands.push_back(words[i]);
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
                if(params.count(declared))
                    newvar.type = "ARG";
                variableInfoMap[declared] = newvar;
            }

            for(auto _operand : operands){
                if(variableInfoMap.find(_operand) == variableInfoMap.end()){
                    Variable newvar = Variable();
                    newvar.startLine = wordIndex;
                    newvar.endLine = wordIndex;
                    if(params.count(_operand))
                        newvar.type = "ARG";

                    variableInfoMap[declared] = newvar;
                    cout<<"!Warning Variable "<<_operand<<" not declared \n\n";
                }
                else{
                    variableInfoMap[_operand].endLine = wordIndex;
                    variableInfoMap[_operand].freq++;
                }
            }

        }
        // Syntax : Return var
        if(find(words.begin(), words.end(), "Return") != words.end()){
            int idx = find(words.begin(), words.end(), "Return") - words.begin();
            // a = b op c
            string declared = words[idx + 1];

            //  ASSUMPTION CANNOT RETURN A NUMBER
            if(declared[0] == '*')
                declared = declared.substr(1);
            

            // now check
            if(variableInfoMap.count(declared) == 0){
                Variable newvar = Variable();
                newvar.startLine = wordIndex;
                newvar.endLine = wordIndex;
                variableInfoMap[declared] = newvar;
            }
        }

    }

    cout<<"Params"<<endl;
    for(auto i : params)
        cout<<i<<" ";
    cout<<endl;
    cout<<"Variables"<<endl;
    for(auto [x,y] : variableInfoMap)
        cout<<x<<" ";

    cout<<endl;
    for(auto i : optimizedStream)
        cout<<i<<endl;

    cout<<endl<<endl;
    // printVariableMap(functionName);
    for(auto regType : {"TEMPSTORAGE", "ARG"})
        allocateRegister(functionName, regType);

}
