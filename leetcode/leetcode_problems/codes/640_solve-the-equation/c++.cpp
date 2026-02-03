/*
 * Problem: Solve the Equation
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
private:
    pair<int, int> parseSide(string side) {
        int coeff = 0, constant = 0;
        for (int i = 0; i < side.length(); i++) {
            if (side[i] == '+' || side[i] == '-') {
                if (i > 0) {
                    side.insert(i, " ");
                }
            }
        }
        
        stringstream ss(side);
        string token;
        while (ss >> token) {
            if (token.find('x') != string::npos) {
                string num = token;
                num.erase(remove(num.begin(), num.end(), 'x'), num.end());
                num.erase(remove(num.begin(), num.end(), '+'), num.end());
                int val = num.empty() || num == "-" ? (num == "-" ? -1 : 1) : stoi(num);
                coeff += val;
            } else {
                constant += stoi(token);
            }
        }
        
        return {coeff, constant};
    }

public:
    string solveEquation(string equation) {
        size_t pos = equation.find('=');
        string left = equation.substr(0, pos);
        string right = equation.substr(pos + 1);
        
        auto leftRes = parseSide(left);
        auto rightRes = parseSide(right);
        
        int coeff = leftRes.first - rightRes.first;
        int constant = rightRes.second - leftRes.second;
        
        if (coeff == 0) {
            return constant == 0 ? "Infinite solutions" : "No solution";
        }
        
        return "x=" + to_string(constant / coeff);
    }
};