/*
 * Problem: Longest Substring with At Least K Repeating Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestSubstring(string s, int k) {
        if (s.length() < k) {
            return 0;
        }
        
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        for (auto& entry : count) {
            if (entry.second < k) {
                int maxLen = 0;
                string delimiter(1, entry.first);
                size_t pos = 0;
                string token;
                string temp = s;
                while ((pos = temp.find(delimiter)) != string::npos) {
                    token = temp.substr(0, pos);
                    maxLen = max(maxLen, longestSubstring(token, k));
                    temp.erase(0, pos + delimiter.length());
                }
                if (!temp.empty()) {
                    maxLen = max(maxLen, longestSubstring(temp, k));
                }
                return maxLen;
            }
        }
        
        return s.length();
    }
};