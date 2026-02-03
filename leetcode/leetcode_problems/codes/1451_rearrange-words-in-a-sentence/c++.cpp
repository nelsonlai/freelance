/*
 * Problem: Rearrange Words in a Sentence
 * Difficulty: Medium
 * Tags: string, sort
 * 
 * Approach: Split, sort by length, capitalize first word, lowercase rest
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for words list
 */

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
public:
    string arrangeWords(string text) {
        vector<string> words;
        stringstream ss(text);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });
        
        string result = "";
        for (int i = 0; i < words.size(); i++) {
            if (i > 0) result += " ";
            if (i == 0) {
                words[i][0] = toupper(words[i][0]);
            } else {
                for (char& c : words[i]) {
                    c = tolower(c);
                }
            }
            result += words[i];
        }
        
        return result;
    }
};