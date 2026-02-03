/*
 * Problem: Find the Kth Largest Integer in the Array
 * Difficulty: Medium
 * Tags: array, string, sort, queue, heap
 * 
 * Approach: Sort by integer value, return k-th largest
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {
        sort(nums.begin(), nums.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) {
                return a.length() > b.length();
            }
            return a > b;
        });
        return nums[k - 1];
    }
};