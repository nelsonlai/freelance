/*
 * Problem: Check if Word Equals Summation of Two Words
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Convert words to numbers, check if sum equals target
 * Time Complexity: O(n) where n is max word length
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
private:
    int wordToNum(string word) {
        string numStr;
        for (char c : word) {
            numStr += to_string(c - 'a');
        }
        return stoi(numStr);
    }
    
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        return wordToNum(firstWord) + wordToNum(secondWord) == wordToNum(targetWord);
    }
};