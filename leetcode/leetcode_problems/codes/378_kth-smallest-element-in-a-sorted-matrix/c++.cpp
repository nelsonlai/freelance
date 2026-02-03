/*
 * Problem: Kth Smallest Element in a Sorted Matrix
 * Difficulty: Medium
 * Tags: array, sort, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        
        for (int i = 0; i < min(k, n); i++) {
            heap.push({matrix[i][0], i, 0});
        }
        
        for (int i = 0; i < k - 1; i++) {
            auto cell = heap.top();
            heap.pop();
            int row = cell[1];
            int col = cell[2];
            if (col + 1 < n) {
                heap.push({matrix[row][col + 1], row, col + 1});
            }
        }
        
        return heap.top()[0];
    }
};