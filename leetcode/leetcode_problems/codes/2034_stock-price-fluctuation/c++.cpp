/*
 * Problem: Stock Price Fluctuation 
 * Difficulty: Medium
 * Tags: hash, queue, heap
 * 
 * Approach: Use hash map for prices, heaps for min/max with lazy deletion
 * Time Complexity: O(log n) for update, O(1) for current, O(log n) for min/max
 * Space Complexity: O(n)
 */

#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class StockPrice {
private:
    unordered_map<int, int> prices;
    priority_queue<pair<int, int>> maxHeap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    int latestTimestamp;

public:
    StockPrice() {
        latestTimestamp = 0;
    }
    
    void update(int timestamp, int price) {
        prices[timestamp] = price;
        latestTimestamp = max(latestTimestamp, timestamp);
        maxHeap.push({price, timestamp});
        minHeap.push({price, timestamp});
    }
    
    int current() {
        return prices[latestTimestamp];
    }
    
    int maximum() {
        while (!maxHeap.empty() && 
               prices[maxHeap.top().second] != maxHeap.top().first) {
            maxHeap.pop();
        }
        return maxHeap.top().first;
    }
    
    int minimum() {
        while (!minHeap.empty() && 
               prices[minHeap.top().second] != minHeap.top().first) {
            minHeap.pop();
        }
        return minHeap.top().first;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */