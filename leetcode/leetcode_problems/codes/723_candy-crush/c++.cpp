#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        bool stable = false;
        
        while (!stable) {
            stable = true;
            unordered_set<string> toCrush;
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == 0) continue;
                    if (j < n - 2 && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2]) {
                        toCrush.insert(to_string(i) + "," + to_string(j));
                        toCrush.insert(to_string(i) + "," + to_string(j+1));
                        toCrush.insert(to_string(i) + "," + to_string(j+2));
                    }
                    if (i < m - 2 && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j]) {
                        toCrush.insert(to_string(i) + "," + to_string(j));
                        toCrush.insert(to_string(i+1) + "," + to_string(j));
                        toCrush.insert(to_string(i+2) + "," + to_string(j));
                    }
                }
            }
            
            if (!toCrush.empty()) {
                stable = false;
                for (string pos : toCrush) {
                    size_t comma = pos.find(',');
                    int i = stoi(pos.substr(0, comma));
                    int j = stoi(pos.substr(comma + 1));
                    board[i][j] = 0;
                }
            }
            
            for (int j = 0; j < n; j++) {
                int write = m - 1;
                for (int i = m - 1; i >= 0; i--) {
                    if (board[i][j] != 0) {
                        board[write][j] = board[i][j];
                        write--;
                    }
                }
                for (int i = write; i >= 0; i--) {
                    board[i][j] = 0;
                }
            }
        }
        
        return board;
    }
};
