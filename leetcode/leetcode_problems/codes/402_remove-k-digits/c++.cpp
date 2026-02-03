/*
 * Problem: Remove K Digits
 * Difficulty: Medium
 * Tags: string, greedy, stack
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
    string removeKdigits(string num, int k) {
        stack<char> st;
        
        for (char digit : num) {
            while (!st.empty() && k > 0 && st.top() > digit) {
                st.pop();
                k--;
            }
            st.push(digit);
        }
        
        while (k > 0) {
            st.pop();
            k--;
        }
        
        string result = "";
        while (!st.empty()) {
            result = st.top() + result;
            st.pop();
        }
        
        while (result.length() > 0 && result[0] == '0') {
            result.erase(0, 1);
        }
        
        return result.empty() ? "0" : result;
    }
};