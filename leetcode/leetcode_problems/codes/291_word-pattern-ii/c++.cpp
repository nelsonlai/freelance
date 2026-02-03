/*
 * Problem: Word Pattern II
 * Difficulty: Medium
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
private:
    bool backtrack(string& pattern, int patternIdx, string& s, int sIdx,
                  unordered_map<char, string>& charToWord, unordered_map<string, char>& wordToChar) {
        if (patternIdx == pattern.length() && sIdx == s.length()) {
            return true;
        }
        if (patternIdx == pattern.length() || sIdx == s.length()) {
            return false;
        }
        
        char c = pattern[patternIdx];
        
        if (charToWord.find(c) != charToWord.end()) {
            string word = charToWord[c];
            if (sIdx + word.length() > s.length() || s.substr(sIdx, word.length()) != word) {
                return false;
            }
            return backtrack(pattern, patternIdx + 1, s, sIdx + word.length(), charToWord, wordToChar);
        }
        
        for (int end = sIdx + 1; end <= s.length(); end++) {
            string word = s.substr(sIdx, end - sIdx);
            
            if (wordToChar.find(word) != wordToChar.end()) {
                continue;
            }
            
            charToWord[c] = word;
            wordToChar[word] = c;
            
            if (backtrack(pattern, patternIdx + 1, s, end, charToWord, wordToChar)) {
                return true;
            }
            
            charToWord.erase(c);
            wordToChar.erase(word);
        }
        
        return false;
    }

public:
    bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;
        return backtrack(pattern, 0, s, 0, charToWord, wordToChar);
    }
};