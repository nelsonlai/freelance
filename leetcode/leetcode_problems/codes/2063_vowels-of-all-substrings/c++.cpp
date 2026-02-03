/*
 * Problem: Vowels of All Substrings
 * Difficulty: Medium
 * Tags: string, math, combinatorics
 * 
 * Approach: For each vowel at index i, count how many substrings contain it
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(1)
 */

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    long long countVowels(string word) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int n = word.length();
        long long result = 0;
        
        for (int i = 0; i < n; i++) {
            if (vowels.find(word[i]) != vowels.end()) {
                // Number of substrings containing this vowel
                // Left choices: i + 1, Right choices: n - i
                result += (long long)(i + 1) * (n - i);
            }
        }
        
        return result;
    }
};