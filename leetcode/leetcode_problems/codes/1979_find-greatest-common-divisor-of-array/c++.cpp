/*
 * Problem: Find Greatest Common Divisor of Array
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Find GCD of min and max elements
 * Time Complexity: O(n + log(min, max)) where n is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <numeric>

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
    int findGCD(vector<int>& nums) {
        int minVal = *min_element(nums.begin(), nums.end());
        int maxVal = *max_element(nums.begin(), nums.end());
        return gcd(minVal, maxVal);
    }
};