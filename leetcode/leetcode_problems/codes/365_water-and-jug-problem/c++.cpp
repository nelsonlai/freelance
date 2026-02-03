/*
 * Problem: Water and Jug Problem
 * Difficulty: Medium
 * Tags: math, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <algorithm>

using namespace std;

class Solution {
private:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

public:
    bool canMeasureWater(int x, int y, int target) {
        if (x + y < target) {
            return false;
        }
        if (x == target || y == target || x + y == target) {
            return true;
        }
        return target % gcd(x, y) == 0;
    }
};