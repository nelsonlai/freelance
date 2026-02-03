/*
 * Problem: Parallel Courses III
 * Difficulty: Hard
 * Tags: array, graph, dp, topological sort
 * 
 * Approach: Topological sort with DP - calculate max time to complete each course
 * Time Complexity: O(n + m) where n is courses, m is relations
 * Space Complexity: O(n + m)
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> graph(n + 1);
        vector<int> inDegree(n + 1, 0);
        
        for (auto& relation : relations) {
            int prev = relation[0];
            int next = relation[1];
            graph[prev].push_back(next);
            inDegree[next]++;
        }
        
        // dp[i] = minimum time to complete course i
        vector<int> dp(n + 1, 0);
        queue<int> q;
        
        // Start with courses that have no prerequisites
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                dp[i] = time[i - 1];
            }
        }
        
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            
            for (int nextCourse : graph[course]) {
                dp[nextCourse] = max(dp[nextCourse], dp[course] + time[nextCourse - 1]);
                inDegree[nextCourse]--;
                if (inDegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        int result = 0;
        for (int i = 1; i <= n; i++) {
            result = max(result, dp[i]);
        }
        
        return result;
    }
};