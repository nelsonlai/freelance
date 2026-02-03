/*
 * Problem: Permutation Sequence
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);
        
        vector<int> fact(n);
        fact[0] = 1;
        for (int i = 1; i < n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        
        k--; // Convert to 0-indexed
        string result;
        
        for (int i = n - 1; i >= 0; i--) {
            int index = k / fact[i];
            result += to_string(nums[index]);
            nums.erase(nums.begin() + index);
            k %= fact[i];
        }
        
        return result;
    }
};