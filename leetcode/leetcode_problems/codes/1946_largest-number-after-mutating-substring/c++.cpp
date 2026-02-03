/*
 * Problem: Largest Number After Mutating Substring
 * Difficulty: Medium
 * Tags: array, string, greedy
 * 
 * Approach: Greedily mutate substring where change[i] > digit
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string maximumNumber(string num, vector<int>& change) {
        bool mutated = false;
        
        for (int i = 0; i < num.length(); i++) {
            int digit = num[i] - '0';
            if (change[digit] > digit) {
                num[i] = '0' + change[digit];
                mutated = true;
            } else if (change[digit] < digit && mutated) {
                break;
            }
        }
        
        return num;
    }
};