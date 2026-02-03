/*
 * Problem: Sparse Matrix Multiplication
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int m = mat1.size();
        int k = mat1[0].size();
        int n = mat2[0].size();
        
        unordered_map<int, unordered_map<int, int>> sparse1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < k; j++) {
                if (mat1[i][j] != 0) {
                    sparse1[i][j] = mat1[i][j];
                }
            }
        }
        
        unordered_map<int, unordered_map<int, int>> sparse2;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) {
                if (mat2[i][j] != 0) {
                    sparse2[i][j] = mat2[i][j];
                }
            }
        }
        
        vector<vector<int>> result(m, vector<int>(n, 0));
        for (auto& [i, row] : sparse1) {
            for (auto& [j, val1] : row) {
                if (sparse2.find(j) != sparse2.end()) {
                    for (auto& [l, val2] : sparse2[j]) {
                        result[i][l] += val1 * val2;
                    }
                }
            }
        }
        
        return result;
    }
};