/*
 * Problem: Validate Stack Sequences
 * Difficulty: Medium
 * Tags: array, stack
 * 
 * Approach: Simulate stack operations - push elements and pop when matching
 * Time Complexity: O(n)
 * Space Complexity: O(n) for stack
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> st;
        int popIdx = 0;
        
        for (int num : pushed) {
            st.push(num);
            while (!st.empty() && st.top() == popped[popIdx]) {
                st.pop();
                popIdx++;
            }
        }
        
        return st.empty();
    }
};