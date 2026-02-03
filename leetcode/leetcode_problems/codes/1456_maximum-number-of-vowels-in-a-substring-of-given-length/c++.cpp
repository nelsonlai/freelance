/*
 * Problem: Maximum Number of Vowels in a Substring of Given Length
 * Difficulty: Medium
 * Tags: array, string, tree
 * 
 * Approach: Sliding window - maintain count of vowels in window of size k
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1)
 */

#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int maxCount = 0;
        int currentCount = 0;
        
        for (int i = 0; i < k; i++) {
            if (vowels.count(s[i])) {
                currentCount++;
            }
        }
        maxCount = currentCount;
        
        for (int i = k; i < s.length(); i++) {
            if (vowels.count(s[i - k])) {
                currentCount--;
            }
            if (vowels.count(s[i])) {
                currentCount++;
            }
            maxCount = max(maxCount, currentCount);
        }
        
        return maxCount;
    }
};