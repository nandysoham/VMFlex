#include "driver.h"
#include "DeadCodeRemoval.h"
#include "codeGenerator.h"
#include <string>
#include "../CompFlex/helper.h"


int main(int arc, char** argv){
    parser();
    translate();
    ifstream TACFile("code.tac");

    // Check if the file is open.
    if (!TACFile.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }
    
    vector <string> inputStream;
    // Read the contents of the file line by line.
    string line;
    while (getline(TACFile, line)) {
        // Print the line to the console.
        inputStream.push_back(line);
    }

    // Close the file.
    TACFile.close();
   
    deadCodeRemoval(inputStream);
    codeGenerator();
    return EXIT_SUCCESS;
}