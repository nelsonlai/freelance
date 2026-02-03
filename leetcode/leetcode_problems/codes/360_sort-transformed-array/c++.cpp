/*
 * Problem: Sort Transformed Array
 * Difficulty: Medium
 * Tags: array, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int transform(int x, int a, int b, int c) {
        return a * x * x + b * x + c;
    }

public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> transformed;
        for (int num : nums) {
            transformed.push_back(transform(num, a, b, c));
        }
        
        if (a == 0) {
            return b >= 0 ? transformed : vector<int>(transformed.rbegin(), transformed.rend());
        }
        
        double vertex = -b / (2.0 * a);
        vector<int> result;
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            if (abs(nums[left] - vertex) > abs(nums[right] - vertex)) {
                result.push_back(transformed[left++]);
            } else {
                result.push_back(transformed[right--]);
            }
        }
        
        return a < 0 ? result : vector<int>(result.rbegin(), result.rend());
    }
};