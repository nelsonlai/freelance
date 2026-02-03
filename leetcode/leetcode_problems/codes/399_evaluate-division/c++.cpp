/*
 * Problem: Evaluate Division
 * Difficulty: Medium
 * Tags: array, string, graph, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    double dfs(string start, string end, unordered_map<string, unordered_map<string, double>>& graph, unordered_set<string>& visited) {
        if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
            return -1.0;
        }
        
        if (graph[start].find(end) != graph[start].end()) {
            return graph[start][end];
        }
        
        visited.insert(start);
        for (auto& entry : graph[start]) {
            string neighbor = entry.first;
            double value = entry.second;
            if (visited.find(neighbor) == visited.end()) {
                double result = dfs(neighbor, end, graph, visited);
                if (result != -1.0) {
                    return value * result;
                }
            }
        }
        visited.erase(start);
        
        return -1.0;
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> graph;
        
        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];
            double value = values[i];
            
            graph[a][b] = value;
            graph[b][a] = 1.0 / value;
        }
        
        vector<double> results;
        for (auto& query : queries) {
            unordered_set<string> visited;
            results.push_back(dfs(query[0], query[1], graph, visited));
        }
        
        return results;
    }
};