#include <vector>
#include <string>
#include <map>
#include <set>


#include "../CompFlex/helper.h"
using namespace std;

 struct BasicBlock{
    int startLine;
    int endLine;                        
    vector <int> successorBlock;        // denote which block shall be its successor
    bool isRequired;           // to denote whether this block has been isRequired or not
    string gotoLabel;

    BasicBlock() : startLine(-1), endLine(-1), successorBlock(vector <int> ()), isRequired(false) , gotoLabel("") {}
};


struct RegisterInfo{
    string name;
    string variableInside;
    int memLoc;

    RegisterInfo() : name(""), variableInside(""), memLoc(-1) {};
};

struct VariableInfo{
    string name;
    string regAllocated;
    int memLoc;
    int memLocOffset;
    bool presentInReg;

    VariableInfo() : name(""), regAllocated(""), memLoc(-1), presentInReg(false) {};
};

class FunctionDetailsTable : public FunctionTable {
    public:
        int variableCnt;
        map <string,RegisterInfo> registerTable;
        map  <string, VariableInfo> variableTable;
        vector <string> optCode;
        FunctionDetailsTable();
        FunctionDetailsTable(FunctionTable _ft); 
};

extern vector <BasicBlock> basicBlockCollection;       // array to collect the basic blocks
extern vector <int> basicBlockAdj;                     // creates the adjacency list for that
extern map <string, int> labelsToColMap;

extern vector <string> processWords(string line);
extern map <string, vector <string> > functionCalleeMap;
extern map <string, FunctionDetailsTable> functionDetailsMap;

// ---------------  REGISTER ALLOCATION ----------------------//
struct Variable{
    int startLine;
    int endLine;
    int freq;
    string reg;
    Variable() : startLine(-1), endLine(-1), freq(0), reg("") {}
};

// extern map <string,struct Variable> variableInfoMap;



//  ---------------- RISC - V Specific ---------------------- //
extern map <string, vector <string> > RISCVReg;
extern set <string> operators;
