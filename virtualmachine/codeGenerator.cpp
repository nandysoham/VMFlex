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
        

        // As per compiler only == type is bein done
        // if( x == y  ) goto types
        if(words[0] == "if"){
            int startB = find(words.begin(), words.end(), "(") - words.begin();
            int endB = find(words.begin(), words.end(), ")") - words.begin();
            int gotoIdx = find(words.begin(), words.end(), "goto") - words.begin();
            if(startB == words.size() || endB== words.size() || gotoIdx == words.size()){
                cout<<"Error : Wrong information in line "<<endl;
                for(auto i : words) cout<<i<<" ";
                cout<<endl;
                continue;
            }
            string label = words[gotoIdx + 1];
            vector <string> identifiers;
            string op = "";
            for(int i = startB + 1; i < endB; i++){
                string word = words[i];
                if(jumpsOp.count(word) > 0){
                    op = word;
                }
                else{
                    identifiers.push_back(word);
                }
            }


            if(op == ""){
                string message = "Error : Incomaptible Comparision operation - not in < >= == !=";
                throwError(words, message);
                continue;
            }

            
            if(identifiers.size() == 2){
                bool integral = false;
                if(identifiers[1][0] == '#')
                    integral = true;

                if(integral )
                    jumpOpCode(funcName, getVarToRegister(identifiers[0], funcName, 0), identifiers[1], op, label,integral);
                else
                    jumpOpCode(funcName, getVarToRegister(identifiers[0], funcName, 0), getVarToRegister(identifiers[1], funcName,1), op, label,integral);

            }
            else{
                string message = "Error : != 2 identifier in if () ";
                throwError(words,message);
                continue;
            }
        }

        // goto <label>
        else if(words[0] == "goto"){
            assemblyCode.push_back("\t JAL " + words[1]);
        }

        else if(words[0] == "call"){
            
            // note return address should be stored here


            // storing the return address
            comment("Spilling the return address to the 0th offset of the function");
            int newRetVal = assemblyCode.size() + 2;

            // store the return address in memory
            loadRAintoMemory(funcName);
            comment("Picking up the new return address");
            string code = "\t li \t\t" +RISCVReg["RETADDRESS"][0]+"\t"+to_string(newRetVal);
            assemblyCode.push_back(code);


            comment("Function call happening");
            assemblyCode.push_back("\t JAL " + words[1]);


             // get back the return address
            comment("getting back the old return address");
            loadMemoryIntoRA(funcName);

        }
        else if(words[0] == "Return"){
            comment("Function returning");
            loadIntoRegFromReg(funcName, getVarToRegister(words[1], funcName, 0), RISCVReg["RETVALUE"][0]);
            string code = "JAL " + RISCVReg["RETADDRESS"][0] + ";";
            assemblyCode.push_back(code);

           
        }

        // FunctionCall
        else if(words[0] == "FunctionCall"){
            string funcCalleeName = words[1];
            wordIndex++;
            // take in all the params
            int paramno = 0;
            while(wordIndex < optimizedStream.size() ){
                vector <string> paramwords = processWords(optimizedStream[wordIndex]);
                // break if the first word is not "param"
                if(paramwords.size() > 0 && paramwords[0] != "param"){
                    wordIndex--;
                    break;
                }
                wordIndex++;
                comment("");
                comment("assigning params for " + funcCalleeName);
                assignParams(funcCalleeName,funcName, paramwords[1], paramno);
                paramno++;
            }
        }

        // a = b op c types
        else if(find(words.begin(), words.end(), "=") != words.end()){
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


void throwError(vector <string> line, string message){
    cout<<message<<endl;
    for(auto i : line) cout<<i<<" ";
    cout<<endl;
}