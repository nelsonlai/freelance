/*
 * Problem: Count Submatrices With All Ones
 * Difficulty: Medium
 * Tags: array, dp, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            vector<int> heights(n, 0);
            for (int j = i; j < m; j++) {
                for (int k = 0; k < n; k++) {
                    if (mat[j][k] == 1) {
                        heights[k]++;
                    } else {
                        heights[k] = 0;
                    }
                }
                
                stack<int> st;
                for (int k = 0; k < n; k++) {
                    while (!st.empty() && heights[st.top()] >= heights[k]) {
                        st.pop();
                    }
                    
                    if (!st.empty()) {
                        int prev = st.top();
                        result += heights[k] * (k - prev);
                    } else {
                        result += heights[k] * (k + 1);
                    }
                    
                    st.push(k);
                }
            }
        }
        
        return result;
    }
};