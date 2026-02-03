/*
 * Problem: Task Scheduler
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        for (char task : tasks) {
            count[task - 'A']++;
        }
        
        sort(count.begin(), count.end());
        int maxCount = count[25];
        int maxCountTasks = 0;
        for (int c : count) {
            if (c == maxCount) {
                maxCountTasks++;
            }
        }
        
        return max((int)tasks.size(), (maxCount - 1) * (n + 1) + maxCountTasks);
    }
};