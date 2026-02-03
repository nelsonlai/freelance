/*
 * LINKED LIST EXAMPLES EXAMPLES
 * 
 * This file demonstrates linked list implementation and operations:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental LINKED LIST concepts
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

/*
 * PREPROCESSOR DIRECTIVES AND INCLUDES
 * 
 * This section includes necessary headers and defines preprocessor directives
 * for the linked list testing program.
 */
#define LINKED_LISTS_NO_MAIN  // Prevent main function from linkList-Single-Double.cpp
#include "linkList-Single-Double.cpp"  // Include the linked list implementation
#include <iostream>  // For input/output operations (cout)
#include <cassert>   // For assertion testing (assert macro)

/*
 * MAIN FUNCTION - LINKED LIST TESTING
 * 
 * This function contains comprehensive tests for both singly and doubly linked lists.
 * It demonstrates proper testing methodology and validates all major operations.
 * 
 * Testing Strategy:
 * - Test basic operations (insert, delete, access)
 * - Test edge cases (empty list, single element)
 * - Test iterator functionality
 * - Use assertions to validate expected behavior
 */
int main() {
    /*
     * TEST SINGLY LINKED LIST BASIC OPERATIONS
     * 
     * This test block validates all fundamental operations of a singly linked list:
     * - Empty list creation and validation
     * - Adding elements (push_back, push_front)
     * - Inserting elements at specific positions
     * - Removing elements (erase, pop_front)
     * - Clearing the list
     * - Size and empty state validation
     */
    {
        SinglyLinkedListInt s;  // Create empty singly linked list
        
        // Test initial empty state
        assert(s.empty());  // Verify list is initially empty
        
        // Test push_back operation
        s.push_back(10);  // Add element to the end
        assert(!s.empty() && s.size() == 1);  // Verify list is no longer empty and has 1 element
        
        // Test push_front operation
        s.push_front(5);  // Add element to the beginning
        assert(s.size() == 2);  // Verify list now has 2 elements
        
        // Test insert operation at specific position
        s.insert(1, 7);  // Insert 7 at position 1: [5, 7, 10]
        assert(s.to_vector() == std::vector<int>({5,7,10}));  // Verify correct order
        
        // Test erase operation
        s.erase(1);  // Remove element at position 1: [5, 10]
        assert(s.to_vector() == std::vector<int>({5,10}));  // Verify correct order after deletion
        
        // Test pop_front operation
        s.pop_front();  // Remove first element: [10]
        assert(s.to_vector() == std::vector<int>({10}));  // Verify only one element remains
        
        // Test clear operation
        s.clear();  // Remove all elements
        assert(s.empty());  // Verify list is empty again
    }

    /*
     * TEST ITERATOR FUNCTIONALITY
     * 
     * This test block validates the iterator implementation for singly linked list:
     * - Range-based for loop support
     * - Correct iteration order
     * - Iterator increment and dereference operations
     */
    {
        SinglyLinkedListInt s;  // Create new singly linked list
        
        // Populate list with numbers 1 through 5
        for (int i = 1; i <= 5; ++i) {
            s.push_back(i);  // Add each number to the end
        }
        
        int expected = 1;  // Expected value for first iteration
        
        // Test range-based for loop iteration
        for (int v : s) {
            assert(v == expected);  // Verify each value matches expected
            ++expected;  // Increment expected value for next iteration
        }
    }

    /*
     * TEST DOUBLY LINKED LIST BASIC OPERATIONS
     * 
     * This test block validates all fundamental operations of a doubly linked list:
     * - Adding elements (push_back)
     * - Inserting elements at specific positions
     * - Removing elements (erase, pop_back)
     * - Size validation
     * - Bidirectional traversal capability
     */
    {
        DoublyLinkedListInt d;  // Create empty doubly linked list
        
        // Test push_back operations
        d.push_back(1);  // Add first element
        d.push_back(2);  // Add second element
        d.push_back(3);  // Add third element
        assert(d.size() == 3);  // Verify list has 3 elements
        
        // Test insert operation at specific position
        d.insert(1, 9);  // Insert 9 at position 1: [1, 9, 2, 3]
        assert(d.to_vector() == std::vector<int>({1,9,2,3}));  // Verify correct order
        
        // Test erase operation
        d.erase(2);  // Remove element at position 2: [1, 9, 3]
        assert(d.to_vector() == std::vector<int>({1,9,3}));  // Verify correct order after deletion
        
        // Test pop_back operation
        assert(d.pop_back() == 3);  // Remove and verify last element
    }

    // Display success message if all tests pass
    std::cout << "All tests passed.\n";
    
    // Return 0 to indicate successful program execution
    return 0;
}
