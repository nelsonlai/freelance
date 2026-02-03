/*
 * Problem: IPO
 * Difficulty: Hard
 * Tags: array, greedy, sort, queue, heap
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
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<pair<int, int>> projects;
        for (int i = 0; i < n; i++) {
            projects.push_back({capital[i], profits[i]});
        }
        sort(projects.begin(), projects.end());
        
        priority_queue<int> heap;
        int i = 0;
        
        for (int j = 0; j < k; j++) {
            while (i < n && projects[i].first <= w) {
                heap.push(projects[i].second);
                i++;
            }
            
            if (heap.empty()) {
                break;
            }
            
            w += heap.top();
            heap.pop();
        }
        
        return w;
    }
};