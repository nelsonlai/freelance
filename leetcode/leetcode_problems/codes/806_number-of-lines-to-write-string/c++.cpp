#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int lines = 1;
        int current = 0;
        for (char c : s) {
            int width = widths[c - 'a'];
            if (current + width > 100) {
                lines++;
                current = width;
            } else {
                current += width;
            }
        }
        return {lines, current};
    }
};
