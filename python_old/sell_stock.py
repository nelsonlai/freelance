def maxProfit(prices: list[int]) -> int:
    min_price = float('inf')
    max_profit = 0

    for i, price in enumerate(prices):
        if price < min_price:
            min_price = price
            print(f"Day {i}: New minimum price found: {min_price}")
        else:
            profit = price - min_price
            print(f"Day {i}: Selling at {price} with min price {min_price} → profit = {profit}")
            if profit > max_profit:
                max_profit = profit
                print(f"Day {i}: New max profit updated to: {max_profit}")

    print(f"Final maximum profit: {max_profit}")
    return max_profit

if __name__ == "__main__":
    print(maxProfit([8,2,1,5,9,3,6,4,7]))