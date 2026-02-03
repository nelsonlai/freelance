/*
 * Problem: Minimum Window Substring
 * Difficulty: Hard
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) {
            return "";
        }
        
        unordered_map<char, int> need;
        for (char c : t) {
            need[c]++;
        }
        
        unordered_map<char, int> window;
        int left = 0;
        int valid = 0;
        int start = 0;
        int minLen = INT_MAX;
        
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }
            
            while (valid == need.size()) {
                if (right - left + 1 < minLen) {
                    start = left;
                    minLen = right - left + 1;
                }
                
                char d = s[left];
                if (need.count(d)) {
                    if (window[d] == need[d]) {
                        valid--;
                    }
                    window[d]--;
                }
                left++;
            }
        }
        
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};