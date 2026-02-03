/*
 * Problem: Nested List Weight Sum II
 * Difficulty: Medium
 * Tags: search, stack
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int getMaxDepth(vector<NestedInteger>& nestedList, int depth) {
        int maxDepth = depth;
        for (auto& item : nestedList) {
            if (!item.isInteger()) {
                maxDepth = max(maxDepth, getMaxDepth(item.getList(), depth + 1));
            }
        }
        return maxDepth;
    }
    
    int dfs(vector<NestedInteger>& nestedList, int depth, int maxDepth) {
        int total = 0;
        for (auto& item : nestedList) {
            if (item.isInteger()) {
                total += item.getInteger() * (maxDepth - depth + 1);
            } else {
                total += dfs(item.getList(), depth + 1, maxDepth);
            }
        }
        return total;
    }

public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int maxDepth = getMaxDepth(nestedList, 1);
        return dfs(nestedList, 1, maxDepth);
    }
};