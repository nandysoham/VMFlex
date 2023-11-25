#include "heapManager.h"
#include "Structure.h"
#include "codeGenerator.h"
#include "codeGenHelper.h"

void allocateMem(string reg, string amountreg){

    string code = "";
    int offset = functionHeapMemoryMap["main"] - sp;
    // pciking up the heapaddress 
    code = "\t lw \t\t "+RISCVReg["TEMPCAL"][0] + "\t" + to_string(offset) + "(sp)";
    assemblyCode.push_back(code);


    // decreasing the address by amount
    code = "\t SUB \t\t" + RISCVReg["TEMPCAL"][0] + "\t," + RISCVReg["TEMPCAL"][0] + ",\t" + amountreg;
    assemblyCode.push_back(code);

    // putting it back to mains offset
    code = "\t sw \t\t "+RISCVReg["TEMPCAL"][0] +"\t"+ to_string(offset) + "(sp)";
    assemblyCode.push_back(code);

    // putting it into register 
    code = "\t mov \t\t" + reg + "\t," + RISCVReg["TEMPCAL"][0];
    assemblyCode.push_back(code);

}


