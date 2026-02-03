/*
 * Problem: N-Queens II
 * Difficulty: Hard
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <unordered_set>
using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        unordered_set<int> cols, diag1, diag2;
        backtrack(count, 0, n, cols, diag1, diag2);
        return count;
    }
    
private:
    void backtrack(int& count, int row, int n, unordered_set<int>& cols, 
                   unordered_set<int>& diag1, unordered_set<int>& diag2) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (cols.count(col) || diag1.count(row - col) || diag2.count(row + col)) {
                continue;
            }
            
            cols.insert(col);
            diag1.insert(row - col);
            diag2.insert(row + col);
            
            backtrack(count, row + 1, n, cols, diag1, diag2);
            
            cols.erase(col);
            diag1.erase(row - col);
            diag2.erase(row + col);
        }
    }
};