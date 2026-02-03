/*
 * Problem: Print FooBar Alternately
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

typedef struct {
    int n;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
    }
}

void fooBarFree(FooBar* obj) {
    
}