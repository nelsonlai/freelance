/*
 * Problem: Sum of Unique Elements
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        int sum = 0;
        for (auto& entry : count) {
            if (entry.second == 1) {
                sum += entry.first;
            }
        }
        
        return sum;
    }
};