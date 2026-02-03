/*
 * Problem: Longest Palindrome
 * Difficulty: Easy
 * Tags: string, greedy, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        int length = 0;
        bool hasOdd = false;
        
        for (auto& entry : count) {
            length += (entry.second / 2) * 2;
            if (entry.second % 2 == 1) {
                hasOdd = true;
            }
        }
        
        return length + (hasOdd ? 1 : 0);
    }
};