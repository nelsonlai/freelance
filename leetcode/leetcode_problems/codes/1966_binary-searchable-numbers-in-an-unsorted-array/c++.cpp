/*
 * Problem: Binary Searchable Numbers in an Unsorted Array
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Number is searchable if all left are smaller and all right are larger
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int binarySearchableNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<int> maxLeft(n);
        vector<int> minRight(n);
        
        maxLeft[0] = nums[0];
        for (int i = 1; i < n; i++) {
            maxLeft[i] = max(maxLeft[i-1], nums[i]);
        }
        
        minRight[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; i--) {
            minRight[i] = min(minRight[i+1], nums[i]);
        }
        
        int count = 0;
        for (int i = 0; i < n; i++) {
            if ((i == 0 || nums[i] > maxLeft[i-1]) && 
                (i == n-1 || nums[i] < minRight[i+1])) {
                count++;
            }
        }
        
        return count;
    }
};