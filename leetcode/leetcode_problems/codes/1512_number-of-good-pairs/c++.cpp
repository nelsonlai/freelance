/*
 * Problem: Number of Good Pairs
 * Difficulty: Easy
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        int result = 0;
        for (auto& [num, count] : freq) {
            result += count * (count - 1) / 2;
        }
        
        return result;
    }
};