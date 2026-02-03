/*
 * Problem: Sum of Digits of String After Convert
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Convert to numbers, sum digits k times
 * Time Complexity: O(n * k) where n is length
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
public:
    int getLucky(string s, int k) {
        string numStr;
        for (char c : s) {
            numStr += to_string(c - 'a' + 1);
        }
        
        for (int i = 0; i < k; i++) {
            long long sum = 0;
            for (char c : numStr) {
                sum += c - '0';
            }
            numStr = to_string(sum);
        }
        
        return stoi(numStr);
    }
};