#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_set<string> bannedSet(banned.begin(), banned.end());
        unordered_map<string, int> count;
        
        string word = "";
        for (char c : paragraph) {
            if (isalpha(c)) {
                word += tolower(c);
            } else {
                if (!word.empty() && bannedSet.find(word) == bannedSet.end()) {
                    count[word]++;
                }
                word = "";
            }
        }
        if (!word.empty() && bannedSet.find(word) == bannedSet.end()) {
            count[word]++;
        }
        
        string result = "";
        int maxCount = 0;
        for (auto& entry : count) {
            if (entry.second > maxCount) {
                maxCount = entry.second;
                result = entry.first;
            }
        }
        return result;
    }
};
