/*
 * Problem: Longest Substring with At Most Two Distinct Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> charCount;
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            charCount[s[right]]++;
            
            while (charCount.size() > 2) {
                charCount[s[left]]--;
                if (charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};