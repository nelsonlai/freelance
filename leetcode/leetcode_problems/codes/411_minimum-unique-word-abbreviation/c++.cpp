/*
 * Problem: Minimum Unique Word Abbreviation
 * Difficulty: Hard
 * Tags: array, string, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
private:
    string getAbbr(string& word, int mask) {
        string abbr = "";
        int count = 0;
        for (int i = 0; i < word.length(); i++) {
            if (mask & (1 << i)) {
                if (count > 0) {
                    abbr += to_string(count);
                    count = 0;
                }
                abbr += word[i];
            } else {
                count++;
            }
        }
        if (count > 0) {
            abbr += to_string(count);
        }
        return abbr;
    }
    
    bool isValid(string& target, int mask, vector<string>& dictionary) {
        for (string& word : dictionary) {
            if (word.length() != target.length()) continue;
            bool valid = true;
            for (int i = 0; i < target.length(); i++) {
                if (mask & (1 << i)) {
                    if (target[i] != word[i]) {
                        valid = false;
                        break;
                    }
                }
            }
            if (valid) return false;
        }
        return true;
    }

public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        int n = target.length();
        int minLen = INT_MAX;
        string result = target;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (isValid(target, mask, dictionary)) {
                string abbr = getAbbr(target, mask);
                if (abbr.length() < minLen) {
                    minLen = abbr.length();
                    result = abbr;
                }
            }
        }
        
        return result;
    }
};