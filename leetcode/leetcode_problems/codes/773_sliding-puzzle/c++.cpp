#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target = "123450";
        string start = "";
        for (auto& row : board) {
            for (int num : row) {
                start += to_string(num);
            }
        }
        
        vector<vector<int>> neighbors = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};
        
        queue<pair<string, int>> q;
        q.push({start, 0});
        unordered_set<string> visited;
        visited.insert(start);
        
        while (!q.empty()) {
            auto [state, moves] = q.front();
            q.pop();
            
            if (state == target) {
                return moves;
            }
            
            int zeroIdx = state.find('0');
            for (int neighbor : neighbors[zeroIdx]) {
                string newState = state;
                swap(newState[zeroIdx], newState[neighbor]);
                if (visited.find(newState) == visited.end()) {
                    visited.insert(newState);
                    q.push({newState, moves + 1});
                }
            }
        }
        
        return -1;
    }
};
