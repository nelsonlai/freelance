/*
 * Problem: Palindrome Permutation
 * Difficulty: Easy
 * Tags: string, hash
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
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        int oddCount = 0;
        for (auto& pair : count) {
            if (pair.second % 2 == 1) {
                oddCount++;
            }
        }
        
        return oddCount <= 1;
    }
};