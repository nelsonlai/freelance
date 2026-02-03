/*
 * Problem: Basic Calculator II
 * Difficulty: Medium
 * Tags: string, math, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <stack>
#include <cctype>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int num = 0;
        char sign = '+';
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            
            if ((c != ' ' && !isdigit(c)) || i == s.length() - 1) {
                if (sign == '+') {
                    st.push(num);
                } else if (sign == '-') {
                    st.push(-num);
                } else if (sign == '*') {
                    int top = st.top();
                    st.pop();
                    st.push(top * num);
                } else if (sign == '/') {
                    int top = st.top();
                    st.pop();
                    st.push(top / num);
                }
                sign = c;
                num = 0;
            }
        }
        
        int result = 0;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        return result;
    }
};