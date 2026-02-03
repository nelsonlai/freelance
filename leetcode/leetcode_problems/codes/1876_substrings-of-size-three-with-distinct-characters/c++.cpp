/*
 * Problem: Substrings of Size Three with Distinct Characters
 * Difficulty: Easy
 * Tags: array, string, hash, sliding window
 * 
 * Approach: Sliding window of size 3, check if all characters distinct
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int countGoodSubstrings(string s) {
        if (s.length() < 3) {
            return 0;
        }
        
        int count = 0;
        for (int i = 0; i <= (int)s.length() - 3; i++) {
            if (s[i] != s[i+1] && s[i+1] != s[i+2] && s[i] != s[i+2]) {
                count++;
            }
        }
        
        return count;
    }
};