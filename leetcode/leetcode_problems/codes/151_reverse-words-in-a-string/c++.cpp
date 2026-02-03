/*
 * Problem: Reverse Words in a String
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        stringstream ss(s);
        string word;
        vector<string> words;
        
        while (ss >> word) {
            words.push_back(word);
        }
        
        reverse(words.begin(), words.end());
        
        string result;
        for (int i = 0; i < words.size(); i++) {
            result += words[i];
            if (i < words.size() - 1) {
                result += " ";
            }
        }
        
        return result;
    }
};