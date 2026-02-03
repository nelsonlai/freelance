/**
 * Problem: Peeking Iterator
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

// Java Iterator interface reference:
// https://docs.oracle.com/javase/8/docs/api/java/util/Iterator.html

import java.util.*;

class PeekingIterator implements Iterator<Integer> {
    private Iterator<Integer> iterator;
    private Integer nextVal;
    
	public PeekingIterator(Iterator<Integer> iterator) {
	    this.iterator = iterator;
	    if (iterator.hasNext()) {
	        nextVal = iterator.next();
	    }
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	public Integer peek() {
        return nextVal;
	}
	
	@Override
	public Integer next() {
	    Integer val = nextVal;
	    if (iterator.hasNext()) {
	        nextVal = iterator.next();
	    } else {
	        nextVal = null;
	    }
	    return val;
	}
	
	@Override
	public boolean hasNext() {
	    return nextVal != null;
	}
}