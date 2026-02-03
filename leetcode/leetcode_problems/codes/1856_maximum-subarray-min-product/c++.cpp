/*
 * Problem: Maximum Subarray Min-Product
 * Difficulty: Medium
 * Tags: array, stack, prefix sum
 * 
 * Approach: Use monotonic stack to find left/right boundaries, prefix sum for range sum
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        vector<int> left(n, 0);
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            left[i] = st.empty() ? 0 : st.top() + 1;
            st.push(i);
        }
        
        vector<int> right(n, n - 1);
        while (!st.empty()) st.pop();
        
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            right[i] = st.empty() ? n - 1 : st.top() - 1;
            st.push(i);
        }
        
        long long result = 0;
        for (int i = 0; i < n; i++) {
            long long total = prefix[right[i] + 1] - prefix[left[i]];
            result = max(result, (long long)nums[i] * total);
        }
        
        return result % 1000000007;
    }
};