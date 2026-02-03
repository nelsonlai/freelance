/*
 * Problem: Maximum Value after Insertion
 * Difficulty: Medium
 * Tags: string, greedy
 * 
 * Approach: Insert x at first position where it increases value
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>

using namespace std;

class Solution {
public:
    string maxValue(string n, int x) {
        bool isNegative = n[0] == '-';
        
        if (isNegative) {
            for (int i = 1; i < n.length(); i++) {
                if (n[i] - '0' > x) {
                    return n.substr(0, i) + to_string(x) + n.substr(i);
                }
            }
            return n + to_string(x);
        } else {
            for (int i = 0; i < n.length(); i++) {
                if (n[i] - '0' < x) {
                    return n.substr(0, i) + to_string(x) + n.substr(i);
                }
            }
            return n + to_string(x);
        }
    }
};