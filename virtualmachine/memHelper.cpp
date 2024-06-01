#include "memHelper.h"
#include "Structure.h"

/**
* @brief Extracts the name information from string with ponters 
*        eg: ***var --> var
*/
string extractNameFromPointer(string s){
    int idx = 0;
    for(; idx < s.size(); idx++){
        if(s[idx] != '*')
            break;
    }
    return s.substr(idx);
}