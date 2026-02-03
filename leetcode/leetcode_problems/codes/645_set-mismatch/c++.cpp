/*
 * Problem: Set Mismatch
 * Difficulty: Easy
 * Tags: array, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        int expectedSum = n * (n + 1) / 2;
        int actualSum = 0;
        unordered_set<int> seen;
        int duplicate = 0;
        
        for (int num : nums) {
            actualSum += num;
            if (seen.find(num) != seen.end()) {
                duplicate = num;
            }
            seen.insert(num);
        }
        
        int missing = expectedSum - (actualSum - duplicate);
        return {duplicate, missing};
    }
};