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


// function that contains all information of a function

struct RegisterInfo{
    string name;
    string variableInside;
    int memLoc;

    RegisterInfo() : name(""), variableInside(""), memLoc(-1) {};
};

struct VariableInfo{
    string name;
    string regAllocated;
    string type;
    int memLoc;
    int memLocOffset;
    bool presentInReg;

    VariableInfo() : name(""), regAllocated(""), memLoc(-1), memLocOffset(-1), type("TEMPSTORAGE"), presentInReg(false) {};
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


FunctionDetailsTable::FunctionDetailsTable(){

}


FunctionDetailsTable::FunctionDetailsTable(FunctionTable _ft){
    this->functionName = _ft.functionName;
    this->code = _ft.code;
    this->label = _ft.label;
    this->returnType = _ft.returnType;
    this->parameters = _ft.parameters;
    this->localVariables = _ft.localVariables;
    this->tempVariables = _ft.tempVariables;


    // child class params
    this->variableCnt = 0;
    this->optCode = {};
    this->registerTable = {};
    this->variableTable = {};

    
}

vector <BasicBlock> basicBlockCollection;       // array to collect the basic blocks
vector <int> basicBlockAdj;                     // creates the adjacency list for that
map <string, int> labelsToColMap;

map <string, vector <string> > functionCalleeMap;
map <string, FunctionDetailsTable> functionDetailsMap;

vector <string> processWords(string line){
    vector <string> words;
    string word;
    for(int i =0; i < line.length(); i++){
        if(line[i] == ' '){
            if(word.length() > 0)
                words.push_back(word);

            word.clear();
        }
        else{
            word.push_back(line[i]);
        }
    }
    if(word.size() > 0)
        words.push_back(word);
    
    return words;
}

// ---------------  REGISTER ALLOCATION ----------------------//
struct Variable{
    int startLine;
    int endLine;
    int freq;
    string reg;
    string type;
    Variable() : startLine(-1), endLine(-1), freq(0), reg(""), type("TEMPSTORAGE") {}
};

// map <string,struct Variable> variableInfoMap;





//  ---------------- RISC - V Specific ---------------------- //
map <string, vector <string> > RISCVReg;
// set <string> operators;
// map <string, string> binaryOpMap;
// map <string, string> iBinaryOpMap;
set <string> operators = {
    "+", "-", "*", "/",
    "==", "<", ">", "<=", ">=", "!=",
    "^", "&", "|", "&&", "||",
    ">>", "<<"
};

 map <string, string> binaryOpMap = {
    {"+"    ,   "add"},
    {"-"    ,   "sub"},
    {"*"    ,   "mul"},
    {"/"    ,   "div"},
    {"^"    ,   "xor"},
    {"&"    ,   "and"},
    {"|"    ,   "or"},
    {">>"   ,   "shr"},
    {"<<"   ,   "shl"},
    {"<"    ,   "slt"},
    {">"    ,   "sgt"},
    {"<="   ,   "sleq"},
    {">="   ,   "sge"},
    {"=="   ,   "seq"}
 };


 map <string, string> iBinaryOpMap = {
    {"+"    ,   "addi"},
    {"-"    ,   "subi"},
    {"*"    ,   "muli"},
    {"/"    ,   "divi"}   
 };
#define FUNCTION_STACK_SIZE 1000
#define NET_STACK_SIZE 1000000

int sp = NET_STACK_SIZE;
map <string, int> functionHeapMemoryMap; 
vector <string> assemblyCode;