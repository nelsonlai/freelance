/*
 * Problem: Find Longest Awesome Substring
 * Difficulty: Hard
 * Tags: string, tree, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestAwesome(string s) {
        unordered_map<int, int> maskMap;
        maskMap[0] = -1;
        int mask = 0;
        int maxLen = 0;
        
        for (int i = 0; i < s.length(); i++) {
            int digit = s[i] - '0';
            mask ^= 1 << digit;
            
            if (maskMap.find(mask) != maskMap.end()) {
                maxLen = max(maxLen, i - maskMap[mask]);
            } else {
                maskMap[mask] = i;
            }
            
            for (int j = 0; j < 10; j++) {
                int tempMask = mask ^ (1 << j);
                if (maskMap.find(tempMask) != maskMap.end()) {
                    maxLen = max(maxLen, i - maskMap[tempMask]);
                }
            }
        }
        
        return maxLen;
    }
};