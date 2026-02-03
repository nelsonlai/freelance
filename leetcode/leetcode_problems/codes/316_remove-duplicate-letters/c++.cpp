/*
 * Problem: Remove Duplicate Letters
 * Difficulty: Medium
 * Tags: string, graph, greedy, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        vector<bool> seen(26, false);
        stack<char> st;
        
        for (char c : s) {
            count[c - 'a']--;
            if (seen[c - 'a']) {
                continue;
            }
            
            while (!st.empty() && st.top() > c && count[st.top() - 'a'] > 0) {
                seen[st.top() - 'a'] = false;
                st.pop();
            }
            
            st.push(c);
            seen[c - 'a'] = true;
        }
        
        string result;
        while (!st.empty()) {
            result = st.top() + result;
            st.pop();
        }
        return result;
    }
};