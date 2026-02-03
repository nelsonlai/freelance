/*
 * Problem: Sorting the Sentence
 * Difficulty: Easy
 * Tags: string, sort
 * 
 * Approach: Split words, extract position numbers, sort and reconstruct
 * Time Complexity: O(n log n) where n is words
 * Space Complexity: O(n)
 */

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string sortSentence(string s) {
        vector<string> words;
        stringstream ss(s);
        string word;
        
        while (ss >> word) {
            words.push_back(word);
        }
        
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.back() < b.back();
        });
        
        string result;
        for (int i = 0; i < words.size(); i++) {
            if (i > 0) result += " ";
            result += words[i].substr(0, words[i].length() - 1);
        }
        
        return result;
    }
};