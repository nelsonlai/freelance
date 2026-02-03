/**
 * Problem: Stock Price Fluctuation 
 * Difficulty: Medium
 * Tags: hash, queue, heap
 * 
 * Approach: Use hash map for prices, heaps for min/max with lazy deletion
 * Time Complexity: O(log n) for update, O(1) for current, O(log n) for min/max
 * Space Complexity: O(n)
 */

import java.util.*;

class StockPrice {
    private Map<Integer, Integer> prices;
    private PriorityQueue<int[]> maxHeap;
    private PriorityQueue<int[]> minHeap;
    private int latestTimestamp;

    public StockPrice() {
        prices = new HashMap<>();
        maxHeap = new PriorityQueue<>((a, b) -> Integer.compare(b[1], a[1]));
        minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a[1], b[1]));
        latestTimestamp = 0;
    }
    
    public void update(int timestamp, int price) {
        prices.put(timestamp, price);
        latestTimestamp = Math.max(latestTimestamp, timestamp);
        maxHeap.offer(new int[]{timestamp, price});
        minHeap.offer(new int[]{timestamp, price});
    }
    
    public int current() {
        return prices.get(latestTimestamp);
    }
    
    public int maximum() {
        while (!maxHeap.isEmpty() && 
               prices.get(maxHeap.peek()[0]) != maxHeap.peek()[1]) {
            maxHeap.poll();
        }
        return maxHeap.peek()[1];
    }
    
    public int minimum() {
        while (!minHeap.isEmpty() && 
               prices.get(minHeap.peek()[0]) != minHeap.peek()[1]) {
            minHeap.poll();
        }
        return minHeap.peek()[1];
    }
}

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice obj = new StockPrice();
 * obj.update(timestamp,price);
 * int param_2 = obj.current();
 * int param_3 = obj.maximum();
 * int param_4 = obj.minimum();
 */