/*
 * Problem: Beautiful Arrangement II
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> result;
        int left = 1, right = n;
        
        while (left <= right) {
            if (k > 1) {
                if (k % 2 == 1) {
                    result.push_back(left++);
                } else {
                    result.push_back(right--);
                }
                k--;
            } else {
                result.push_back(left++);
            }
        }
        
        return result;
    }
};