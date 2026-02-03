/*
 * Problem: Redistribute Characters to Make All Strings Equal
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Count all characters, check if divisible by number of words
 * Time Complexity: O(n * m) where n is words, m is avg length
 * Space Complexity: O(1) - fixed 26 characters
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool makeEqual(vector<string>& words) {
        int count[26] = {0};
        for (string& word : words) {
            for (char c : word) {
                count[c - 'a']++;
            }
        }
        
        int n = words.size();
        for (int i = 0; i < 26; i++) {
            if (count[i] % n != 0) {
                return false;
            }
        }
        
        return true;
    }
};