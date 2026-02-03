/*
 * Problem: Reshape the Matrix
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size(), n = mat[0].size();
        if (m * n != r * c) {
            return mat;
        }
        
        vector<int> flat;
        for (auto& row : mat) {
            for (int num : row) {
                flat.push_back(num);
            }
        }
        
        vector<vector<int>> result(r, vector<int>(c));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                result[i][j] = flat[i * c + j];
            }
        }
        
        return result;
    }
};