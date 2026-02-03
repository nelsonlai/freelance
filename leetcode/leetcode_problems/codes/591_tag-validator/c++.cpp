/*
 * Problem: Tag Validator
 * Difficulty: Hard
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <stack>
#include <regex>

using namespace std;

class Solution {
public:
    bool isValid(string code) {
        if (code.empty() || code[0] != '<' || code.back() != '>') {
            return false;
        }
        
        stack<string> st;
        int i = 0;
        
        while (i < code.length()) {
            if (i > 0 && st.empty()) {
                return false;
            }
            
            if (code.substr(i, 9) == "<![CDATA[") {
                size_t pos = code.find("]]>", i + 9);
                if (pos == string::npos) {
                    return false;
                }
                i = pos + 3;
            } else if (code.substr(i, 2) == "</") {
                size_t pos = code.find(">", i + 2);
                if (pos == string::npos) {
                    return false;
                }
                string tag = code.substr(i + 2, pos - i - 2);
                if (st.empty() || st.top() != tag) {
                    return false;
                }
                st.pop();
                i = pos + 1;
            } else if (code[i] == '<') {
                size_t pos = code.find(">", i + 1);
                if (pos == string::npos) {
                    return false;
                }
                string tag = code.substr(i + 1, pos - i - 1);
                if (tag.empty() || tag.length() > 9) {
                    return false;
                }
                for (char c : tag) {
                    if (!isupper(c)) {
                        return false;
                    }
                }
                st.push(tag);
                i = pos + 1;
            } else {
                i++;
            }
        }
        
        return st.empty();
    }
};