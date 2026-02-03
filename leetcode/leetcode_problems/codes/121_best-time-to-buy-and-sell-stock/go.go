// Problem: Best Time to Buy and Sell Stock
// Difficulty: Easy
// Tags: array, dp
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) or O(n * m) for DP table

func maxProfit(prices []int) int {
    if len(prices) == 0 {
        return 0
    }
    
    minPrice := prices[0]
    maxProfit := 0
    
    for i := 1; i < len(prices); i++ {
        if prices[i]-minPrice > maxProfit {
            maxProfit = prices[i] - minPrice
        }
        if prices[i] < minPrice {
            minPrice = prices[i]
        }
    }
    
    return maxProfit
}