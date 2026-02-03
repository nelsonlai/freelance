// Problem: Best Time to Buy and Sell Stock
// Difficulty: Easy
// Tags: array, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        if prices.is_empty() {
            return 0;
        }
        
        let mut min_price = prices[0];
        let mut max_profit = 0;
        
        for &price in prices.iter().skip(1) {
            max_profit = max_profit.max(price - min_price);
            min_price = min_price.min(price);
        }
        
        max_profit
    }
}