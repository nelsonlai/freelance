/*
 * Problem: Count Houses in a Circular Street II
 * Difficulty: Hard
 * Tags: tree
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a street.
 * 
 * YOU HAVE TO PASS THE OBJECT ITSELF AS THE FIRST PARAMETER
 * 
 * struct Street {
 *     void (*closeDoor)(struct Street*);
 *     bool (*isDoorOpen)(struct Street*);
 *     void (*moveRight)(struct Street*);
 * };
 */
int houseCount(struct Street* street, int k){

}