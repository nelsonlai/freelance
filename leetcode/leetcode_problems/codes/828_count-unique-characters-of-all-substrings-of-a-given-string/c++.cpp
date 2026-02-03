#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    int uniqueLetterString(string s) {
        map<char, vector<int>> index;
        for (char c = 'A'; c <= 'Z'; c++) {
            index[c] = {-1, -1};
        }
        
        int result = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            int k = index[c][0], j = index[c][1];
            result += (i - j) * (j - k);
            index[c][0] = j;
            index[c][1] = i;
        }
        
        for (char c = 'A'; c <= 'Z'; c++) {
            int k = index[c][0], j = index[c][1];
            result += (s.length() - j) * (j - k);
        }
        
        return result;
    }
};
