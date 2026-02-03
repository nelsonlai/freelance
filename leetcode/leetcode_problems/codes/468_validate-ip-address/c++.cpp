/*
 * Problem: Validate IP Address
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Solution {
private:
    bool isValidIPv4(string s) {
        stringstream ss(s);
        string part;
        int count = 0;
        
        while (getline(ss, part, '.')) {
            count++;
            if (part.empty() || (part.length() > 1 && part[0] == '0')) {
                return false;
            }
            try {
                int num = stoi(part);
                if (num < 0 || num > 255) {
                    return false;
                }
            } catch (...) {
                return false;
            }
        }
        return count == 4 && s.back() != '.';
    }
    
    bool isValidIPv6(string s) {
        stringstream ss(s);
        string part;
        int count = 0;
        
        while (getline(ss, part, ':')) {
            count++;
            if (part.empty() || part.length() > 4) {
                return false;
            }
            for (char c : part) {
                if (!isxdigit(c)) {
                    return false;
                }
            }
        }
        return count == 8 && s.back() != ':';
    }

public:
    string validIPAddress(string queryIP) {
        if (queryIP.find('.') != string::npos) {
            return isValidIPv4(queryIP) ? "IPv4" : "Neither";
        } else if (queryIP.find(':') != string::npos) {
            return isValidIPv6(queryIP) ? "IPv6" : "Neither";
        }
        return "Neither";
    }
};