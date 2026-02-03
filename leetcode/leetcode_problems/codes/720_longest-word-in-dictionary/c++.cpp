#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        unordered_set<string> wordSet(words.begin(), words.end());
        
        string result = "";
        for (string word : words) {
            if (word.length() > result.length() || 
                (word.length() == result.length() && word < result)) {
                bool valid = true;
                for (int i = 1; i < word.length(); i++) {
                    if (wordSet.find(word.substr(0, i)) == wordSet.end()) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    result = word;
                }
            }
        }
        
        return result;
    }
};
