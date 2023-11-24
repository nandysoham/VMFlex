#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>


using namespace std;
void increaseSp(int step);
void loadIntoRegFromMem(string funcName, string reg, int step);
string getOrgVarFromParam(string s);
void loadToVariable(int addr, string param, string funcName, int no);
string getOffsetMemoryInt(int step);

void arithOpCode(string funcName,string a, string b, string c, string op, bool integral );
string getVarToRegister(string var, string funcName, int cnt);
void insertDetailsIntoRegisterTable(string funcName,string reg, string var);
void clearExistingRegister(string funcName, string reg);
void assignOpCode(string funcName, string a, string b, bool integral);