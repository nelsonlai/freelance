/*
 * Problem: Crawler Log Folder
 * Difficulty: Easy
 * Tags: array, string, stack
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
    int minOperations(vector<string>& logs) {
        int depth = 0;
        for (string& log : logs) {
            if (log == "../") {
                if (depth > 0) {
                    depth--;
                }
            } else if (log != "./") {
                depth++;
            }
        }
        return depth;
    }
};