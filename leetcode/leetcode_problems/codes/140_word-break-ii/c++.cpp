/*
 * Problem: Word Break II
 * Difficulty: Hard
 * Tags: array, string, dp, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_map<int, vector<string>> memo;
    
    vector<string> backtrack(const string& s, int start, const unordered_set<string>& wordSet) {
        if (memo.find(start) != memo.end()) {
            return memo[start];
        }
        
        vector<string> result;
        if (start == s.length()) {
            result.push_back("");
            return result;
        }
        
        for (int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            if (wordSet.find(word) != wordSet.end()) {
                vector<string> sentences = backtrack(s, end, wordSet);
                for (const string& sentence : sentences) {
                    if (sentence.empty()) {
                        result.push_back(word);
                    } else {
                        result.push_back(word + " " + sentence);
                    }
                }
            }
        }
        
        memo[start] = result;
        return result;
    }
    
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return backtrack(s, 0, wordSet);
    }
};