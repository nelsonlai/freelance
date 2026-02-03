/*
 * Problem: Smallest Good Base
 * Difficulty: Hard
 * Tags: string, math, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    string smallestGoodBase(string n) {
        long long num = stoll(n);
        
        for (int m = (int)(log2(num)); m > 1; m--) {
            long long k = (long long)pow(num, 1.0 / m);
            if (k >= 2) {
                long long total = (long long)((pow(k, m + 1) - 1) / (k - 1));
                if (total == num) {
                    return to_string(k);
                }
            }
        }
        
        return to_string(num - 1);
    }
};