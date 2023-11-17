#include "codeGenerator.h"
#include "Structure.h"
#include "codeGenHelper.h"

// a = b op c 
// op a,b,c
string appendCode(string a, string b, string c, string op, bool integral = false){
    string opCode = binaryOpMap[op];
    string codeLine = opCode + "\t" + a + ", " + "b, " + "c ";
    return codeLine;
}

bool memoryInitializer(){
    int cnt = 0;
    for(auto [_functionName, _functionDetails] : functionDetailsMap){
        if(NET_STACK_SIZE - cnt*FUNCTION_STACK_SIZE < 0){
            return false;
        }
        functionHeapMemoryMap[_functionName] = NET_STACK_SIZE - cnt*FUNCTION_STACK_SIZE;
        cnt++;
    }

    functionHeapMemoryMap["free"] = NET_STACK_SIZE - cnt*FUNCTION_STACK_SIZE; 
    sp = functionHeapMemoryMap["free"];
    return true;
}

void fetchParams(string funcName){
    vector <SymbolTableEntry> params = functionDetailsMap[funcName].parameters;
    int cnt = 0;
    for(auto _param : params){
        int addr = functionHeapMemoryMap[funcName];
        loadToVariable(addr, _param.name, funcName, cnt);
        cnt++;
    }
} 

void codeGenerator(string funcName){
    comment("Fetching params for " + funcName);
    fetchParams(funcName);

    FunctionDetailsTable _functionDetailsTable = functionDetailsMap[funcName];
    vector <string> optimizedStream = _functionDetailsTable.optCode;

    vector <string> assemblyStream;
    for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
         string line = optimizedStream[wordIndex];
        vector <string> words = processWords(line);

        // a = b op types
        if(find(words.begin(), words.end(), "=") != words.end()){

        }

    }

}

void preProcessAssembly(){
    assemblyCode.push_back(".data\n");
    assemblyCode.push_back(".text");
    assemblyCode.push_back("\t .globl main");
    assemblyCode.push_back(".main");

}

void comment(string s){
    assemblyCode.push_back("\t ;" + s);
}