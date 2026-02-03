/*
 * Problem: Count Houses in a Circular Street
 * Difficulty: Easy
 * Tags: array, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a street.
 * 
 * YOU HAVE TO PASS THE OBJECT ITSELF AS THE FIRST PARAMETER
 * 
 * struct Street {
 *     void (*openDoor)(struct Street*);
 *     void (*closeDoor)(struct Street*);
 *     bool (*isDoorOpen)(struct Street*);
 *     void (*moveRight)(struct Street*);
 *     void (*moveLeft)(struct Street*);
 * };
 */
int houseCount(struct Street* street, int k){

}