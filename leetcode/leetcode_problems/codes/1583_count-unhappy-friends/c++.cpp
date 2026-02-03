/*
 * Problem: Count Unhappy Friends
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<unordered_map<int, int>> prefMap(n);
        for (int i = 0; i < n; i++) {
            for (int rank = 0; rank < preferences[i].size(); rank++) {
                prefMap[i][preferences[i][rank]] = rank;
            }
        }
        
        unordered_map<int, int> pairMap;
        for (auto& pair : pairs) {
            pairMap[pair[0]] = pair[1];
            pairMap[pair[1]] = pair[0];
        }
        
        unordered_set<int> unhappy;
        
        for (int x = 0; x < n; x++) {
            int y = pairMap[x];
            for (int u = 0; u < n; u++) {
                if (u != x && u != y) {
                    int v = pairMap[u];
                    int xPrefU = prefMap[x].count(u) ? prefMap[x][u] : n;
                    int xPrefY = prefMap[x].count(y) ? prefMap[x][y] : n;
                    int uPrefX = prefMap[u].count(x) ? prefMap[u][x] : n;
                    int uPrefV = prefMap[u].count(v) ? prefMap[u][v] : n;
                    
                    if (xPrefU < xPrefY && uPrefX < uPrefV) {
                        unhappy.insert(x);
                        unhappy.insert(u);
                    }
                }
            }
        }
        
        return unhappy.size();
    }
};