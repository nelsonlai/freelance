/*
 * Problem: License Key Formatting
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        s.erase(remove(s.begin(), s.end(), '-'), s.end());
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        
        int n = s.length();
        int firstGroup = n % k != 0 ? n % k : k;
        string result = s.substr(0, firstGroup);
        
        for (int i = firstGroup; i < n; i += k) {
            result += "-" + s.substr(i, k);
        }
        
        return result;
    }
};