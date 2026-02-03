#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
private:
    bool isPrime(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

public:
    int primePalindrome(int n) {
        if (n <= 2) return 2;
        if (n <= 3) return 3;
        if (n <= 5) return 5;
        if (n <= 7) return 7;
        if (n <= 11) return 11;
        
        int length = to_string(n).length();
        for (int l = length; l < 10; l++) {
            int start = pow(10, l / 2);
            int end = pow(10, (l + 1) / 2);
            for (int root = start; root < end; root++) {
                string s = to_string(root);
                string palindrome = l % 2 == 0 ? s + string(s.rbegin(), s.rend())
                                                : s + string(s.rbegin() + 1, s.rend());
                int num = stoi(palindrome);
                if (num >= n && isPrime(num)) {
                    return num;
                }
            }
        }
        return -1;
    }
};
