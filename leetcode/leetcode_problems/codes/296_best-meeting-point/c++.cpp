/*
 * Problem: Best Meeting Point
 * Difficulty: Hard
 * Tags: array, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> rows;
        vector<int> cols;
        
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
        
        sort(cols.begin(), cols.end());
        int rowMedian = rows[rows.size() / 2];
        int colMedian = cols[cols.size() / 2];
        
        int distance = 0;
        for (int row : rows) {
            distance += abs(row - rowMedian);
        }
        for (int col : cols) {
            distance += abs(col - colMedian);
        }
        
        return distance;
    }
};