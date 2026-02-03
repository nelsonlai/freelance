/*
 * Problem: Longest Word in Dictionary through Deleting
 * Difficulty: Medium
 * Tags: array, string, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isSubsequence(string word, string s) {
        int i = 0;
        for (char c : s) {
            if (i < word.length() && word[i] == c) {
                i++;
            }
        }
        return i == word.length();
    }

public:
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) {
                return a.length() > b.length();
            }
            return a < b;
        });
        
        for (string word : dictionary) {
            if (isSubsequence(word, s)) {
                return word;
            }
        }
        
        return "";
    }
};