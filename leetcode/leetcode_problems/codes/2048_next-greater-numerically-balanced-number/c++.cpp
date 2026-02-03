/*
 * Problem: Next Greater Numerically Balanced Number
 * Difficulty: Medium
 * Tags: math, hash
 * 
 * Approach: Check numbers starting from n+1, verify if balanced
 * Time Complexity: O(n * log n) in worst case
 * Space Complexity: O(1)
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    bool isBalanced(int num) {
        vector<int> count(10, 0);
        string s = to_string(num);
        
        for (char c : s) {
            count[c - '0']++;
        }
        
        for (int i = 0; i < 10; i++) {
            if (count[i] > 0 && count[i] != i) {
                return false;
            }
        }
        
        return true;
    }
    
public:
    int nextBeautifulNumber(int n) {
        int num = n + 1;
        
        while (true) {
            if (isBalanced(num)) {
                return num;
            }
            num++;
        }
    }
};