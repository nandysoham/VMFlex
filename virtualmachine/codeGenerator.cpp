#include <iostream>
#include "Structure.h"
#include "codeGenerator.h"

void intializeReg(){
    vector <string> Temp = {
        "x4", "x5", "x6" , "x7", "x18", "x19", "x20",
        "x21", "x22", "x23", "x24", "x25", "x26", "x27",
        "x28", "x29", "x30", "x31"
        };

    vector <string> Arg = {
        "x12", "x13", "x14", "x15", "x16", "x17"
    };

    RISCVReg["Temp"]  = Temp;
    RISCVReg["Arg"] =  Arg;
}


void printVariableMap(){
    for(auto [x,y] : variableInfoMap){
        cout<<"Name : "<< x<<endl;
        cout<<"startLine : "<<y.startLine<<endl;
        cout<<"endLine : "<<y.endLine<<endl;
        cout<<"frequency : "<<y.freq<<endl;
        cout<<"register : "<<y.reg<<endl;
        cout<<"\n ---------------------------------------------- \n";
    }
}

void codeGenerator(){
    intializeReg();
    for(int wordIndex = 0; wordIndex < optimizedStream.size(); wordIndex++){
        string line = optimizedStream[wordIndex];
        vector <string> words = processWords(line);
        if(find(words.begin(), words.end(), "=") != words.end()){
            int idx = find(words.begin(), words.end(), "=") - words.begin();
            // a = b op c
            string declared = words[idx - 1];
            vector <string> operands;
            for(int i = idx + 1; i< words.size(); i++){
                if(operators.count(words[i]) == 0){
                    if(words[i][0] != '#'){
                        operands.push_back(words[i]);
                    }
                }
            }


            // now check
            if(variableInfoMap.count(declared) == 0){
                Variable newvar = Variable();
                newvar.startLine = wordIndex;
                variableInfoMap[declared] = newvar;
            }

            for(auto _operand : operands){
                if(variableInfoMap.find(_operand) == variableInfoMap.end()){
                    cout<<"!Error Variable "<<_operand<<" not delcared \n\n";
                }
                else{
                    variableInfoMap[_operand].endLine = wordIndex;
                    variableInfoMap[_operand].freq++;
                }
            }

        }
    }

    printVariableMap();

}
