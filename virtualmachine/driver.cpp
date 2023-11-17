#include "driver.h"
#include "DeadCodeRemoval.h"
#include "registerAllocator.h"
#include <string>
#include "Structure.h"
#include "codeGenerator.h"


int main(int arc, char** argv){
    parser();
    // translate();
    for(auto functionStruct : globalTable){
        if(functionStruct.functionTables.size() > 0){
            for(auto _function : functionStruct.functionTables){
                functionDetailsMap[_function.functionName] = FunctionDetailsTable(_function);
                vector <string> code = _function.code;
                // for(auto i : code)
                //     cout<<i<<endl;
                // cout<<endl;

                // deadCodeRemoval should be at function level
                deadCodeRemoval(code, _function.functionName);
                
               
            }
        
        }
        else
            cout<<"No function exists for File"<<endl;
    }

    showCallerCalllee();
    removeUnessentialFunction();
    // printFunctionDetails();

    for(auto [_functionName, _functionDetails] : functionDetailsMap ){
        registerAllocator(_functionName);
    }



    bool isEnoughMemory = memoryInitializer();
    if(!isEnoughMemory){
        cout<<"Not enough Memory to allocate! Increase Memory stack size"<<endl;
        return EXIT_FAILURE;
    }
    preProcessAssembly();
    // actual code
    codeGenerator("main");
    for(auto [_functionName, _functionDetails] : functionDetailsMap ){
        if(_functionName == "main") continue;
        cout<<_functionName<<endl;
        map <string, VariableInfo> mp= _functionDetails.variableTable;
        cout<<"size "<<mp.size()<<endl;
        codeGenerator(_functionName);
    }


    ofstream assemblyFile;
    assemblyFile.open("assembly.asm", std::ios::out);

    if (!assemblyFile.is_open()) {
        std::cerr << "Error opening assemblyFile" << std::endl;
        return 1;
    }

    
    for(auto i : assemblyCode){
        assemblyFile<<i<<endl;
    }
    
    // ifstream TACFile("code.tac");

    // // Check if the file is open.
    // if (!TACFile.is_open()) {
    //     cout << "Error opening file." << endl;
    //     return 1;
    // }
    
    // vector <string> inputStream;
    // // Read the contents of the file line by line.
    // string line;
    // while (getline(TACFile, line)) {
    //     // Print the line to the console.
    //     inputStream.push_back(line);
    // }

    // // Close the file.
    // TACFile.close();
   
    // deadCodeRemoval(inputStream);
    // registerAllocator();
    return EXIT_SUCCESS;
}