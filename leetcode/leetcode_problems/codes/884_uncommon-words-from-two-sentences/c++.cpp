#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> count;
        stringstream ss1(s1), ss2(s2);
        string word;
        
        while (ss1 >> word) {
            count[word]++;
        }
        while (ss2 >> word) {
            count[word]++;
        }
        
        vector<string> result;
        for (auto& entry : count) {
            if (entry.second == 1) {
                result.push_back(entry.first);
            }
        }
        return result;
    }
};
