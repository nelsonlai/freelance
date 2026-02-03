/*
 * Problem: Fraction Addition and Subtraction
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <regex>
#include <algorithm>

using namespace std;

class Solution {
private:
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

public:
    string fractionAddition(string expression) {
        regex pattern("([+-]?\\d+)/(\\d+)");
        sregex_iterator iter(expression.begin(), expression.end(), pattern);
        sregex_iterator end;
        
        long long numerator = 0;
        long long denominator = 1;
        
        for (; iter != end; ++iter) {
            long long num = stoll(iter->str(1));
            long long den = stoll(iter->str(2));
            numerator = numerator * den + num * denominator;
            denominator *= den;
        }
        
        if (numerator == 0) {
            return "0/1";
        }
        
        long long g = gcd(abs(numerator), denominator);
        numerator /= g;
        denominator /= g;
        
        return to_string(numerator) + "/" + to_string(denominator);
    }
};