/*
 * Problem: Get Biggest Three Rhombus Sums in a Grid
 * Difficulty: Medium
 * Tags: array, math, heap
 * 
 * Approach: For each center, try all possible rhombus sizes, use heap to track top 3
 * Time Complexity: O(m * n * min(m,n)) where m, n are dimensions
 * Space Complexity: O(1) excluding output
 */

#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        unordered_set<int> sums;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int maxSize = min({i + 1, m - i, j + 1, n - j});
                for (int size = 0; size < maxSize; size++) {
                    int total = 0;
                    if (size == 0) {
                        total = grid[i][j];
                    } else {
                        total += grid[i - size][j];
                        total += grid[i + size][j];
                        total += grid[i][j - size];
                        total += grid[i][j + size];
                        
                        for (int k = 1; k < size; k++) {
                            total += grid[i - size + k][j - k];
                            total += grid[i - size + k][j + k];
                            total += grid[i + size - k][j - k];
                            total += grid[i + size - k][j + k];
                        }
                    }
                    sums.insert(total);
                }
            }
        }
        
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int s : sums) {
            heap.push(s);
            if (heap.size() > 3) {
                heap.pop();
            }
        }
        
        vector<int> result;
        while (!heap.empty()) {
            result.push_back(heap.top());
            heap.pop();
        }
        reverse(result.begin(), result.end());
        
        return result;
    }
};