/*
 * Problem: Minimum Suffix Flips
 * Difficulty: Medium
 * Tags: string, greedy
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int minFlips(string target) {
        int flips = 0;
        char current = '0';
        for (char c : target) {
            if (c != current) {
                flips++;
                current = c;
            }
        }
        return flips;
    }
};