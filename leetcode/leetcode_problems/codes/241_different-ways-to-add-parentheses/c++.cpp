/*
 * Problem: Different Ways to Add Parentheses
 * Difficulty: Medium
 * Tags: string, dp, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> result;
        
        bool isNumber = true;
        for (char c : expression) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        if (isNumber) {
            result.push_back(stoi(expression));
            return result;
        }
        
        for (int i = 0; i < expression.length(); i++) {
            char c = expression[i];
            if (c == '+' || c == '-' || c == '*') {
                vector<int> left = diffWaysToCompute(expression.substr(0, i));
                vector<int> right = diffWaysToCompute(expression.substr(i + 1));
                
                for (int l : left) {
                    for (int r : right) {
                        if (c == '+') {
                            result.push_back(l + r);
                        } else if (c == '-') {
                            result.push_back(l - r);
                        } else {
                            result.push_back(l * r);
                        }
                    }
                }
            }
        }
        
        return result;
    }
};