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
class FunctionDetailsTable : public FunctionTable {
    public:
        string registers;
        string variables;
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
    this->optCode = {};
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
    Variable() : startLine(-1), endLine(-1), freq(0), reg("") {}
};

map <string,struct Variable> variableInfoMap;





//  ---------------- RISC - V Specific ---------------------- //
map <string, vector <string> > RISCVReg;
set <string> operators = {
    "+", "-", "*", "/",
    "==", "<", ">", "<=", ">=", "!=",
    "^", "&", "|", "&&", "||",
    ">>", "<<"
};
