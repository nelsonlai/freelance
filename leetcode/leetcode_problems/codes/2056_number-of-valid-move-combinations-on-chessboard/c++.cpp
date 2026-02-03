/*
 * Problem: Number of Valid Move Combinations On Chessboard
 * Difficulty: Hard
 * Tags: array, string, backtracking, DFS
 * 
 * Approach: Generate all possible move combinations, check for collisions
 * Time Complexity: O(8^n * n^2) where n is number of pieces
 * Space Complexity: O(n)
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_map<string, vector<pair<int, int>>> directions;
    
    vector<vector<int>> getMoves(string piece, vector<int>& pos) {
        vector<vector<int>> moves;
        moves.push_back({pos[0], pos[1]});  // Can stay in place
        
        for (auto& [dx, dy] : directions[piece]) {
            for (int dist = 1; dist < 8; dist++) {
                int x = pos[0] + dx * dist;
                int y = pos[1] + dy * dist;
                if (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
                    moves.push_back({x, y});
                } else {
                    break;
                }
            }
        }
        return moves;
    }
    
    bool isValid(vector<vector<int>>& positionsAtTime) {
        unordered_set<string> seen;
        for (auto& pos : positionsAtTime) {
            string key = to_string(pos[0]) + "," + to_string(pos[1]);
            if (seen.count(key)) {
                return false;
            }
            seen.insert(key);
        }
        return true;
    }
    
    int backtrack(vector<string>& pieces, vector<vector<int>>& positions, 
                  int index, vector<vector<vector<int>>>& currentPaths) {
        if (index == pieces.size()) {
            // Check all time steps
            int maxTime = 0;
            for (auto& path : currentPaths) {
                maxTime = max(maxTime, (int)path.size());
            }
            
            for (int t = 0; t < maxTime; t++) {
                vector<vector<int>> positionsAtT;
                for (auto& path : currentPaths) {
                    if (t < path.size()) {
                        positionsAtT.push_back(path[t]);
                    } else {
                        positionsAtT.push_back(path.back());  // Stay at last position
                    }
                }
                
                if (!isValid(positionsAtT)) {
                    return 0;
                }
            }
            return 1;
        }
        
        int result = 0;
        string piece = pieces[index];
        vector<int> startPos = positions[index];
        vector<vector<int>> moves = getMoves(piece, startPos);
        
        for (auto& move : moves) {
            // Generate path from start to move
            vector<vector<int>> path;
            int dx = move[0] == startPos[0] ? 0 : (move[0] > startPos[0] ? 1 : -1);
            int dy = move[1] == startPos[1] ? 0 : (move[1] > startPos[1] ? 1 : -1);
            
            int x = startPos[0], y = startPos[1];
            while (true) {
                path.push_back({x, y});
                if (x == move[0] && y == move[1]) {
                    break;
                }
                x += dx;
                y += dy;
            }
            
            currentPaths.push_back(path);
            result += backtrack(pieces, positions, index + 1, currentPaths);
            currentPaths.pop_back();
        }
        
        return result;
    }
    
public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        directions["rook"] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        directions["queen"] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        directions["bishop"] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        
        vector<vector<vector<int>>> currentPaths;
        return backtrack(pieces, positions, 0, currentPaths);
    }
};