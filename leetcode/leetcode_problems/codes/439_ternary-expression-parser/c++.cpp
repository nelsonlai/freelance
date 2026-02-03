/*
 * Problem: Ternary Expression Parser
 * Difficulty: Medium
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string parseTernary(string expression) {
        stack<char> st;
        int i = expression.length() - 1;
        
        while (i >= 0) {
            if (expression[i] == '?') {
                char condition = st.top();
                st.pop();
                char trueVal = st.top();
                st.pop();
                char falseVal = st.top();
                st.pop();
                st.push(condition == 'T' ? trueVal : falseVal);
                i--;
            } else if (expression[i] != ':') {
                st.push(expression[i]);
            }
            i--;
        }
        
        return string(1, st.top());
    }
};