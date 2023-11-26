#include "heapManager.h"
#include "Structure.h"
#include "codeGenerator.h"
#include "codeGenHelper.h"

void allocateMem(string reg, string amountreg){

    string code = "";
    int offset = functionHeapMemoryMap["main"] - sp;
    // pciking up the heapaddress 
    code = "\t lw \t\t "+RISCVReg["TEMPCAL"][0] + "\t,\t" + to_string(offset) + "(sp)";
    assemblyCode.push_back(code);


    // decreasing the address by amount
    code = "\t sub \t\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + amountreg;
    assemblyCode.push_back(code);

    // putting it back to mains offset
    code = "\t sw \t\t "+RISCVReg["TEMPCAL"][0] +"\t,\t"+ to_string(offset) + "(sp)";
    assemblyCode.push_back(code);

    // putting it into register 
    code = "\t mov \t\t" + reg + "\t,\t" + RISCVReg["TEMPCAL"][0];
    assemblyCode.push_back(code);

}

void loaderPointerToReg(string var,string funcName, int cnt){
    string code;
    if(var[0] != '*'){
        // base case
        string reg = getVarToRegister(var, funcName, cnt);
        // code = "\t SUB \t\t" + RISCVReg["TEMPCAL"][cnt] + "\t," + reg + ",\t" + "sp";
        // assemblyCode.push_back(code);
        // code = "\tlw \t\t " + RISCVReg["TEMPCAL"][cnt] + "\t," + RISCVReg["TEMPCAL"][cnt] + "(sp)";
        // assemblyCode.push_back(code);
        return;
    }
    // recursively 
    loaderPointerToReg(var.substr(1), funcName, cnt);
    code = "\t sub \t\t" + RISCVReg["TEMPCAL"][cnt] + "\t,\t" + RISCVReg["TEMPCAL"][cnt] + "\t,\t" + "sp";
    assemblyCode.push_back(code);
    code = "\tlw \t\t " + RISCVReg["TEMPCAL"][cnt] + "\t,\t" + RISCVReg["TEMPCAL"][cnt] + "(sp)";
    assemblyCode.push_back(code);

}

// **a = b + c
// spill Tempcal[0] into that location 
void storeDeclaredInHeap(string reg, string var, string funcName, string orgVar){
    string code;
    if(var[0] != '*'){
        // load address into the tempcal[2]
        string reg = getVarToRegister(var, funcName, 2);
        return;
    }
    // recursively 
    loaderPointerToReg(var.substr(1), funcName, 1);
    code = "\t sub \t\t" + RISCVReg["TEMPCAL"][1] + "\t,\t" + RISCVReg["TEMPCAL"][1] + "\t,\t" + "sp";
    assemblyCode.push_back(code);
    
    code = "\tlw \t\t " + RISCVReg["TEMPCAL"][1] + "\t,\t" + RISCVReg["TEMPCAL"][1] + "(sp)";
    assemblyCode.push_back(code);
    if(var == orgVar){
        // now store this
        code = "\t sub \t\t" + RISCVReg["TEMPCAL"][1] + "\t,\t" + RISCVReg["TEMPCAL"][1] + "\t,\t" + "sp";
        assemblyCode.push_back(code);
        
        // always the first one will be stored
        code = "\tsw \t\t " + reg + "\t,\t" + RISCVReg["TEMPCAL"][1] + "(sp)";
        assemblyCode.push_back(code);
        functionDetailsMap[funcName].registerTable[reg].variableInside = "";
    }
}


void storeRegisterTable(string funcName){
    comment("Storing register table of " + funcName);
    comment("");
    comment("");
    int sze = functionDetailsMap[funcName].registerTable.size();
    string code = "";
    int offset = functionHeapMemoryMap["main"] - sp;
    // pciking up the heapaddress 
    code = "\t lw \t\t "+RISCVReg["TEMPCAL"][0] + "\t,\t" + to_string(offset) + "(sp)";
    assemblyCode.push_back(code);
    code = "\t addi \t\t"+RISCVReg["TEMPCAL"][0]+"\t,\t"+RISCVReg["TEMPCAL"][0]+"\t,t"+to_string(offset);
    assemblyCode.push_back(code);
    code = "\t sw \t\t "+RISCVReg["TEMPCAL"][0] + "\t,\t" + to_string(offset) + "(sp)";
    assemblyCode.push_back(code);


    code = "\t sub \t\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + "sp";
    assemblyCode.push_back(code);

    for(auto [_regName, _regDetails] : functionDetailsMap[funcName].registerTable){
        code = "\tsw \t\t " + _regName + "\t,\t" + RISCVReg["TEMPCAL"][0] + "(sp)";
        assemblyCode.push_back(code);
        code =  "\taddi \t\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + "4";
        assemblyCode.push_back(code);
    }

    comment("Done storing Register Table");
    comment("");
    comment("");
    
}




void retrieveRegisterTable(string funcName){
    comment("Retreiving register table of " + funcName);
    comment("");
    comment("");
    int sze = functionDetailsMap[funcName].registerTable.size();
    string code = "";
    int offset = functionHeapMemoryMap["main"] - sp;
    // pciking up the heapaddress 
    code = "\t lw \t\t "+RISCVReg["TEMPCAL"][0] + "\t,\t" + to_string(offset) + "(sp)";
    assemblyCode.push_back(code);


    code = "\t sub \t\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + "sp";
    assemblyCode.push_back(code);

    for(auto [_regName, _regDetails] : functionDetailsMap[funcName].registerTable){
        code = "\tlw \t\t " + _regName + "\t,\t" + RISCVReg["TEMPCAL"][0] + "(sp)";
        assemblyCode.push_back(code);
        code =  "\taddi \t\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + RISCVReg["TEMPCAL"][0] + "\t,\t" + "4";
        assemblyCode.push_back(code);
    }

    comment("Done Retrieving Register Table");
    comment("");
    comment("");
    
}