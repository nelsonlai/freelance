/*
 * Problem: Strobogrammatic Number
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char, char> map = {
            {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}
        };
        
        int left = 0, right = num.length() - 1;
        while (left <= right) {
            if (map.find(num[left]) == map.end() || map[num[left]] != num[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};