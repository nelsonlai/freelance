#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string digits = to_string(n);
        int marker = digits.length();
        
        for (int i = digits.length() - 1; i > 0; i--) {
            if (digits[i] < digits[i - 1]) {
                marker = i;
                digits[i - 1]--;
            }
        }
        
        for (int i = marker; i < digits.length(); i++) {
            digits[i] = '9';
        }
        
        return stoi(digits);
    }
};
