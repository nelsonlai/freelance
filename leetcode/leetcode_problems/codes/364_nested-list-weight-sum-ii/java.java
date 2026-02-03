/**
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
 * public interface NestedInteger {
 *     // Constructor initializes an empty nested list.
 *     public NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     public NestedInteger(int value);
 *
 *     // @return true if this NestedInteger holds a single integer, rather than a nested list.
 *     public boolean isInteger();
 *
 *     // @return the single integer that this NestedInteger holds, if it holds a single integer
 *     // Return null if this NestedInteger holds a nested list
 *     public Integer getInteger();
 *
 *     // Set this NestedInteger to hold a single integer.
 *     public void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     public void add(NestedInteger ni);
 *
 *     // @return the nested list that this NestedInteger holds, if it holds a nested list
 *     // Return empty list if this NestedInteger holds a single integer
 *     public List<NestedInteger> getList();
 * }
 */
import java.util.*;

class Solution {
    public int depthSumInverse(List<NestedInteger> nestedList) {
        int maxDepth = getMaxDepth(nestedList, 1);
        return dfs(nestedList, 1, maxDepth);
    }
    
    private int getMaxDepth(List<NestedInteger> nestedList, int depth) {
        int maxDepth = depth;
        for (NestedInteger item : nestedList) {
            if (!item.isInteger()) {
                maxDepth = Math.max(maxDepth, getMaxDepth(item.getList(), depth + 1));
            }
        }
        return maxDepth;
    }
    
    private int dfs(List<NestedInteger> nestedList, int depth, int maxDepth) {
        int total = 0;
        for (NestedInteger item : nestedList) {
            if (item.isInteger()) {
                total += item.getInteger() * (maxDepth - depth + 1);
            } else {
                total += dfs(item.getList(), depth + 1, maxDepth);
            }
        }
        return total;
    }
}