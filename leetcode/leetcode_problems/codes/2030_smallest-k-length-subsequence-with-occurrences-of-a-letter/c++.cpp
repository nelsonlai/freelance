/*
 * Problem: Smallest K-Length Subsequence With Occurrences of a Letter
 * Difficulty: Hard
 * Tags: string, graph, greedy, stack
 * 
 * Approach: Greedy with stack - maintain smallest lexicographic subsequence while ensuring letter count
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        int n = s.length();
        // Count remaining occurrences of letter after each position
        vector<int> letterCount(n);
        int count = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == letter) {
                count++;
            }
            letterCount[i] = count;
        }
        
        stack<char> st;
        int letterUsed = 0;  // Count of letter used in stack
        
        for (int i = 0; i < n; i++) {
            char c = s[i];
            // Pop if we can maintain k-length and letter requirement
            while (!st.empty() && st.top() > c) {
                // Check if we can still form valid subsequence after popping
                int remainingChars = n - i;
                int remainingLetters = letterCount[i];
                int stackSize = st.size();
                
                // After popping, we need: (k - stackSize) chars and (repetition - letterUsed) letters
                if (stackSize + remainingChars >= k && letterUsed + remainingLetters >= repetition) {
                    char popped = st.top();
                    st.pop();
                    if (popped == letter) {
                        letterUsed--;
                    }
                } else {
                    break;
                }
            }
            
            // Add current character if we have space
            if (st.size() < k) {
                st.push(c);
                if (c == letter) {
                    letterUsed++;
                }
            } else {
                // Replace if current is smaller and we can maintain requirements
                if (!st.empty() && st.top() > c) {
                    char popped = st.top();
                    st.pop();
                    if (popped == letter) {
                        letterUsed--;
                    }
                    st.push(c);
                    if (c == letter) {
                        letterUsed++;
                    }
                }
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