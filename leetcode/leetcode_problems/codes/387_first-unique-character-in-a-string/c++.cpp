/*
 * Problem: First Unique Character in a String
 * Difficulty: Easy
 * Tags: string, hash, queue
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
    int firstUniqChar(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        for (int i = 0; i < s.length(); i++) {
            if (count[s[i]] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};