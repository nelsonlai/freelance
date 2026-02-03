/*
 * Problem: Course Schedule III
 * Difficulty: Hard
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
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        priority_queue<int> heap;
        int time = 0;
        
        for (auto& course : courses) {
            time += course[0];
            heap.push(course[0]);
            
            if (time > course[1]) {
                time -= heap.top();
                heap.pop();
            }
        }
        
        return heap.size();
    }
};