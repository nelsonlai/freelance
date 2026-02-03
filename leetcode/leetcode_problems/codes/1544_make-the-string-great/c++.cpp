/*
 * Problem: Make The String Great
 * Difficulty: Easy
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
    string makeGood(string s) {
        stack<char> st;
        for (char c : s) {
            if (!st.empty() && st.top() != c && 
                tolower(st.top()) == tolower(c)) {
                st.pop();
            } else {
                st.push(c);
            }
        }
        
        string result;
        while (!st.empty()) {
            result = st.top() + result;
            st.pop();
        }
        return result;
    }
};