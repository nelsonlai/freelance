/*
 * Problem: Shuffle String
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        string result(s.length(), ' ');
        for (int i = 0; i < s.length(); i++) {
            result[indices[i]] = s[i];
        }
        return result;
    }
};