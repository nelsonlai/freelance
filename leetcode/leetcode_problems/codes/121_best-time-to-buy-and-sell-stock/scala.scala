object Solution {
    def maxProfit(prices: Array[Int]): Int = {
        if (prices.isEmpty) {
            return 0
        }
        
        var minPrice = prices(0)
        var maxProfit = 0
        
        for (i <- 1 until prices.length) {
            maxProfit = math.max(maxProfit, prices(i) - minPrice)
            minPrice = math.min(minPrice, prices(i))
        }
        
        maxProfit
    }
}