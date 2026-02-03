/*
 * Problem: Delete Columns to Make Sorted
 * Difficulty: Easy
 * Tags: array, string, graph, sort
 * 
 * Approach: Check each column to see if it's sorted
 * Time Complexity: O(n * m) where n is number of strings, m is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int count = 0;
        int n = strs.size();
        int m = strs[0].length();
        
        for (int j = 0; j < m; j++) {
            for (int i = 1; i < n; i++) {
                if (strs[i][j] < strs[i-1][j]) {
                    count++;
                    break;
                }
            }
        }
        
        return count;
    }
};