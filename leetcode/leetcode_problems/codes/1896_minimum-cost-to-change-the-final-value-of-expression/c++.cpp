/*
 * Problem: Minimum Cost to Change the Final Value of Expression
 * Difficulty: Hard
 * Tags: string, tree, dp, math, stack
 * 
 * Approach: Parse expression tree, DP to track min cost to flip value
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperationsToFlip(string expression) {
        vector<char> ops;
        stack<char> st;
        
        for (char c : expression) {
            if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    ops.push_back(st.top());
                    st.pop();
                }
                st.pop();
            } else if (c == '&' || c == '|') {
                while (!st.empty() && (st.top() == '&' || st.top() == '|')) {
                    ops.push_back(st.top());
                    st.pop();
                }
                st.push(c);
            } else {
                ops.push_back(c);
            }
        }
        
        while (!st.empty()) {
            ops.push_back(st.top());
            st.pop();
        }
        
        stack<pair<int, int>> evalStack;
        
        for (char op : ops) {
            if (op == '&') {
                auto b = evalStack.top(); evalStack.pop();
                auto a = evalStack.top(); evalStack.pop();
                
                if (a.first == 1 && b.first == 1) {
                    evalStack.push({1, min(a.second, b.second) + 1});
                } else if (a.first == 0 && b.first == 0) {
                    evalStack.push({0, min(a.second, b.second) + 1});
                } else {
                    evalStack.push({0, 1});
                }
            } else if (op == '|') {
                auto b = evalStack.top(); evalStack.pop();
                auto a = evalStack.top(); evalStack.pop();
                
                if (a.first == 1 && b.first == 1) {
                    evalStack.push({1, 1});
                } else if (a.first == 0 && b.first == 0) {
                    evalStack.push({0, min(a.second, b.second) + 1});
                } else {
                    evalStack.push({1, min(a.second, b.second) + 1});
                }
            } else {
                int val = op - '0';
                evalStack.push({val, 1});
            }
        }
        
        return evalStack.top().second;
    }
};