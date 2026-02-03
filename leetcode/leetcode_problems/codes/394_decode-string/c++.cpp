/*
 * Problem: Decode String
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
    string decodeString(string s) {
        stack<string> stringStack;
        stack<int> numStack;
        string currentString = "";
        int currentNum = 0;
        
        for (char c : s) {
            if (isdigit(c)) {
                currentNum = currentNum * 10 + (c - '0');
            } else if (c == '[') {
                stringStack.push(currentString);
                numStack.push(currentNum);
                currentString = "";
                currentNum = 0;
            } else if (c == ']') {
                string prevString = stringStack.top();
                stringStack.pop();
                int num = numStack.top();
                numStack.pop();
                for (int i = 0; i < num; i++) {
                    prevString += currentString;
                }
                currentString = prevString;
            } else {
                currentString += c;
            }
        }
        
        return currentString;
    }
};