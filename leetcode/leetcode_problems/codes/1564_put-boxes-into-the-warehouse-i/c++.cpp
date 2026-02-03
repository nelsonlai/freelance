/*
 * Problem: Put Boxes Into the Warehouse I
 * Difficulty: Medium
 * Tags: array, greedy, sort, stack
 * 
 * Approach: Sort boxes, use greedy - try to place largest boxes first, track warehouse heights
 * Time Complexity: O(n log n + m) where n is boxes, m is warehouse
 * Space Complexity: O(m) for effective heights
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(boxes.begin(), boxes.end());
        int m = warehouse.size();
        vector<int> effectiveHeights(m);
        effectiveHeights[0] = warehouse[0];
        
        for (int i = 1; i < m; i++) {
            effectiveHeights[i] = min(effectiveHeights[i - 1], warehouse[i]);
        }
        
        int count = 0;
        int boxIdx = boxes.size() - 1;
        
        for (int i = m - 1; i >= 0 && boxIdx >= 0; i--) {
            if (boxes[boxIdx] <= effectiveHeights[i]) {
                count++;
                boxIdx--;
            }
        }
        
        return count;
    }
};