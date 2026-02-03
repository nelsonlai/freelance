/*
 * Problem: Find Root of N-Ary Tree
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    Node* findRoot(vector<Node*> tree) {
        unordered_set<Node*> children_set;
        for (Node* node : tree) {
            for (Node* child : node->children) {
                children_set.insert(child);
            }
        }
        
        for (Node* node : tree) {
            if (children_set.find(node) == children_set.end()) {
                return node;
            }
        }
        return nullptr;
    }
};