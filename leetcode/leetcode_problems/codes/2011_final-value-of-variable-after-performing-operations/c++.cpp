/*
 * Problem: Final Value of Variable After Performing Operations
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Count increment and decrement operations
 * Time Complexity: O(n) where n is number of operations
 * Space Complexity: O(1)
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int x = 0;
        for (string& op : operations) {
            if (op.find('+') != string::npos) {
                x++;
            } else {
                x--;
            }
        }
        return x;
    }
};