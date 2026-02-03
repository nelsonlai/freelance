/*
 * Problem: Minimum Garden Perimeter to Collect Enough Apples
 * Difficulty: Medium
 * Tags: tree, math, search, binary search
 * 
 * Approach: Binary search on perimeter, calculate apples in square
 * Time Complexity: O(log(neededApples))
 * Space Complexity: O(1)
 */

class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        long long left = 0, right = 1000000;
        long long result = 0;
        
        while (left <= right) {
            long long mid = (left + right) / 2;
            long long apples = 2 * mid * (mid + 1) * (2 * mid + 1);
            if (apples >= neededApples) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return 8 * result;
    }
};