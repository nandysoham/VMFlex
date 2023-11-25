#include "codeGenerator.h"
#include "codeGenHelper.h"
#include "Structure.h"

/**
 * @brief Assembly code to increment the stack pointer
 * 
 * @param step the number of steps to go down
 * if currently it sp --> it would be sp + step
 */
void increaseSp(int step = 1){
    string code = "\t addi \t sp sp "+to_string(step);
    assemblyCode.push_back(code);
}


/**
 * @brief Get the Offset Memory value given a particular step
 * 
 * @param step : step in integer
 * @return string 
 */
string getOffsetMemoryInt(int step=1){
    step = step*4;
    string code = to_string(step) + "(sp)";
    return code;
}


/**
 * @brief Load into register from memory
 * 
 * @param reg Destination Register
 * @param step the no of steps(/4) to get up
 */
void loadIntoRegFromMem(string funcName, string reg, int step, string val){
    // clearing existing details of reg
    clearExistingRegister(funcName, reg);
    insertDetailsIntoRegisterTable(funcName, reg, val);
    string code = "\t lw \t " + reg +" \t "+ getOffsetMemoryInt(step);
    assemblyCode.push_back(code);
}


/**
 * @brief Copy content of a register to another
 * 
 * @param funcName Name of the function
 * @param sourceReg Source Register
 * @param destReg Destination Register
 */
void loadIntoRegFromReg(string funcName, string sourceReg, string destReg){
    string val = functionDetailsMap[funcName].registerTable[sourceReg].variableInside;

    insertDetailsIntoRegisterTable(funcName, destReg, val);
    clearExistingRegister(funcName, destReg);


    string code = "\t mv \t\t" + destReg + "\t" + sourceReg;
    assemblyCode.push_back(code);
}


void loadValueIntoRegister(string funcName,string reg, string val){
    clearExistingRegister(funcName, reg);
    insertDetailsIntoRegisterTable(funcName, reg, val);

    string code = "\t li \t\t"+reg+"\t "+val;
    assemblyCode.push_back(code);
}

void loadRAintoMemory(string funcName){
    int addr = functionHeapMemoryMap[funcName];
    int step = (addr - sp)/4;
    string code = "\t sw \t " + RISCVReg["RETADDRESS"][0] +" \t "+ getOffsetMemoryInt(step);
    assemblyCode.push_back(code);
}

void loadMemoryIntoRA(string funcName){
    int addr = functionHeapMemoryMap[funcName];
    int step = (addr - sp)/4;
    string code = "\t lw \t " + RISCVReg["RETADDRESS"][0] +" \t "+ getOffsetMemoryInt(step);
    assemblyCode.push_back(code);
}

/**
 * @brief Load Into local Memory from Register
 * 
 * @param reg Destination Register where value needs to be stored 
 */
void loadIntoLocalMemoryFromReg(string reg){
    increaseSp;
    string code = "\t sw \t\t" + reg + "\t" + getOffsetMemoryInt(1);
    assemblyCode.push_back(code);
}


void loadIntoMemoryFromReg(string reg, int step){
    string code = "\t sw \t\t" + reg + "\t" + getOffsetMemoryInt(step);
    assemblyCode.push_back(code);
}


/**
 * @brief Given a identifier Gets the details of Variable and store it back
 * 
 * @param var Variable Name
 */
string getVarToRegister(string var, string funcName, int cnt){
    if(functionDetailsMap[funcName].variableTable[var].regAllocated != ""){
        functionDetailsMap[funcName].variableTable[var].presentInReg = true;
        return functionDetailsMap[funcName].variableTable[var].regAllocated;
    }
    else{
        int addr = functionDetailsMap[funcName].variableTable[var].memLoc;
        if(addr == -1){
            addr = functionDetailsMap[funcName].variableTable[var].memLocOffset;
            // functionDetailsMap[funcName].variableTable[var].memLoc = functionDetailsMap[funcName].variableTable[var].memLocOffset;
        }
        addr = functionHeapMemoryMap["free"] + addr*4;
        int step = (addr - sp)/4;
        string reg = RISCVReg["TEMPCAL"][cnt];

        // put the existing content of the register where it belongs
        
        loadIntoRegFromMem(funcName, reg, step, var);
        return reg;
    }
}



