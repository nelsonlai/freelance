/*
 * Problem: Flatten Nested List Iterator
 * Difficulty: Medium
 * Tags: tree, search, stack, queue
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

#include <vector>
#include <stack>

using namespace std;

class NestedIterator {
private:
    stack<NestedInteger> st;

public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        flatten(nestedList);
    }
    
    void flatten(vector<NestedInteger>& nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; i--) {
            st.push(nestedList[i]);
        }
    }
    
    int next() {
        NestedInteger top = st.top();
        st.pop();
        return top.getInteger();
    }
    
    bool hasNext() {
        while (!st.empty()) {
            if (st.top().isInteger()) {
                return true;
            }
            vector<NestedInteger> list = st.top().getList();
            st.pop();
            flatten(list);
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */