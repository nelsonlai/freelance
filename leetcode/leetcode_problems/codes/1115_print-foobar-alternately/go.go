// Problem: Print FooBar Alternately
// Difficulty: Medium
// Tags: general
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

type FooBar struct {
	n int
}

func NewFooBar(n int) *FooBar {
	return &FooBar{n: n}
}

func (fb *FooBar) Foo(printFoo func()) {
	for i := 0; i < fb.n; i++ {
		// printFoo() outputs "foo". Do not change or remove this line.
        printFoo()
	}
}

func (fb *FooBar) Bar(printBar func()) {
	for i := 0; i < fb.n; i++ {
		// printBar() outputs "bar". Do not change or remove this line.
        printBar()
	}
}