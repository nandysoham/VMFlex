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


vector <BasicBlock> basicBlockCollection;       // array to collect the basic blocks
vector <int> basicBlockAdj;                     // creates the adjacency list for that
map <string, int> labelsToColMap;
vector <string> optimizedStream;

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
