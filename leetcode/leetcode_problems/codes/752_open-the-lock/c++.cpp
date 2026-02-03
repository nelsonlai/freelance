#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());
        if (dead.find("0000") != dead.end()) {
            return -1;
        }
        
        queue<pair<string, int>> q;
        q.push({"0000", 0});
        unordered_set<string> visited;
        visited.insert("0000");
        
        while (!q.empty()) {
            auto [state, moves] = q.front();
            q.pop();
            
            if (state == target) {
                return moves;
            }
            
            for (int i = 0; i < 4; i++) {
                for (int d = -1; d <= 1; d += 2) {
                    string newState = state;
                    newState[i] = ((newState[i] - '0' + d + 10) % 10) + '0';
                    if (visited.find(newState) == visited.end() && dead.find(newState) == dead.end()) {
                        visited.insert(newState);
                        q.push({newState, moves + 1});
                    }
                }
            }
        }
        
        return -1;
    }
};
