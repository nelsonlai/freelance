/*
 * Problem: Longest Substring with At Most K Distinct Characters
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
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) {
            return 0;
        }
        
        unordered_map<char, int> charCount;
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            charCount[s[right]]++;
            
            while (charCount.size() > k) {
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