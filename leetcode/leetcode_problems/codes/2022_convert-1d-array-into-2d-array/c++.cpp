/*
 * Problem: Convert 1D Array Into 2D Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Check if size matches, then reshape array
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (original.size() != m * n) {
            return {};
        }
        
        vector<vector<int>> result(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = original[i * n + j];
            }
        }
        
        return result;
    }
};