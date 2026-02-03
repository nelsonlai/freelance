/*
 * Problem: Concatenation of Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Concatenate array with itself
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        vector<int> result = nums;
        result.insert(result.end(), nums.begin(), nums.end());
        return result;
    }
};