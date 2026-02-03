/*
 * Problem: Minimum Moves to Equal Array Elements
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int minVal = *min_element(nums.begin(), nums.end());
        return sum - minVal * nums.size();
    }
};