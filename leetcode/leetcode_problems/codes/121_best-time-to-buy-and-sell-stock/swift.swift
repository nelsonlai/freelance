class Solution {
    func maxProfit(_ prices: [Int]) -> Int {
        if prices.isEmpty {
            return 0
        }
        
        var minPrice = prices[0]
        var maxProfit = 0
        
        for i in 1..<prices.count {
            maxProfit = max(maxProfit, prices[i] - minPrice)
            minPrice = min(minPrice, prices[i])
        }
        
        return maxProfit
    }
}