#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
 

using namespace std;
bool memoryInitializer();
void codeGenerator(string funcName);
void preProcessAssembly();
void comment(string s);

void initializeRegisterTable(string funcName);
void printRegisterTable(string funcName);
void throwError(vector <string> line, string message);