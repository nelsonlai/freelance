/*
 * Problem: Verify Preorder Sequence in Binary Search Tree
 * Difficulty: Medium
 * Tags: array, tree, search, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> st;
        int lowerBound = INT_MIN;
        
        for (int val : preorder) {
            if (val < lowerBound) {
                return false;
            }
            
            while (!st.empty() && val > st.top()) {
                lowerBound = st.top();
                st.pop();
            }
            
            st.push(val);
        }
        
        return true;
    }
};