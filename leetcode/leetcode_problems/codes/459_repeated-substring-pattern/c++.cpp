/*
 * Problem: Repeated Substring Pattern
 * Difficulty: Easy
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>

using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.length();
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string pattern = s.substr(0, i);
                string repeated = "";
                for (int j = 0; j < n / i; j++) {
                    repeated += pattern;
                }
                if (repeated == s) {
                    return true;
                }
            }
        }
        return false;
    }
};