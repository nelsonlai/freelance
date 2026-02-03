/*
 * Problem: Fraction to Recurring Decimal
 * Difficulty: Medium
 * Tags: string, math, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }
        
        string result;
        if ((numerator < 0) ^ (denominator < 0)) {
            result += "-";
        }
        
        long num = abs((long) numerator);
        long den = abs((long) denominator);
        
        result += to_string(num / den);
        long remainder = num % den;
        
        if (remainder == 0) {
            return result;
        }
        
        result += ".";
        unordered_map<long, int> remainderMap;
        
        while (remainder != 0) {
            if (remainderMap.find(remainder) != remainderMap.end()) {
                result.insert(remainderMap[remainder], "(");
                result += ")";
                break;
            }
            
            remainderMap[remainder] = result.length();
            remainder *= 10;
            result += to_string(remainder / den);
            remainder %= den;
        }
        
        return result;
    }
};