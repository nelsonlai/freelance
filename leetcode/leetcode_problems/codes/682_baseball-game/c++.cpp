/*
 * Problem: Baseball Game
 * Difficulty: Easy
 * Tags: array, string, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        
        for (string op : operations) {
            if (op == "C") {
                st.pop();
            } else if (op == "D") {
                st.push(st.top() * 2);
            } else if (op == "+") {
                int top = st.top();
                st.pop();
                int newTop = top + st.top();
                st.push(top);
                st.push(newTop);
            } else {
                st.push(stoi(op));
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