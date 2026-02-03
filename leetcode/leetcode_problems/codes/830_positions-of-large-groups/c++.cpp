#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vector<int>> result;
        int i = 0;
        while (i < s.length()) {
            int j = i;
            while (j < s.length() && s[j] == s[i]) {
                j++;
            }
            if (j - i >= 3) {
                result.push_back({i, j - 1});
            }
            i = j;
        }
        return result;
    }
};
