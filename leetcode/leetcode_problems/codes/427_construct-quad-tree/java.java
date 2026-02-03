/**
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
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;

    
    public Node() {
        this.val = false;
        this.isLeaf = false;
        this.topLeft = null;
        this.topRight = null;
        this.bottomLeft = null;
        this.bottomRight = null;
    }
    
    public Node(boolean val, boolean isLeaf) {
        this.val = val;
        this.isLeaf = isLeaf;
        this.topLeft = null;
        this.topRight = null;
        this.bottomLeft = null;
        this.bottomRight = null;
    }
    
    public Node(boolean val, boolean isLeaf, Node topLeft, Node topRight, Node bottomLeft, Node bottomRight) {
        this.val = val;
        this.isLeaf = isLeaf;
        this.topLeft = topLeft;
        this.topRight = topRight;
        this.bottomLeft = bottomLeft;
        this.bottomRight = bottomRight;
    }
}
*/

class Solution {
    public Node construct(int[][] grid) {
        return build(grid, 0, 0, grid.length - 1, grid.length - 1);
    }
    
    private Node build(int[][] grid, int r1, int c1, int r2, int c2) {
        if (r1 == r2 && c1 == c2) {
            return new Node(grid[r1][c1] == 1, true, null, null, null, null);
        }
        
        int midR = (r1 + r2) / 2;
        int midC = (c1 + c2) / 2;
        
        Node topLeft = build(grid, r1, c1, midR, midC);
        Node topRight = build(grid, r1, midC + 1, midR, c2);
        Node bottomLeft = build(grid, midR + 1, c1, r2, midC);
        Node bottomRight = build(grid, midR + 1, midC + 1, r2, c2);
        
        if (topLeft.isLeaf && topRight.isLeaf && bottomLeft.isLeaf && bottomRight.isLeaf &&
            topLeft.val == topRight.val && topRight.val == bottomLeft.val && bottomLeft.val == bottomRight.val) {
            return new Node(topLeft.val, true, null, null, null, null);
        }
        
        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }
}