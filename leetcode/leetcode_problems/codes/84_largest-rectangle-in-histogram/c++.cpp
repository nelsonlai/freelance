/*
 * Problem: Largest Rectangle in Histogram
 * Difficulty: Hard
 * Tags: array, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        
        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        
        while (!st.empty()) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? heights.size() : heights.size() - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        
        return maxArea;
    }
};