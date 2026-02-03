/*
 * Problem: Jump Game IV
 * Difficulty: Hard
 * Tags: array, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) {
            return 0;
        }
        
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; i++) {
            valueToIndices[arr[i]].push_back(i);
        }
        
        queue<int> q;
        unordered_set<int> visited;
        q.push(0);
        visited.insert(0);
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int curr = q.front();
                q.pop();
                
                if (curr == n - 1) {
                    return steps;
                }
                
                // Check neighbors
                if (curr - 1 >= 0 && visited.find(curr - 1) == visited.end()) {
                    visited.insert(curr - 1);
                    q.push(curr - 1);
                }
                if (curr + 1 < n && visited.find(curr + 1) == visited.end()) {
                    visited.insert(curr + 1);
                    q.push(curr + 1);
                }
                
                // Check same values
                if (valueToIndices.find(arr[curr]) != valueToIndices.end()) {
                    for (int neighbor : valueToIndices[arr[curr]]) {
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            q.push(neighbor);
                        }
                    }
                    valueToIndices.erase(arr[curr]);
                }
            }
            steps++;
        }
        
        return steps;
    }
};