/*
 * Problem: Find the Student that Will Replace the Chalk
 * Difficulty: Medium
 * Tags: array, search, prefix sum
 * 
 * Approach: Use prefix sum, find position after k mod total
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        long long total = accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= total;
        
        for (int i = 0; i < chalk.size(); i++) {
            if (k < chalk[i]) {
                return i;
            }
            k -= chalk[i];
        }
        
        return 0;
    }
};