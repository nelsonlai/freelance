/*
 * Problem: Cyclically Rotating a Grid
 * Difficulty: Medium
 * Tags: array, simulation
 * 
 * Approach: Extract each layer, rotate, put back
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> result(m, vector<int>(n));
        
        int layers = min(m, n) / 2;
        
        for (int layer = 0; layer < layers; layer++) {
            vector<int> elements;
            
            // Extract layer
            for (int j = layer; j < n - layer; j++) {
                elements.push_back(grid[layer][j]);
            }
            for (int i = layer + 1; i < m - layer; i++) {
                elements.push_back(grid[i][n - 1 - layer]);
            }
            for (int j = n - 2 - layer; j >= layer; j--) {
                elements.push_back(grid[m - 1 - layer][j]);
            }
            for (int i = m - 2 - layer; i > layer; i--) {
                elements.push_back(grid[i][layer]);
            }
            
            // Rotate
            int rot = k % elements.size();
            rotate(elements.begin(), elements.begin() + (elements.size() - rot), elements.end());
            
            // Put back
            int idx = 0;
            for (int j = layer; j < n - layer; j++) {
                result[layer][j] = elements[idx++];
            }
            for (int i = layer + 1; i < m - layer; i++) {
                result[i][n - 1 - layer] = elements[idx++];
            }
            for (int j = n - 2 - layer; j >= layer; j--) {
                result[m - 1 - layer][j] = elements[idx++];
            }
            for (int i = m - 2 - layer; i > layer; i--) {
                result[i][layer] = elements[idx++];
            }
        }
        
        return result;
    }
};