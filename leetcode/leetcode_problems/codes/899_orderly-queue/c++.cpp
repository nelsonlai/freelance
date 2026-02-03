#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k == 1) {
            string result = s;
            for (int i = 1; i < s.length(); i++) {
                string candidate = s.substr(i) + s.substr(0, i);
                if (candidate < result) {
                    result = candidate;
                }
            }
            return result;
        }
        sort(s.begin(), s.end());
        return s;
    }
};
