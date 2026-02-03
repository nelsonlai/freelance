/*
 * Problem: Find a Peak Element II
 * Difficulty: Medium
 * Tags: array, search, binary search
 * 
 * Approach: Binary search on columns, find max in each column
 * Time Complexity: O(m log n) where m is rows, n is columns
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int left = 0, right = n - 1;
        
        while (left < right) {
            int mid = (left + right) / 2;
            int maxRow = 0;
            for (int i = 0; i < m; i++) {
                if (mat[i][mid] > mat[maxRow][mid]) {
                    maxRow = i;
                }
            }
            
            if (mid < n - 1 && mat[maxRow][mid] < mat[maxRow][mid + 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        int maxRow = 0;
        for (int i = 0; i < m; i++) {
            if (mat[i][left] > mat[maxRow][left]) {
                maxRow = i;
            }
        }
        
        return {maxRow, left};
    }
};