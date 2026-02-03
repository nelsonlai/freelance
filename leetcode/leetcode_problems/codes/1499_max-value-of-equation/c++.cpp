/*
 * Problem: Max Value of Equation
 * Difficulty: Hard
 * Tags: array, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <deque>
#include <climits>

using namespace std;

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        deque<pair<int, int>> dq;
        int maxValue = INT_MIN;
        
        for (auto& point : points) {
            int x = point[0];
            int y = point[1];
            
            while (!dq.empty() && x - dq.front().second > k) {
                dq.pop_front();
            }
            
            if (!dq.empty()) {
                maxValue = max(maxValue, x + y + dq.front().first);
            }
            
            while (!dq.empty() && dq.back().first <= y - x) {
                dq.pop_back();
            }
            
            dq.push_back({y - x, x});
        }
        
        return maxValue;
    }
};