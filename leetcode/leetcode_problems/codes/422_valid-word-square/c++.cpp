/*
 * Problem: Valid Word Square
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        int n = words.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < words[i].length(); j++) {
                if (j >= n || i >= words[j].length() || 
                    words[i][j] != words[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }
};