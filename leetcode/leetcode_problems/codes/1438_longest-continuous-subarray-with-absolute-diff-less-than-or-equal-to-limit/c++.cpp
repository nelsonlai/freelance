/*
 * Problem: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
 * Difficulty: Medium
 * Tags: array, queue, heap
 * 
 * Approach: Sliding window with two deques to track min and max
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(n) for deques
 */

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> minDeque;
        deque<int> maxDeque;
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            while (!minDeque.empty() && nums[minDeque.back()] >= nums[right]) {
                minDeque.pop_back();
            }
            minDeque.push_back(right);
            
            while (!maxDeque.empty() && nums[maxDeque.back()] <= nums[right]) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(right);
            
            while (nums[maxDeque.front()] - nums[minDeque.front()] > limit) {
                if (minDeque.front() == left) {
                    minDeque.pop_front();
                }
                if (maxDeque.front() == left) {
                    maxDeque.pop_front();
                }
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};