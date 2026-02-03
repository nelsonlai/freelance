/*
 * Problem: Find the Celebrity
 * Difficulty: Medium
 * Tags: array, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
public:
    int findCelebrity(int n) {
        int candidate = 0;
        
        for (int i = 1; i < n; i++) {
            if (knows(candidate, i)) {
                candidate = i;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (i != candidate) {
                if (knows(candidate, i) || !knows(i, candidate)) {
                    return -1;
                }
            }
        }
        
        return candidate;
    }
};