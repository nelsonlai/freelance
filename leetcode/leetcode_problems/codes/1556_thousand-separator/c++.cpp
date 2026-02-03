/*
 * Problem: Thousand Separator
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string thousandSeparator(int n) {
        string s = to_string(n);
        string result;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (!result.empty() && (s.length() - 1 - i) % 3 == 0) {
                result += '.';
            }
            result += s[i];
        }
        reverse(result.begin(), result.end());
        return result;
    }
};