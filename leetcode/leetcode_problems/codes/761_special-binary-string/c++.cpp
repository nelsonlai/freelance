#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string makeLargestSpecial(string s) {
        int count = 0;
        int i = 0;
        vector<string> res;
        
        for (int j = 0; j < s.length(); j++) {
            count += s[j] == '1' ? 1 : -1;
            if (count == 0) {
                res.push_back("1" + makeLargestSpecial(s.substr(i + 1, j - i - 1)) + "0");
                i = j + 1;
            }
        }
        
        sort(res.rbegin(), res.rend());
        string result = "";
        for (string str : res) {
            result += str;
        }
        return result;
    }
};
