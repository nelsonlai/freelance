/*
 * Problem: Move Sub-Tree of N-Ary Tree
 * Difficulty: Hard
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
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

class Solution {
private:
    Node* findParent(Node* node, Node* target, Node* parent) {
        if (node == target) {
            return parent;
        }
        for (Node* child : node->children) {
            Node* result = findParent(child, target, node);
            if (result != nullptr) {
                return result;
            }
        }
        return nullptr;
    }
    
    bool isDescendant(Node* node, Node* target) {
        if (node == target) {
            return true;
        }
        for (Node* child : node->children) {
            if (isDescendant(child, target)) {
                return true;
            }
        }
        return false;
    }
    
public:
    Node* moveSubTree(Node* root, Node* p, Node* q) {
        if (p == q) {
            return root;
        }
        
        Node* pParent = findParent(root, p, nullptr);
        
        if (isDescendant(p, q)) {
            Node* qParent = findParent(root, q, nullptr);
            qParent->children.erase(
                remove(qParent->children.begin(), qParent->children.end(), q),
                qParent->children.end()
            );
            if (pParent != nullptr) {
                pParent->children.erase(
                    remove(pParent->children.begin(), pParent->children.end(), p),
                    pParent->children.end()
                );
                pParent->children.push_back(q);
            } else {
                root = q;
            }
            q->children.push_back(p);
        } else {
            if (pParent != nullptr) {
                pParent->children.erase(
                    remove(pParent->children.begin(), pParent->children.end(), p),
                    pParent->children.end()
                );
            } else {
                root = nullptr;
            }
            q->children.push_back(p);
        }
        
        return root != nullptr ? root : p;
    }
};