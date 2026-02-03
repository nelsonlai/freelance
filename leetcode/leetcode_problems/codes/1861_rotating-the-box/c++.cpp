/*
 * Problem: Rotating the Box
 * Difficulty: Medium
 * Tags: array, simulation
 * 
 * Approach: First apply gravity (stones fall), then rotate 90 degrees
 * Time Complexity: O(n * m) where n, m are dimensions
 * Space Complexity: O(n * m)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();
        
        // Apply gravity: stones fall down
        for (int j = 0; j < n; j++) {
            int writePos = m - 1;
            for (int i = m - 1; i >= 0; i--) {
                if (boxGrid[i][j] == '*') {
                    writePos = i - 1;
                } else if (boxGrid[i][j] == '#') {
                    if (writePos != i) {
                        boxGrid[writePos][j] = '#';
                        boxGrid[i][j] = '.';
                    }
                    writePos--;
                }
            }
        }
        
        // Rotate 90 degrees clockwise
        vector<vector<char>> result(n, vector<char>(m));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[j][m - 1 - i] = boxGrid[i][j];
            }
        }
        
        return result;
    }
};