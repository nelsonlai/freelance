/*
 * Problem: Check If Array Pairs Are Divisible by k
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> remainderCount;
        for (int num : arr) {
            int remainder = ((num % k) + k) % k;
            remainderCount[remainder]++;
        }
        
        for (auto& [remainder, count] : remainderCount) {
            if (remainder == 0) {
                if (count % 2 != 0) {
                    return false;
                }
            } else if (remainder * 2 == k) {
                if (count % 2 != 0) {
                    return false;
                }
            } else {
                int complement = k - remainder;
                if (remainderCount[complement] != count) {
                    return false;
                }
            }
        }
        
        return true;
    }
};