/*
 * Problem: 132 Pattern
 * Difficulty: Medium
 * Tags: array, search, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        stack<int> st;
        int third = INT_MIN;
        
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] < third) {
                return true;
            }
            while (!st.empty() && st.top() < nums[i]) {
                third = st.top();
                st.pop();
            }
            st.push(nums[i]);
        }
        
        return false;
    }
};