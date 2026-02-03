#include <string>

using namespace std;

class Solution {
public:
    int minAddToMakeValid(string s) {
        int openCount = 0;
        int closeCount = 0;
        
        for (char c : s) {
            if (c == '(') {
                openCount++;
            } else {
                if (openCount > 0) {
                    openCount--;
                } else {
                    closeCount++;
                }
            }
        }
        
        return openCount + closeCount;
    }
};
