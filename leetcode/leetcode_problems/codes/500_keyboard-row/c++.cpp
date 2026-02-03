/*
 * Problem: Keyboard Row
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        unordered_set<char> row1 = {'q','w','e','r','t','y','u','i','o','p'};
        unordered_set<char> row2 = {'a','s','d','f','g','h','j','k','l'};
        unordered_set<char> row3 = {'z','x','c','v','b','n','m'};
        vector<unordered_set<char>> rows = {row1, row2, row3};
        
        vector<string> result;
        for (string word : words) {
            string wordLower = word;
            transform(wordLower.begin(), wordLower.end(), wordLower.begin(), ::tolower);
            
            for (auto& row : rows) {
                bool valid = true;
                for (char c : wordLower) {
                    if (row.find(c) == row.end()) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    result.push_back(word);
                    break;
                }
            }
        }
        
        return result;
    }
};