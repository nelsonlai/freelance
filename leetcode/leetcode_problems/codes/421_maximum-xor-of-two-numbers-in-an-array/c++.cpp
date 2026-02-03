/*
 * Problem: Maximum XOR of Two Numbers in an Array
 * Difficulty: Medium
 * Tags: array, hash
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
    int findMaximumXOR(vector<int>& nums) {
        int maxXor = 0;
        int mask = 0;
        
        for (int i = 31; i >= 0; i--) {
            mask |= (1 << i);
            unordered_set<int> prefixes;
            for (int num : nums) {
                prefixes.insert(num & mask);
            }
            
            int temp = maxXor | (1 << i);
            for (int prefix : prefixes) {
                if (prefixes.find(temp ^ prefix) != prefixes.end()) {
                    maxXor = temp;
                    break;
                }
            }
        }
        
        return maxXor;
    }
};