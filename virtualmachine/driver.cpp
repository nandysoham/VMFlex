#include "driver.h"
#include "DeadCodeRemoval.h"
#include "file2.h"
#include <string>


int main(int arc, char** argv){
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

    return EXIT_SUCCESS;
}