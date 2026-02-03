/*
 * Problem: Concatenated Words
 * Difficulty: Hard
 * Tags: array, string, dp, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    bool canForm(string word, unordered_set<string>& wordSet) {
        if (word.empty()) {
            return false;
        }
        
        vector<bool> dp(word.length() + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= word.length(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.find(word.substr(j, i - j)) != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[word.length()];
    }

public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string> wordSet(words.begin(), words.end());
        vector<string> result;
        
        for (string word : words) {
            wordSet.erase(word);
            if (canForm(word, wordSet)) {
                result.push_back(word);
            }
            wordSet.insert(word);
        }
        
        return result;
    }
};