/*
 * Problem: Word Pattern
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        
        if (pattern.length() != words.size()) {
            return false;
        }
        
        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;
        
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            string w = words[i];
            
            if (charToWord.find(c) != charToWord.end()) {
                if (charToWord[c] != w) {
                    return false;
                }
            } else {
                if (wordToChar.find(w) != wordToChar.end()) {
                    return false;
                }
                charToWord[c] = w;
                wordToChar[w] = c;
            }
        }
        
        return true;
    }
};