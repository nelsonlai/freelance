/*
 * Problem: Maximum Number of Words You Can Type
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: Check each word if contains any broken letter
 * Time Complexity: O(n * m) where n is words, m is avg word length
 * Space Complexity: O(1) - fixed 26 characters
 */

#include <string>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        unordered_set<char> broken(brokenLetters.begin(), brokenLetters.end());
        
        stringstream ss(text);
        string word;
        int count = 0;
        
        while (ss >> word) {
            bool canType = true;
            for (char c : word) {
                if (broken.find(c) != broken.end()) {
                    canType = false;
                    break;
                }
            }
            if (canType) {
                count++;
            }
        }
        
        return count;
    }
};