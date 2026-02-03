/*
 * Problem: Unique Substrings in Wraparound String
 * Difficulty: Medium
 * Tags: string, tree, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findSubstringInWraproundString(string s) {
        if (s.empty()) {
            return 0;
        }
        
        unordered_map<char, int> count;
        int length = 1;
        
        for (int i = 0; i < s.length(); i++) {
            if (i > 0 && (s[i] - s[i-1] == 1 || (s[i-1] == 'z' && s[i] == 'a'))) {
                length++;
            } else {
                length = 1;
            }
            
            count[s[i]] = max(count[s[i]], length);
        }
        
        int result = 0;
        for (auto& entry : count) {
            result += entry.second;
        }
        return result;
    }
};