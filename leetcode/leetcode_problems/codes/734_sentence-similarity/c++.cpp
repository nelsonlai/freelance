#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if (sentence1.size() != sentence2.size()) {
            return false;
        }
        
        unordered_map<string, unordered_set<string>> similar;
        for (auto& pair : similarPairs) {
            similar[pair[0]].insert(pair[1]);
            similar[pair[1]].insert(pair[0]);
        }
        
        for (int i = 0; i < sentence1.size(); i++) {
            if (sentence1[i] != sentence2[i] && 
                similar[sentence1[i]].find(sentence2[i]) == similar[sentence1[i]].end()) {
                return false;
            }
        }
        
        return true;
    }
};
