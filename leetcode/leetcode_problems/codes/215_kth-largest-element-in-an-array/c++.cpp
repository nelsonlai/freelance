/*
 * Problem: Kth Largest Element in an Array
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        
        for (int num : nums) {
            heap.push(num);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        
        return heap.top();
    }
};