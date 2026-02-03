/*
 * Problem: Minimum Cost to Separate Sentence Into Rows
 * Difficulty: Medium
 * Tags: array, string, dp
 * 
 * Approach: DP - minimize cost of splitting sentence into rows with max width k
 * Time Complexity: O(n^2) where n is number of words
 * Space Complexity: O(n)
 */

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumCost(string sentence, int k) {
        vector<string> words;
        stringstream ss(sentence);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        
        int n = words.size();
        // dp[i] = minimum cost to split words[i:]
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[n] = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int length = 0;
            for (int j = i; j < n; j++) {
                if (j > i) {
                    length += 1;  // space
                }
                length += words[j].length();
                
                if (length > k) {
                    break;
                }
                
                // Cost is (k - length)^2
                long long cost = (long long)(k - length) * (k - length);
                if (dp[j + 1] != LLONG_MAX) {
                    dp[i] = min(dp[i], cost + dp[j + 1]);
                }
            }
        }
        
        return (int) dp[0];
    }
};