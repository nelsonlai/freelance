/*
 * Problem: Best Time to Buy and Sell Stock
 * Difficulty: Easy
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) {
        return 0;
    }
    
    int minPrice = prices[0];
    int maxProfit = 0;
    
    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] - minPrice > maxProfit) {
            maxProfit = prices[i] - minPrice;
        }
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        }
    }
    
    return maxProfit;
}