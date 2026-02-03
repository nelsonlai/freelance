# @param {Integer[]} prices
# @return {Integer}
def max_profit(prices)
    return 0 if prices.empty?
    
    min_price = prices[0]
    max_profit = 0
    
    prices[1..-1].each do |price|
        max_profit = [max_profit, price - min_price].max
        min_price = [min_price, price].min
    end
    
    max_profit
end