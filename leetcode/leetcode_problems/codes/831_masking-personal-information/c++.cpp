#include <string>
#include <regex>
#include <algorithm>

using namespace std;

class Solution {
public:
    string maskPII(string s) {
        if (s.find('@') != string::npos) {
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            int at = s.find('@');
            return s.substr(0, 1) + "*****" + s.substr(at - 1, 1) + s.substr(at);
        } else {
            string digits = "";
            for (char c : s) {
                if (isdigit(c)) {
                    digits += c;
                }
            }
            if (digits.length() == 10) {
                return "***-***-" + digits.substr(digits.length() - 4);
            } else {
                return "+" + string(digits.length() - 10, '*') + "-***-***-" + digits.substr(digits.length() - 4);
            }
        }
    }
};
