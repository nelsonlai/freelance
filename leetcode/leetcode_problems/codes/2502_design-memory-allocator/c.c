/*
 * Problem: Design Memory Allocator
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} Allocator;


Allocator* allocatorCreate(int n) {
    
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    
}

void allocatorFree(Allocator* obj) {
    
}

/**
 * Your Allocator struct will be instantiated and called as such:
 * Allocator* obj = allocatorCreate(n);
 * int param_1 = allocatorAllocate(obj, size, mID);
 
 * int param_2 = allocatorFreeMemory(obj, mID);
 
 * allocatorFree(obj);
*/