#include <vector>
#include <string>
#include <map>

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