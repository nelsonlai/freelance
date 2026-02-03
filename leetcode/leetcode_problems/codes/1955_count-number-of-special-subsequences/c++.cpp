/*
 * Problem: Count Number of Special Subsequences
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP - track count of subsequences ending with 0, 01, 012
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    
public:
    int countSpecialSubsequences(vector<int>& nums) {
        long long count0 = 0;
        long long count01 = 0;
        long long count012 = 0;
        
        for (int num : nums) {
            if (num == 0) {
                count0 = (2 * count0 + 1) % MOD;
            } else if (num == 1) {
                count01 = (2 * count01 + count0) % MOD;
            } else {  // num == 2
                count012 = (2 * count012 + count01) % MOD;
            }
        }
        
        return count012;
    }
};