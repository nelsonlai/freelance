/*
 * Problem: Pascal's Triangle II
 * Difficulty: Easy
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row;
        row.push_back(1);
        
        for (int i = 1; i <= rowIndex; i++) {
            vector<int> newRow;
            newRow.push_back(1);
            for (int j = 1; j < i; j++) {
                newRow.push_back(row[j - 1] + row[j]);
            }
            newRow.push_back(1);
            row = newRow;
        }
        
        return row;
    }
};