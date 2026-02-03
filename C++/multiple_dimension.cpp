/*
 * C++ PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates C++ programming concepts and techniques:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental C++ PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */


Common Sorting Algorithms (Most Widely Used)
These are the ones you'll often encounter in coding interviews and practical software applications.

Algorithm	    Time Complexity (Average)	    Space	Stable?	Notes
Bubble Sort	    O(n²)	                        O(1)	✅	Simple, educational only
Selection Sort	O(n²)	                        O(1)	❌	Always scans entire list
Insertion Sort	O(n²)	                        O(1)	✅	Good for small or mostly sorted data
Merge Sort	    O(n log n)	                    O(n)	✅	Divide and conquer
Quick Sort	    O(n log n)	                    O(log n)❌	Fastest in practice, but unstable
Heap Sort	    O(n log n)	                    O(1)	❌	Based on heap data structure
Shell Sort	    ~O(n log n)	                    O(1)	❌	Improved Insertion Sort
Counting Sort	O(n + k)	                    O(k)	✅	Only for integers or small range
Radix Sort	O(nk)	                            O(n + k)	✅	Works on digits/characters
Bucket Sort	O(n + k)	                        O(n)	✅	Good when input is uniformly distributed

Recursive functions are functions that call themselves to solve smaller instances of the same problem. They are often used for problems that can be broken down into smaller, similar subproblems.

Caller --> Callee

Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Merge Sort, Quick Sort, Heap Sort, Shell Sort