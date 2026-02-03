/*
 * Problem: Longest Subsequence Repeated k Times
 * Difficulty: Hard
 * Tags: string, graph, greedy, backtracking
 * 
 * Approach: Generate candidate subsequences, check if they appear k times
 * Time Complexity: O(26^L * n) where L is length of subsequence
 * Space Complexity: O(L)
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    string result = "";
    
    bool isSubsequence(string& s, string& subseq, int k) {
        // Check if subseq appears k times in s
        int occurrences = 0;
        int i = 0;
        
        while (i < s.length() && occurrences < k) {
            int j = 0;
            int start = i;
            while (start < s.length() && j < subseq.length()) {
                if (s[start] == subseq[j]) {
                    j++;
                }
                start++;
            }
            if (j == subseq.length()) {
                occurrences++;
                i = start;
            } else {
                i++;
            }
        }
        
        return occurrences >= k;
    }
    
    void backtrack(string& s, int k, string current, vector<char>& remainingChars) {
        if (current.length() > result.length() && isSubsequence(s, current, k)) {
            result = current;
        }
        
        if (current.length() >= s.length() / k) {
            return;
        }
        
        // Try adding each remaining character
        for (char c : remainingChars) {
            backtrack(s, k, current + c, remainingChars);
        }
    }
    
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        // Count character frequencies
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        // Only consider characters that appear at least k times
        vector<char> candidates;
        for (auto& [c, freq] : count) {
            if (freq >= k) {
                candidates.push_back(c);
            }
        }
        sort(candidates.begin(), candidates.end());
        
        // Try all possible subsequences of increasing length
        backtrack(s, k, "", candidates);
        
        return result;
    }
};