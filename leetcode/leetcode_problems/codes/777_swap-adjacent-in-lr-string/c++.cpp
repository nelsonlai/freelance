#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canTransform(string start, string end) {
        string s1 = start, s2 = end;
        s1.erase(remove(s1.begin(), s1.end(), 'X'), s1.end());
        s2.erase(remove(s2.begin(), s2.end(), 'X'), s2.end());
        if (s1 != s2) {
            return false;
        }
        
        int n = start.length();
        int i = 0, j = 0;
        
        while (i < n && j < n) {
            while (i < n && start[i] == 'X') {
                i++;
            }
            while (j < n && end[j] == 'X') {
                j++;
            }
            
            if (i == n || j == n) {
                return i == n && j == n;
            }
            
            if (start[i] != end[j]) {
                return false;
            }
            
            if (start[i] == 'L' && i < j) {
                return false;
            }
            if (start[i] == 'R' && i > j) {
                return false;
            }
            
            i++;
            j++;
        }
        
        return true;
    }
};
