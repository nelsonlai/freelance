/*
 * Problem: Peeking Iterator
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
private:
    int nextVal;
    bool hasNextVal;

public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    hasNextVal = Iterator::hasNext();
	    if (hasNextVal) {
	        nextVal = Iterator::next();
	    }
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        return nextVal;
	}
	
	int next() {
	    int val = nextVal;
	    hasNextVal = Iterator::hasNext();
	    if (hasNextVal) {
	        nextVal = Iterator::next();
	    }
	    return val;
	}
	
	bool hasNext() const {
	    return hasNextVal;
	}
};