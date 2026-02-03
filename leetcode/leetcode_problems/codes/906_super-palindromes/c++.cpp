#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        long long L = stoll(left);
        long long R = stoll(right);
        int count = 0;
        
        for (int i = 1; i < 100000; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            
            long long p1 = stoll(s + rev);
            long long p1Sq = p1 * p1;
            if (p1Sq > R) break;
            if (p1Sq >= L && isPalindrome(to_string(p1Sq))) {
                count++;
            }
            
            if (s.length() > 1) {
                string rev2 = s.substr(0, s.length() - 1);
                reverse(rev2.begin(), rev2.end());
                long long p2 = stoll(s + rev2);
                long long p2Sq = p2 * p2;
                if (p2Sq >= L && p2Sq <= R && isPalindrome(to_string(p2Sq))) {
                    count++;
                }
            }
        }
        
        return count;
    }
    
private:
    bool isPalindrome(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        return s == rev;
    }
};
