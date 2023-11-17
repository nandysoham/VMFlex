#include "codeGenerator.h"
#include "Structure.h"


void increaseSp(int step = 1){
    string code = "\t addi \t sp sp "+to_string(4*step);
    sp = sp + 4;
    assemblyCode.push_back(code);
}

string getOffsetMemory(int step){
    string code = to_string(step) + "(sp)";
    return code;
}


void loadIntoRegFromMem(string reg, int step){
    string code = "\t lw \t " + reg + getOffsetMemory(step);
    assemblyCode.push_back(code);
}

void loadIntoRegFromReg(string sourceReg, string destReg){
    string code = "\t mv \t\t" + destReg + "\t" + sourceReg;
    assemblyCode.push_back(code);
}

void loadIntoLocalMemoryFromReg(string reg){
    increaseSp;
    string code = "\t sw \t\t" + reg + "\t" + getOffsetMemory(4);
    assemblyCode.push_back(code);
}

string getOrgVarFromParam(string s){
    int idx = find(s.begin(), s.end(), '_') - s.begin();
    string sFinal = "";
    for(int i = 0; i < idx; i++)
        sFinal.push_back(s[i]);

    return sFinal;
}


void loadToVariable(int addr, string param, string funcName, int no){
    cout<<funcName<<endl;
    map <string, VariableInfo> mp = functionDetailsMap[funcName].variableTable;
    cout<<mp.size()<<endl;
    bool touch = false;
    for(auto [_varName,_varDetails] : functionDetailsMap[funcName].variableTable){
        // cout<<_varName<<" & "<<getOrgVarFromParam(_varName)<<endl;
        if(getOrgVarFromParam(_varName) == param){
            if(functionDetailsMap[funcName].variableTable[_varName].regAllocated != ""){
                // the variable is stored in a register

                if(no < RISCVReg["ARG"].size()){
                    // copying from arg registers to the allocated register
                    loadIntoRegFromReg(RISCVReg["ARG"][no], _varDetails.regAllocated);
                }
                else{
                    // copying from the memory address to the allocated register;
                    int step = (addr - sp)/4;
                    loadIntoRegFromMem(_varDetails.regAllocated, step);
                    functionDetailsMap[funcName].variableTable[_varName].presentInReg = true;
                }
            }
            else{
                // this variable has got no register
                if(no < RISCVReg["ARG"].size()){
                    loadIntoLocalMemoryFromReg(RISCVReg["ARG"][no]);
                    loadIntoRegFromMem(_varDetails.regAllocated, 1);
                }
                else{
                    functionDetailsMap[funcName].variableTable[_varName].memLoc = addr;
                }
            }
            touch = true;
        }
    }

    if(!touch){
        cout<<"!!!Error"<<endl;
        cout<<"Could not find param "<<param<<endl;
    }
}