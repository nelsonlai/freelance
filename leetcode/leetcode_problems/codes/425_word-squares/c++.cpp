/*
 * Problem: Word Squares
 * Difficulty: Hard
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    void backtrack(vector<string>& square, int index, int n,
                   unordered_map<string, vector<string>>& prefixMap,
                   vector<vector<string>>& result) {
        if (index == n) {
            result.push_back(square);
            return;
        }
        
        string prefix = "";
        for (string word : square) {
            prefix += word[index];
        }
        
        vector<string> candidates = prefixMap[prefix];
        for (string word : candidates) {
            square.push_back(word);
            backtrack(square, index + 1, n, prefixMap, result);
            square.pop_back();
        }
    }

public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        int n = words[0].length();
        unordered_map<string, vector<string>> prefixMap;
        
        for (string word : words) {
            for (int i = 0; i < n; i++) {
                string prefix = word.substr(0, i + 1);
                prefixMap[prefix].push_back(word);
            }
        }
        
        vector<vector<string>> result;
        vector<string> square;
        
        for (string word : words) {
            square.push_back(word);
            backtrack(square, 1, n, prefixMap, result);
            square.pop_back();
        }
        
        return result;
    }
};