/*
 * Problem: Letter Combinations of a Phone Number
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_map<char, string> phoneMap = {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
    };
    
    void backtrack(string& digits, int index, string& current, vector<string>& result) {
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }
        
        string letters = phoneMap[digits[index]];
        for (char letter : letters) {
            current.push_back(letter);
            backtrack(digits, index + 1, current, result);
            current.pop_back();
        }
    }
    
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.empty()) {
            return result;
        }
        
        string current;
        backtrack(digits, 0, current, result);
        return result;
    }
};