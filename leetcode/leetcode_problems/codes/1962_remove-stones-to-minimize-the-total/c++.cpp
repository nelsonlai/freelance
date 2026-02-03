/*
 * Problem: Remove Stones to Minimize the Total
 * Difficulty: Medium
 * Tags: array, greedy, queue, heap
 * 
 * Approach: Use max heap to always remove from largest pile
 * Time Complexity: O(n log n + k log n) where n is piles
 * Space Complexity: O(n)
 */

#include <vector>
#include <queue>
#include <numeric>

using namespace std;

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> heap(piles.begin(), piles.end());
        
        for (int i = 0; i < k; i++) {
            int largest = heap.top();
            heap.pop();
            int remove = largest / 2;
            heap.push(largest - remove);
        }
        
        int sum = 0;
        while (!heap.empty()) {
            sum += heap.top();
            heap.pop();
        }
        return sum;
    }
};