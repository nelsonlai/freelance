/*
 * Problem: Mini Parser
 * Difficulty: Medium
 * Tags: string, search, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) {
            return NestedInteger();
        }
        
        if (s[0] != '[') {
            return NestedInteger(stoi(s));
        }
        
        stack<NestedInteger> st;
        int num = 0;
        bool negative = false;
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == '[') {
                st.push(NestedInteger());
            } else if (c == '-') {
                negative = true;
            } else if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == ',' || c == ']') {
                if (i > 0 && isdigit(s[i - 1])) {
                    if (negative) {
                        num = -num;
                    }
                    st.top().add(NestedInteger(num));
                    num = 0;
                    negative = false;
                }
                
                if (c == ']' && st.size() > 1) {
                    NestedInteger nested = st.top();
                    st.pop();
                    st.top().add(nested);
                }
            }
        }
        
        return st.empty() ? NestedInteger() : st.top();
    }
};