/*
 * Problem: Convert a Number to Hexadecimal
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
    string toHex(int num) {
        if (num == 0) {
            return "0";
        }
        
        char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        string result = "";
        
        unsigned int n = num;
        
        while (n > 0) {
            result += hexChars[n % 16];
            n /= 16;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};