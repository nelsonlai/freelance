#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<string, vector<char>> rules;
    
    bool dfs(string level) {
        if (level.length() == 1) {
            return true;
        }
        return buildNext(level, 0, "");
    }
    
    bool buildNext(string level, int i, string current) {
        if (i == level.length() - 1) {
            return dfs(current);
        }
        
        string key = level.substr(i, 2);
        if (rules.find(key) != rules.end()) {
            for (char c : rules[key]) {
                if (buildNext(level, i + 1, current + c)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (string rule : allowed) {
            rules[rule.substr(0, 2)].push_back(rule[2]);
        }
        return dfs(bottom);
    }
};
