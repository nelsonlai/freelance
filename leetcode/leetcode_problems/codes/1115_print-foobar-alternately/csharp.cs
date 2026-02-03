/*
 * Problem: Print FooBar Alternately
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

public class FooBar {
    private int n;

    public FooBar(int n) {
        this.n = n;
    }

    public void Foo(Action printFoo) {
        
        for (int i = 0; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
        }
    }

    public void Bar(Action printBar) {
        
        for (int i = 0; i < n; i++) {
            
            // printBar() outputs "bar". Do not change or remove this line.
        	printBar();
        }
    }
}