#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Solution {
private:
    vector<string> result;
    
    void backtrack(string& s, int i, string current) {
        if (i == s.length()) {
            result.push_back(current);
            return;
        }
        
        char c = s[i];
        if (isalpha(c)) {
            backtrack(s, i + 1, current + (char)tolower(c));
            backtrack(s, i + 1, current + (char)toupper(c));
        } else {
            backtrack(s, i + 1, current + c);
        }
    }

public:
    vector<string> letterCasePermutation(string s) {
        backtrack(s, 0, "");
        return result;
    }
};
