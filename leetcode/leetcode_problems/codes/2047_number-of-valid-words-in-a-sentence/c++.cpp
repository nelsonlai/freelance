/*
 * Problem: Number of Valid Words in a Sentence
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Check each word against validation rules
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Solution {
private:
    bool isValid(const string& word) {
        // Check for digits
        for (char c : word) {
            if (isdigit(c)) {
                return false;
            }
        }
        
        // Count hyphens and punctuation
        int hyphenCount = 0;
        int punctCount = 0;
        for (char c : word) {
            if (c == '-') hyphenCount++;
            if (c == '!' || c == '.' || c == ',') punctCount++;
        }
        
        if (hyphenCount > 1 || punctCount > 1) {
            return false;
        }
        
        // Hyphen must be between letters
        size_t hyphenIdx = word.find('-');
        if (hyphenIdx != string::npos) {
            if (hyphenIdx == 0 || hyphenIdx == word.length() - 1) {
                return false;
            }
            if (!isalpha(word[hyphenIdx - 1]) || !isalpha(word[hyphenIdx + 1])) {
                return false;
            }
        }
        
        // Punctuation must be at the end
        for (char c : {'!', '.', ','}) {
            size_t idx = word.find(c);
            if (idx != string::npos && idx != word.length() - 1) {
                return false;
            }
        }
        
        return true;
    }
    
public:
    int countValidWords(string sentence) {
        stringstream ss(sentence);
        string word;
        int count = 0;
        
        while (ss >> word) {
            if (isValid(word)) {
                count++;
            }
        }
        
        return count;
    }
};