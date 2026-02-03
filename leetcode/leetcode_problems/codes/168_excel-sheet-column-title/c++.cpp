/*
 * Problem: Excel Sheet Column Title
 * Difficulty: Easy
 * Tags: string, math
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
    string convertToTitle(int columnNumber) {
        string result;
        
        while (columnNumber > 0) {
            columnNumber--;
            result += (char)('A' + columnNumber % 26);
            columnNumber /= 26;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};