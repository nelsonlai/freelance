/*
 * Problem: Building H2O
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

typedef struct {
    // User defined data may be declared here.
    
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Initialize user defined data here.
    
    return obj;
}

void hydrogen(H2O* obj) {
    
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
}

void oxygen(H2O* obj) {
    
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here.
    
}