/*
 * Problem: Find the Difference
 * Difficulty: Easy
 * Tags: string, hash, sort
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        unordered_map<char, int> sCount;
        for (char c : s) {
            sCount[c]++;
        }
        
        for (char c : t) {
            if (sCount[c] == 0) {
                return c;
            }
            sCount[c]--;
        }
        
        return ' ';
    }
};