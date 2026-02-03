/*
 * Problem: Put Boxes Into the Warehouse II
 * Difficulty: Medium
 * Tags: array, greedy, sort, stack
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
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(boxes.begin(), boxes.end());
        int m = warehouse.size();
        int left = 0, right = m - 1;
        int count = 0;
        int boxIdx = boxes.size() - 1;
        
        while (left <= right && boxIdx >= 0) {
            if (boxes[boxIdx] <= warehouse[left]) {
                count++;
                left++;
                boxIdx--;
            } else if (boxes[boxIdx] <= warehouse[right]) {
                count++;
                right--;
                boxIdx--;
            } else {
                boxIdx--;
            }
        }
        
        return count;
    }
};