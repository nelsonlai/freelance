/*
 * Problem: Construct Quad Tree
 * Difficulty: Medium
 * Tags: array, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

#include <vector>

using namespace std;

class Solution {
private:
    Node* build(vector<vector<int>>& grid, int r1, int c1, int r2, int c2) {
        if (r1 == r2 && c1 == c2) {
            return new Node(grid[r1][c1] == 1, true, nullptr, nullptr, nullptr, nullptr);
        }
        
        int midR = (r1 + r2) / 2;
        int midC = (c1 + c2) / 2;
        
        Node* topLeft = build(grid, r1, c1, midR, midC);
        Node* topRight = build(grid, r1, midC + 1, midR, c2);
        Node* bottomLeft = build(grid, midR + 1, c1, r2, midC);
        Node* bottomRight = build(grid, midR + 1, midC + 1, r2, c2);
        
        if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf &&
            topLeft->val == topRight->val && topRight->val == bottomLeft->val && bottomLeft->val == bottomRight->val) {
            return new Node(topLeft->val, true, nullptr, nullptr, nullptr, nullptr);
        }
        
        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }

public:
    Node* construct(vector<vector<int>>& grid) {
        return build(grid, 0, 0, grid.size() - 1, grid.size() - 1);
    }
};