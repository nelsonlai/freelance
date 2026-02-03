#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int target = n * n;
        
        queue<pair<int, int>> q;
        q.push({1, 0});
        unordered_set<int> visited;
        visited.insert(1);
        
        while (!q.empty()) {
            auto [pos, moves] = q.front();
            q.pop();
            
            if (pos == target) {
                return moves;
            }
            
            for (int i = 1; i <= 6; i++) {
                int nextPos = pos + i;
                if (nextPos > target) break;
                
                auto [r, c] = getPos(nextPos, n);
                if (board[r][c] != -1) {
                    nextPos = board[r][c];
                }
                
                if (visited.find(nextPos) == visited.end()) {
                    visited.insert(nextPos);
                    q.push({nextPos, moves + 1});
                }
            }
        }
        
        return -1;
    }
    
private:
    pair<int, int> getPos(int num, int n) {
        int row = (num - 1) / n;
        int col = (num - 1) % n;
        if (row % 2 == 1) {
            col = n - 1 - col;
        }
        row = n - 1 - row;
        return {row, col};
    }
};
