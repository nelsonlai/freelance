/*
 * Problem: Complex Number Multiplication
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
private:
    pair<int, int> parseComplex(string num) {
        num.pop_back();
        size_t pos = num.find('+');
        int real = stoi(num.substr(0, pos));
        int imag = stoi(num.substr(pos + 1));
        return {real, imag};
    }

public:
    string complexNumberMultiply(string num1, string num2) {
        auto a = parseComplex(num1);
        auto b = parseComplex(num2);
        
        int real = a.first * b.first - a.second * b.second;
        int imag = a.first * b.second + a.second * b.first;
        
        return to_string(real) + "+" + to_string(imag) + "i";
    }
};