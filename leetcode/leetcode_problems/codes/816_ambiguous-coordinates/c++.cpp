#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<string> generate(string s) {
        vector<string> result;
        if (s.length() == 1) {
            result.push_back(s);
            return result;
        }
        if (s[0] != '0') {
            result.push_back(s);
        }
        for (int i = 1; i < s.length(); i++) {
            string left = s.substr(0, i);
            string right = s.substr(i);
            if ((left.length() == 1 || left[0] != '0') && right[right.length() - 1] != '0') {
                result.push_back(left + "." + right);
            }
        }
        return result;
    }

public:
    vector<string> ambiguousCoordinates(string s) {
        s = s.substr(1, s.length() - 2);
        int n = s.length();
        vector<string> result;
        
        for (int i = 1; i < n; i++) {
            vector<string> left = generate(s.substr(0, i));
            vector<string> right = generate(s.substr(i));
            for (string l : left) {
                for (string r : right) {
                    result.push_back("(" + l + ", " + r + ")");
                }
            }
        }
        return result;
    }
};
