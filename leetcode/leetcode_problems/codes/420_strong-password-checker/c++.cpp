/*
 * Problem: Strong Password Checker
 * Difficulty: Hard
 * Tags: string, greedy, queue, heap
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.length();
        int missingTypes = 3;
        bool hasLower = false, hasUpper = false, hasDigit = false;
        
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        
        if (hasLower) missingTypes--;
        if (hasUpper) missingTypes--;
        if (hasDigit) missingTypes--;
        
        int replace = 0;
        int one = 0, two = 0;
        
        int i = 0;
        while (i < n) {
            int length = 1;
            while (i + length < n && password[i + length] == password[i]) {
                length++;
            }
            
            if (length >= 3) {
                replace += length / 3;
                if (length % 3 == 0) one++;
                else if (length % 3 == 1) two++;
            }
            
            i += length;
        }
        
        if (n < 6) {
            return max(missingTypes, 6 - n);
        } else if (n <= 20) {
            return max(missingTypes, replace);
        } else {
            int delete_count = n - 20;
            replace -= min(delete_count, one);
            replace -= min(max(delete_count - one, 0), two * 2) / 2;
            replace -= max(delete_count - one - 2 * two, 0) / 3;
            return delete_count + max(missingTypes, replace);
        }
    }
};