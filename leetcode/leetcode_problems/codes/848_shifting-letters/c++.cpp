#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        int n = s.length();
        long total = 0;
        string result = s;
        
        for (int i = n - 1; i >= 0; i--) {
            total = (total + shifts[i]) % 26;
            result[i] = (char)((s[i] - 'a' + total) % 26 + 'a');
        }
        
        return result;
    }
};
