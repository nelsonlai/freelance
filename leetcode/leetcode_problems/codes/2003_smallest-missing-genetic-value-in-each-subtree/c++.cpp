/*
 * Problem: Smallest Missing Genetic Value in Each Subtree
 * Difficulty: Hard
 * Tags: array, tree, graph, DFS
 * 
 * Approach: DFS to collect values in each subtree, find smallest missing value
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n)
 */

#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        vector<vector<int>> children(n);
        
        // Build tree
        for (int i = 1; i < n; i++) {
            children[parents[i]].push_back(i);
        }
        
        vector<int> result(n, 1);
        
        // Find node with value 1 (if exists)
        int nodeWithOne = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                nodeWithOne = i;
                break;
            }
        }
        
        if (nodeWithOne == -1) {
            return result;
        }
        
        // Collect all values in path from nodeWithOne to root
        unordered_set<int> visited;
        int current = nodeWithOne;
        int missing = 1;
        
        while (current != -1) {
            // DFS to collect all values in subtree of current
            unordered_set<int> subtreeValues;
            stack<int> st;
            st.push(current);
            
            while (!st.empty()) {
                int node = st.top();
                st.pop();
                if (visited.count(node)) {
                    continue;
                }
                visited.insert(node);
                subtreeValues.insert(nums[node]);
                
                for (int child : children[node]) {
                    if (!visited.count(child)) {
                        st.push(child);
                    }
                }
            }
            
            // Find smallest missing value
            while (subtreeValues.count(missing)) {
                missing++;
            }
            
            result[current] = missing;
            current = (current < n) ? parents[current] : -1;
        }
        
        return result;
    }
};