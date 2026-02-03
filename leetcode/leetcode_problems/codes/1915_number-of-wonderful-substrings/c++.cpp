/*
 * Problem: Number of Wonderful Substrings
 * Difficulty: Medium
 * Tags: array, string, hash, bit manipulation
 * 
 * Approach: Use prefix XOR to track character parity, count substrings with at most 1 odd count
 * Time Complexity: O(n * 10) where n is length, 10 is possible characters
 * Space Complexity: O(1024) for mask counts
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    long long wonderfulSubstrings(string word) {
        unordered_map<int, long long> count;
        count[0] = 1;
        int mask = 0;
        long long result = 0;
        
        for (char c : word) {
            int idx = c - 'a';
            mask ^= (1 << idx);
            
            // All even counts
            result += count[mask];
            
            // One odd count
            for (int i = 0; i < 10; i++) {
                result += count[mask ^ (1 << i)];
            }
            
            count[mask]++;
        }
        
        return result;
    }
};