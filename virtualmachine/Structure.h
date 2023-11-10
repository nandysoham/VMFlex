#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

 struct BasicBlock{
    int startLine;
    int endLine;                        
    vector <int> successorBlock;        // denote which block shall be its successor
    bool isRequired;           // to denote whether this block has been isRequired or not
    string gotoLabel;

    BasicBlock() : startLine(-1), endLine(-1), successorBlock(vector <int> ()), isRequired(false) , gotoLabel("") {}
};


extern vector <BasicBlock> basicBlockCollection;       // array to collect the basic blocks
extern vector <int> basicBlockAdj;                     // creates the adjacency list for that
extern map <string, int> labelsToColMap;
extern vector <string> optimizedStream;
extern vector <string> processWords(string line);


// ---------------  REGISTER ALLOCATION ----------------------//
struct Variable{
    int startLine;
    int endLine;
    int freq;
    string reg;
    Variable() : startLine(-1), endLine(-1), freq(0), reg("") {}
};

extern map <string,struct Variable> variableInfoMap;



//  ---------------- RISC - V Specific ---------------------- //
extern map <string, vector <string> > RISCVReg;
extern set <string> operators;
