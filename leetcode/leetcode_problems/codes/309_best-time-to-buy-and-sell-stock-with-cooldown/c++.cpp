/*
 * Problem: Best Time to Buy and Sell Stock with Cooldown
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        
        int hold = -prices[0];
        int sold = 0;
        int rest = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            int prevHold = hold;
            int prevSold = sold;
            hold = max(hold, rest - prices[i]);
            sold = prevHold + prices[i];
            rest = max(rest, prevSold);
        }
        
        return max(sold, rest);
    }
};