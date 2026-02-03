/*
 * Problem: String Matching in an Array
 * Difficulty: Easy
 * Tags: array, string, tree
 * 
 * Approach: Check if each word is substring of any other word
 * Time Complexity: O(n^2 * m) where n is words, m is average length
 * Space Complexity: O(n) for result
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> result;
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words.size(); j++) {
                if (i != j && words[j].find(words[i]) != string::npos) {
                    result.push_back(words[i]);
                    break;
                }
            }
        }
        return result;
    }
};