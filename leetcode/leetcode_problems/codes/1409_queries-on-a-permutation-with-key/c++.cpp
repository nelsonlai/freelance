/*
 * Problem: Queries on a Permutation With Key
 * Difficulty: Medium
 * Tags: array, tree
 * 
 * Approach: Simulate - find index, move to front, track positions
 * Time Complexity: O(q * m) where q is queries length
 * Space Complexity: O(m) for permutation
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> perm;
        for (int i = 1; i <= m; i++) {
            perm.push_back(i);
        }
        
        vector<int> result;
        for (int query : queries) {
            auto it = find(perm.begin(), perm.end(), query);
            int idx = distance(perm.begin(), it);
            result.push_back(idx);
            perm.erase(it);
            perm.insert(perm.begin(), query);
        }
        
        return result;
    }
};