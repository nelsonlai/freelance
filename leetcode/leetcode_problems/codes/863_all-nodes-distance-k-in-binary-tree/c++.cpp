#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    unordered_map<int, vector<int>> graph;
    
    void buildGraph(TreeNode* node, TreeNode* parent) {
        if (node == nullptr) {
            return;
        }
        if (parent != nullptr) {
            graph[node->val].push_back(parent->val);
            graph[parent->val].push_back(node->val);
        }
        buildGraph(node->left, node);
        buildGraph(node->right, node);
    }

public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        buildGraph(root, nullptr);
        
        queue<int> q;
        q.push(target->val);
        unordered_set<int> visited;
        visited.insert(target->val);
        int level = 0;
        
        while (!q.empty() && level < k) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();
                for (int neighbor : graph[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            level++;
        }
        
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
};
