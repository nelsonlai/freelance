/*
 * Problem: Destination City
 * Difficulty: Easy
 * Tags: array, string, graph, hash
 * 
 * Approach: Find city that appears only as destination (not as source)
 * Time Complexity: O(n) where n is number of paths
 * Space Complexity: O(n) for sources set
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_set<string> sources;
        for (auto& path : paths) {
            sources.insert(path[0]);
        }
        
        for (auto& path : paths) {
            if (sources.find(path[1]) == sources.end()) {
                return path[1];
            }
        }
        
        return "";
    }
};