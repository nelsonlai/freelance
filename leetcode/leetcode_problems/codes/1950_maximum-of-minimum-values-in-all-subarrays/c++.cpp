/*
 * Problem: Maximum of Minimum Values in All Subarrays
 * Difficulty: Medium
 * Tags: array, stack, monotonic stack
 * 
 * Approach: For each element, find range where it's minimum, update result for that length
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findMaximums(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 0);
        vector<int> left(n, -1);
        vector<int> right(n, n);
        stack<int> st;
        
        // Find left boundaries
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                left[i] = st.top();
            }
            st.push(i);
        }
        
        while (!st.empty()) st.pop();
        // Find right boundaries
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                right[i] = st.top();
            }
            st.push(i);
        }
        
        // Update result
        for (int i = 0; i < n; i++) {
            int length = right[i] - left[i] - 1;
            result[length - 1] = max(result[length - 1], nums[i]);
        }
        
        // Fill gaps
        for (int i = n - 2; i >= 0; i--) {
            result[i] = max(result[i], result[i + 1]);
        }
        
        return result;
    }
};