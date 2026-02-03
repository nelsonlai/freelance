#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        bool inBlock = false;
        vector<string> result;
        string newline;
        
        for (string line : source) {
            int i = 0;
            if (!inBlock) {
                newline = "";
            }
            while (i < line.length()) {
                if (!inBlock && i + 1 < line.length() && line.substr(i, 2) == "/*") {
                    inBlock = true;
                    i += 2;
                } else if (inBlock && i + 1 < line.length() && line.substr(i, 2) == "*/") {
                    inBlock = false;
                    i += 2;
                } else if (!inBlock && i + 1 < line.length() && line.substr(i, 2) == "//") {
                    break;
                } else if (!inBlock) {
                    newline += line[i];
                    i++;
                } else {
                    i++;
                }
            }
            if (!inBlock && !newline.empty()) {
                result.push_back(newline);
            }
        }
        
        return result;
    }
};
