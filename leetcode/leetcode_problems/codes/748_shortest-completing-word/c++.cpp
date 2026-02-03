#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        unordered_map<char, int> target;
        for (char c : licensePlate) {
            if (isalpha(c)) {
                target[tolower(c)]++;
            }
        }
        
        string result = "";
        for (string word : words) {
            unordered_map<char, int> wordCount;
            for (char c : word) {
                wordCount[tolower(c)]++;
            }
            
            bool valid = true;
            for (auto& entry : target) {
                if (wordCount[entry.first] < entry.second) {
                    valid = false;
                    break;
                }
            }
            
            if (valid && (result.empty() || word.length() < result.length())) {
                result = word;
            }
        }
        
        return result;
    }
};
