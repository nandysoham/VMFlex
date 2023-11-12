#include "driver.h"
#include "DeadCodeRemoval.h"
#include "codeGenerator.h"
#include <string>
#include "Structure.h"

int main(int arc, char** argv){
    parser();
    // translate();
    for(auto functionStruct : globalTable){
        if(functionStruct.functionTables.size() > 0){
            for(auto _function : functionStruct.functionTables){
                functionDetailsMap[_function.functionName] = FunctionDetailsTable(_function);
                vector <string> code = _function.code;
                for(auto i : code)
                    cout<<i<<endl;
                cout<<endl;

                // deadCodeRemoval should be at function level
                deadCodeRemoval(code, _function.functionName);
               
            }
        
        }
        else
            cout<<"No function exists for File"<<endl;
    }

    showCallerCalllee();
    removeUnessentialFunction();
    printFunctionDetails();
    
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
    // codeGenerator();
    return EXIT_SUCCESS;
}