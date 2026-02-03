/*
 * Problem: Number of Visible People in a Queue
 * Difficulty: Hard
 * Tags: array, stack, monotonic stack
 * 
 * Approach: Monotonic stack - count people visible to the right
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> result(n, 0);
        stack<int> st;
        
        for (int i = n - 1; i >= 0; i--) {
            int count = 0;
            while (!st.empty() && heights[st.top()] < heights[i]) {
                st.pop();
                count++;
            }
            
            if (!st.empty()) {
                count++;
            }
            
            result[i] = count;
            st.push(i);
        }
        
        return result;
    }
};