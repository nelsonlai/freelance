/*
 * Problem: Plates Between Candles
 * Difficulty: Medium
 * Tags: array, string, prefix sum, binary search
 * 
 * Approach: Use prefix sum for plates, binary search for nearest candles
 * Time Complexity: O(n + q log n) where n is length, q is queries
 * Space Complexity: O(n)
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.length();
        // Store positions of candles
        vector<int> candles;
        // Prefix sum of plates
        vector<int> prefixPlates(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            if (s[i] == '|') {
                candles.push_back(i);
            }
            prefixPlates[i + 1] = prefixPlates[i] + (s[i] == '*' ? 1 : 0);
        }
        
        vector<int> result;
        
        for (auto& query : queries) {
            int left = query[0];
            int right = query[1];
            
            // Find first candle >= left
            int leftIdx = lower_bound(candles.begin(), candles.end(), left) - candles.begin();
            // Find last candle <= right
            int rightIdx = upper_bound(candles.begin(), candles.end(), right) - candles.begin() - 1;
            
            if (leftIdx < candles.size() && rightIdx >= leftIdx) {
                int leftCandle = candles[leftIdx];
                int rightCandle = candles[rightIdx];
                // Count plates between candles
                result.push_back(prefixPlates[rightCandle + 1] - prefixPlates[leftCandle]);
            } else {
                result.push_back(0);
            }
        }
        
        return result;
    }
};