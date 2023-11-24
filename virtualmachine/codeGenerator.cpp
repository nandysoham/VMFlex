#include "codeGenerator.h"
#include "Structure.h"
#include "codeGenHelper.h"


/**
 * @brief On start of each function , a space is reversed in the stack which is used as
 * heap. This stores the information regarding overflown params
 * 
 * @return true - If initialized successfully
 * @return false - Otherwise
 */
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

/**
 * @brief Fetch all the arguments to the particular function 
 * 
 * @param funcName The name of the function it currently refers to
 */
void fetchParams(string funcName){
    if(funcName == "main"){
        // get the sp down
        comment("Moving sp to the Free segment");
        int steps = NET_STACK_SIZE - functionHeapMemoryMap["free"];
        string code = "\t add \t sp,    sp  , " + to_string(steps);
        assemblyCode.push_back(code);

        // initializing heap address at O(Main)
        comment("Initializing Heap Address at First offset of main");
        string reg = RISCVReg["TEMPSTORAGE"][0];
         code = "\t li \t\t "+ reg + ",  x000";
        assemblyCode.push_back(code);
        int addr = functionHeapMemoryMap[funcName];
        cout<<"Main starts at"<<addr<<endl;
        cout<<"sp is at "<<sp<<endl;
        int dist = (addr - sp)/4;
        code = "\t sw \t\t" + reg + "\t" + getOffsetMemoryInt(dist);
        assemblyCode.push_back(code);


        // initializing return address at 1(Main)
        comment("Initializing Return Address at Second offset of main");
        code = "\t li \t\t "+ reg+ ",  x000";
        assemblyCode.push_back(code);
        dist-=1;
        code = "\t sw \t\t " + reg + ", \t" + getOffsetMemoryInt(dist);
        assemblyCode.push_back(code);
        return;
    }

    // Fetching params for other functions
    comment("Fetching params for " + funcName);
    vector <SymbolTableEntry> params = functionDetailsMap[funcName].parameters;
    int cnt = 0;
    for(auto _param : params){
        int addr = functionHeapMemoryMap[funcName];
        loadToVariable(addr, _param.name, funcName, cnt);
        cnt++;
    }
} 

/**
* @brief Initializes the Register Table for a particular function
*/
void initializeRegisterTable(string funcName){
    for(auto [_registype, _regArray] : RISCVReg){
        for(auto j : _regArray){
            functionDetailsMap[funcName].registerTable[j] = RegisterInfo();
            functionDetailsMap[funcName].registerTable[j].name = j;
            functionDetailsMap[funcName].registerTable[j].type = _registype;
        }
    }
}


/**
*   @brief Printing the register table
*/
void printRegisterTable(string funcName){
    cout<<"Printing Register Table for "<<funcName<<endl;
    cout<<"--------------------------------------------------------\n";
    for(auto i : functionDetailsMap[funcName].registerTable){
        cout<<i.first<<" : "<<endl;
        cout<<endl;
        cout<<"Type : "<<i.second.type<<endl;
        cout<<"Value : "<<i.second.variableInside<<endl;
        cout<<endl;
    }
    
    cout<<"--------------------------------------------------------\n";

}


void initializeMemoryForSpilling(string funcName){
    int cnt = 0;
    for(auto [_varName, _varDetails] : functionDetailsMap[funcName].variableTable){
        if(_varDetails.memLocOffset != -1){
            functionDetailsMap[funcName].variableTable[_varName].memLoc = sp + cnt;
            cnt++;
        }
    }

    // increase the stack pointer by this value
    if(cnt){
        comment("Allocating space for variables ");
    }
}

/**
 * @brief Creates the assembly code for the function
 *  
 * @param funcName Name of the function  
 */
void codeGenerator(string funcName){
    assemblyCode.push_back("\n\n");
    comment("Function " + funcName);
    assemblyCode.push_back("\n");
    initializeRegisterTable(funcName);
    fetchParams(funcName);
    printRegisterTable(funcName);
    FunctionDetailsTable _functionDetailsTable = functionDetailsMap[funcName];
    vector <string> optimizedStream = _functionDetailsTable.optCode;

    vector <string> assemblyStream;
    for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
         string line = optimizedStream[wordIndex];
        vector <string> words = processWords(line);

        // a = b op c types
        if(find(words.begin(), words.end(), "=") != words.end()){
            int idx = find(words.begin(), words.end(), "=") - words.begin();
            string var1 = words[idx - 1];
            string op= "";
            vector <string> vars;
            for(int i = idx + 1; i < words.size(); i++){
                if(binaryOpMap.count(words[i])){
                    op = words[i];
                }
                else{
                    vars.push_back(words[i]);
                }
            }

            if(op != "" && vars.size() == 2){
                bool integral = false;
                if(vars[1][0] == '#'){
                    integral = true;
                    vars[1] = vars[1].substr(1);
                }

                if(!integral){
                    arithOpCode(
                    funcName,
                    getVarToRegister(var1, funcName, 0), 
                    getVarToRegister(vars[0], funcName, 1), 
                    getVarToRegister(vars[1], funcName, 2),
                     op, integral);
                }
                else{
                    arithOpCode(
                    funcName,
                    getVarToRegister(var1, funcName, 0), 
                    getVarToRegister(vars[0], funcName, 1), 
                    vars[1],
                     op, integral);
                }
            }
            else if(op == "" && vars.size() == 2 && vars[0] == "minus"){
                bool integral = false;
                if(vars[1][0] == '#'){
                    integral = true;
                    vars[1] = vars[1].substr(1);
                }

                if(!integral){
                    arithOpCode(
                    funcName,
                    getVarToRegister(var1, funcName, 0), 
                    RISCVReg["ZERO"][0], 
                    getVarToRegister(vars[1], funcName, 2),
                    "-", integral);
                }
                else{
                    arithOpCode(
                    funcName,
                    getVarToRegister(var1, funcName, 0), 
                    RISCVReg["ZERO"][0],
                    vars[1],
                     "-", integral);
                }
            }
            else if(op == "" && vars.size() == 1){
                if(vars[0][0] != '#'){
                    assignOpCode(funcName, getVarToRegister(var1, funcName, 0) ,
                         getVarToRegister(vars[0], funcName, 1),
                         false
                    );
                }
                else{
                    assignOpCode(funcName, getVarToRegister(var1, funcName, 0) ,
                         vars[0].substr(1),
                         true
                    );
                    
                }
            } 
            else{
               assemblyCode.push_back("\t Error " + line); 
            }
        }
        else{
            assemblyCode.push_back("\t" + line);
        }

    }

}

/**
 * @brief Preprocesses the assembly which includes addition of .data and .text 
 * segments before any Instruction gets added 
 * 
 */
void preProcessAssembly(){
    assemblyCode.push_back(".data\n");
    assemblyCode.push_back(".text");
    assemblyCode.push_back("\t .globl main");
    assemblyCode.push_back(".main");

}

/**
 * @brief Prints a commented line in the assembly
 * 
 * @param s the actual comment
 */
void comment(string s){
    assemblyCode.push_back("\t #" + s);
}