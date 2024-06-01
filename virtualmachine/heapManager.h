#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
 

using namespace std;
void allocateMem(string reg, string amountreg);
void loaderPointerToReg(string var,string funcName, int cnt);
void storeDeclaredInHeap(string reg, string var, string funcName, string orgVar);
void storeRegisterTable(string funcName);
void retrieveRegisterTable(string funcName);