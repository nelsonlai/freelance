/*
 * Problem: Reconstruct Itinerary
 * Difficulty: Hard
 * Tags: string, graph, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
private:
    void dfs(string airport, unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& graph, vector<string>& result) {
        while (!graph[airport].empty()) {
            string next = graph[airport].top();
            graph[airport].pop();
            dfs(next, graph, result);
        }
        result.push_back(airport);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
        for (auto& ticket : tickets) {
            graph[ticket[0]].push(ticket[1]);
        }
        
        vector<string> result;
        dfs("JFK", graph, result);
        reverse(result.begin(), result.end());
        return result;
    }
};