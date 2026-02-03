/*
 * Problem: Count Vowel Substrings of a String
 * Difficulty: Easy
 * Tags: string, hash, sliding window
 * 
 * Approach: Count substrings containing all 5 vowels exactly once each
 * Time Complexity: O(n^2) where n is string length
 * Space Complexity: O(1)
 */

#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countVowelSubstrings(string word) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int result = 0;
        int n = word.length();
        
        for (int i = 0; i < n; i++) {
            unordered_map<char, int> count;
            for (int j = i; j < n; j++) {
                char c = word[j];
                if (vowels.find(c) == vowels.end()) {
                    break;
                }
                count[c]++;
                if (count.size() == 5) {
                    bool allOne = true;
                    for (char v : vowels) {
                        if (count[v] != 1) {
                            allOne = false;
                            break;
                        }
                    }
                    if (allOne) {
                        result++;
                    }
                }
            }
        }
        
        return result;
    }
};