/*
 * Problem: Meeting Rooms II
 * Difficulty: Medium
 * Tags: array, greedy, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        
        priority_queue<int, vector<int>, greater<int>> heap;
        heap.push(intervals[0][1]);
        
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= heap.top()) {
                heap.pop();
            }
            heap.push(intervals[i][1]);
        }
        
        return heap.size();
    }
};