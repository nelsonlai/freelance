/*
 * Problem: Generalized Abbreviation
 * Difficulty: Medium
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void backtrack(string& word, int index, string current, int count, vector<string>& result) {
        if (index == word.length()) {
            if (count > 0) {
                current += to_string(count);
            }
            result.push_back(current);
            return;
        }
        
        backtrack(word, index + 1, current, count + 1, result);
        
        if (count > 0) {
            backtrack(word, index + 1, current + to_string(count) + word[index], 0, result);
        } else {
            backtrack(word, index + 1, current + word[index], 0, result);
        }
    }

public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        backtrack(word, 0, "", 0, result);
        return result;
    }
};