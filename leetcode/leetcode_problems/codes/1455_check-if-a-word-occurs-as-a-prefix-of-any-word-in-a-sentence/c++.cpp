/*
 * Problem: Check If a Word Occurs As a Prefix of Any Word in a Sentence
 * Difficulty: Easy
 * Tags: array, string, tree, search
 * 
 * Approach: Split sentence, check if searchWord is prefix of any word
 * Time Complexity: O(n * m) where n is words, m is searchWord length
 * Space Complexity: O(n) for words
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        stringstream ss(sentence);
        string word;
        int index = 1;
        
        while (ss >> word) {
            if (word.find(searchWord) == 0) {
                return index;
            }
            index++;
        }
        
        return -1;
    }
};