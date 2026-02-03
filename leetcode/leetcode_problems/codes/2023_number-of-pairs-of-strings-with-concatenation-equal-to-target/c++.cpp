/*
 * Problem: Number of Pairs of Strings With Concatenation Equal to Target
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Count occurrences of each string, check all pairs that form target
 * Time Complexity: O(n * m) where n is strings, m is target length
 * Space Complexity: O(n)
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numOfPairs(vector<string>& nums, string target) {
        int result = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i != j && nums[i] + nums[j] == target) {
                    result++;
                }
            }
        }
        
        return result;
    }
};