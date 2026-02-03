/*
 * Problem: Valid Sudoku
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_set>
#include <string>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<string> seen;
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    char num = board[i][j];
                    string rowKey = "row-" + to_string(i) + "-" + num;
                    string colKey = "col-" + to_string(j) + "-" + num;
                    string boxKey = "box-" + to_string(i / 3) + "-" + to_string(j / 3) + "-" + num;
                    
                    if (seen.find(rowKey) != seen.end() || 
                        seen.find(colKey) != seen.end() || 
                        seen.find(boxKey) != seen.end()) {
                        return false;
                    }
                    
                    seen.insert(rowKey);
                    seen.insert(colKey);
                    seen.insert(boxKey);
                }
            }
        }
        
        return true;
    }
};