// a = b op c 
// op a,b,c

void arithOpCode(string funcName, string a, string b, string c, string op, bool integral = false){
    cout<<"here in artithOpcode"<<endl;
    string opCode = binaryOpMap[op];
    if(integral){
        opCode = iBinaryOpMap[op];
    }
    string codeLine = "\t" + opCode + "\t\t" + a + "\t" + b +  "\t" + c ;
   assemblyCode.push_back(codeLine);
}


void assignOpCode(string funcName, string a, string b, bool integral){
    if(!integral){
        loadIntoRegFromReg(funcName, a,b);
    }
    else{
        loadValueIntoRegister(funcName, a,b);
    }
}


void jumpOpCode(string funcName, string a, string b, string op, string label,bool integral){
    string opcode = jumpsOp[op];
    if(integral){
        // This would always be 0 -- as per compiler formulation
        b = RISCVReg["ZERO"][0];
    }

    string code = "\t "+opcode + "\t\t" + a + " ,\t" + b + " ,\t" + label;
    assemblyCode.push_back(code);

}



void assignParams(string funcName, string thisFuncName, string param, int pno){
    int MAX_ARG_REG = RISCVReg["ARG"].size();
    if(pno < MAX_ARG_REG){
        // only using the 0th temp register we can do the stuff
        comment("Param "+ param + "loading into " + RISCVReg["ARG"][pno]);
        loadIntoRegFromReg(funcName, getVarToRegister(param, thisFuncName, 0), RISCVReg["ARG"][pno]);
    }
    else{
        // load into the offset of the function
        int offset = pno - MAX_ARG_REG;
        int mem = functionHeapMemoryMap[funcName] + offset*4;
        int step = (mem - sp)/4;
        comment("Param "+ param + "loading into offset "+ to_string(offset) + " of " + funcName);
        loadIntoMemoryFromReg( getVarToRegister(param, thisFuncName, 0),step);      
    }
}

/**
 * @brief Get the Org Variable From Param object
 * 
 * @param s argument name
 * @return string 
 */
string getOrgVarFromParam(string s){
    int idx = find(s.begin(), s.end(), '_') - s.begin();
    string sFinal = "";
    for(int i = 0; i < idx; i++)
        sFinal.push_back(s[i]);

    return sFinal;
}

/**
* 
*/
void insertDetailsIntoRegisterTable(string funcName,string reg, string var){
    string code = "Putting " + var + " inside "+reg;
    comment(code);
    functionDetailsMap[funcName].registerTable[reg].variableInside = var;
}





/**
*   @brief Clears the existing content of a register
*/
void clearExistingRegister(string funcName, string reg){
    if(functionDetailsMap[funcName].registerTable[reg].variableInside != ""){
        string var = functionDetailsMap[funcName].registerTable[reg].variableInside;
        if(var != ""){
            string code = "Clearing " + reg + " having value " + var;
            int mem = functionDetailsMap[funcName].variableTable[var].memLocOffset;
            int step = (functionHeapMemoryMap["free"] + 2*mem - sp)/4;
            comment(code);
            loadIntoMemoryFromReg(reg, step);
        }
        // push this value back
    }
}



/**
 * @brief Loading Argument to a variable
 * 
 * @param addr Address of the argument
 * @param param Name of the argument
 * @param funcName Function Name
 * @param no ith argument
 */
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
                    loadIntoRegFromReg(funcName, RISCVReg["ARG"][no], _varDetails.regAllocated);
                }
                else{
                    // copying from the memory address to the allocated register;
                    int step = (addr - sp)/4;
                    loadIntoRegFromMem(funcName, _varDetails.regAllocated, step, _varName);
                    functionDetailsMap[funcName].variableTable[_varName].presentInReg = true;
                }
            }
            else{
                // this variable has got no register
                if(no < RISCVReg["ARG"].size()){
                    loadIntoLocalMemoryFromReg(RISCVReg["ARG"][no]);
                    loadIntoRegFromMem(funcName, _varDetails.regAllocated, 1, _varName);
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