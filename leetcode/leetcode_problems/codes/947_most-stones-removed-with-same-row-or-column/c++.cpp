/*
 * Problem: Most Stones Removed with Same Row or Column
 * Difficulty: Medium
 * Tags: array, graph, hash, search
 * 
 * Approach: Union-Find to group stones in same row/column, answer is total - number of groups
 * Time Complexity: O(n * α(n)) where α is inverse Ackermann function
 * Space Complexity: O(n) for Union-Find
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_map<int, int> parent;
    
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unionSet(int x, int y) {
        parent[find(x)] = find(y);
    }
    
public:
    int removeStones(vector<vector<int>>& stones) {
        for (auto& stone : stones) {
            unionSet(stone[0], ~stone[1]);
        }
        
        unordered_set<int> groups;
        for (auto& stone : stones) {
            groups.insert(find(stone[0]));
        }
        
        return stones.size() - groups.size();
    }
};