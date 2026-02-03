#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    void buildGraph(TreeNode* node, TreeNode* parent, unordered_map<int, vector<int>>& graph, unordered_set<int>& leaves) {
        if (node == nullptr) return;
        if (parent != nullptr) {
            graph[node->val].push_back(parent->val);
        }
        if (node->left != nullptr) {
            graph[node->val].push_back(node->left->val);
            buildGraph(node->left, node, graph, leaves);
        }
        if (node->right != nullptr) {
            graph[node->val].push_back(node->right->val);
            buildGraph(node->right, node, graph, leaves);
        }
        if (node->left == nullptr && node->right == nullptr) {
            leaves.insert(node->val);
        }
    }

public:
    int findClosestLeaf(TreeNode* root, int k) {
        unordered_map<int, vector<int>> graph;
        unordered_set<int> leaves;
        
        buildGraph(root, nullptr, graph, leaves);
        
        queue<int> q;
        unordered_set<int> visited;
        q.push(k);
        visited.insert(k);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            if (leaves.find(node) != leaves.end()) {
                return node;
            }
            for (int neighbor : graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        
        return -1;
    }
};
