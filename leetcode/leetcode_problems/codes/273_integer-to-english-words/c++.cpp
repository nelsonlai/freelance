/*
 * Problem: Integer to English Words
 * Difficulty: Hard
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    vector<string> ones = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    vector<string> teens = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> thousands = {"", "Thousand", "Million", "Billion"};
    
    string helper(int n) {
        if (n == 0) {
            return "";
        } else if (n < 10) {
            return ones[n] + " ";
        } else if (n < 20) {
            return teens[n - 10] + " ";
        } else if (n < 100) {
            return tens[n / 10] + " " + helper(n % 10);
        } else {
            return ones[n / 100] + " Hundred " + helper(n % 100);
        }
    }

public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }
        
        string result;
        int i = 0;
        
        while (num > 0) {
            if (num % 1000 != 0) {
                result = helper(num % 1000) + thousands[i] + " " + result;
            }
            num /= 1000;
            i++;
        }
        
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        return result;
    }
};