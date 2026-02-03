/*
 * Problem: Find K Pairs with Smallest Sums
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
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
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (nums1.empty() || nums2.empty()) {
            return {};
        }
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        
        for (int i = 0; i < min(k, (int)nums1.size()); i++) {
            heap.push({nums1[i] + nums2[0], i, 0});
        }
        
        vector<vector<int>> result;
        while (!heap.empty() && result.size() < k) {
            auto cell = heap.top();
            heap.pop();
            int i = cell[1];
            int j = cell[2];
            result.push_back({nums1[i], nums2[j]});
            
            if (j + 1 < nums2.size()) {
                heap.push({nums1[i] + nums2[j + 1], i, j + 1});
            }
        }
        
        return result;
    }
};