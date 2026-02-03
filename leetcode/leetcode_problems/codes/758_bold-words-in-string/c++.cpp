#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string boldWords(vector<string>& words, string s) {
        int n = s.length();
        vector<bool> bold(n, false);
        
        for (string word : words) {
            size_t start = 0;
            while (true) {
                size_t idx = s.find(word, start);
                if (idx == string::npos) break;
                for (int i = idx; i < idx + word.length(); i++) {
                    bold[i] = true;
                }
                start = idx + 1;
            }
        }
        
        string result = "";
        for (int i = 0; i < n; i++) {
            if (bold[i] && (i == 0 || !bold[i - 1])) {
                result += "<b>";
            }
            result += s[i];
            if (bold[i] && (i == n - 1 || !bold[i + 1])) {
                result += "</b>";
            }
        }
        
        return result;
    }
};
