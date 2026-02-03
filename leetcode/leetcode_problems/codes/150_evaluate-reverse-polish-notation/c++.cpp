/*
 * Problem: Evaluate Reverse Polish Notation
 * Difficulty: Medium
 * Tags: array, string, math, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = st.top();
                st.pop();
                int a = st.top();
                st.pop();
                
                if (token == "+") {
                    st.push(a + b);
                } else if (token == "-") {
                    st.push(a - b);
                } else if (token == "*") {
                    st.push(a * b);
                } else {
                    st.push(a / b);
                }
            } else {
                st.push(stoi(token));
            }
        }
        
        return st.top();
    }
};