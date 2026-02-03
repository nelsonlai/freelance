/*
 * Problem: Find the Kth Smallest Sum of a Matrix With Sorted Rows
 * Difficulty: Hard
 * Tags: array, sort, search, queue, heap
 * 
 * Approach: Use heap to merge sorted rows, keep k smallest sums
 * Time Complexity: O(m * k * log(k)) where m is rows
 * Space Complexity: O(k) for heap
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        priority_queue<int> heap;
        heap.push(0);
        
        for (auto& row : mat) {
            priority_queue<int> newHeap;
            while (!heap.empty()) {
                int sumVal = heap.top();
                heap.pop();
                for (int num : row) {
                    newHeap.push(sumVal + num);
                    if (newHeap.size() > k) {
                        newHeap.pop();
                    }
                }
            }
            heap = newHeap;
        }
        
        return heap.top();
    }
};