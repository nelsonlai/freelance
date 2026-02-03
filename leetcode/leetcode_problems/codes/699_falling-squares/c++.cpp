/*
 * Problem: Falling Squares
 * Difficulty: Hard
 * Tags: array, tree, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> result;
        vector<vector<int>> heights;
        
        for (auto& pos : positions) {
            int left = pos[0];
            int sideLength = pos[1];
            int right = left + sideLength;
            int currentHeight = sideLength;
            
            for (auto& h : heights) {
                int prevLeft = h[0];
                int prevRight = h[1];
                int prevHeight = h[2];
                
                if (right > prevLeft && left < prevRight) {
                    currentHeight = max(currentHeight, prevHeight + sideLength);
                }
            }
            
            heights.push_back({left, right, currentHeight});
            int maxHeight = 0;
            for (auto& h : heights) {
                maxHeight = max(maxHeight, h[2]);
            }
            result.push_back(maxHeight);
        }
        
        return result;
    }
};