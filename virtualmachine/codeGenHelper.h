#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>


using namespace std;
void increaseSp(int step = 1);
void loadIntoRegFromMem(string reg, int step);
string getOrgVarFromParam(string s);
void loadToVariable(int addr, string param, string funcName, int no);
string getOffsetMemoryInt(int step=1);

void arithOpCode(string a, string b, string c, string op, bool integral = false);
string getVarToRegister(string var, string funcName, int cnt);