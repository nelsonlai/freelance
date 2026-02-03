#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        vector<string> reversed;
        for (string word : words) {
            reverse(word.begin(), word.end());
            reversed.push_back(word);
        }
        sort(reversed.begin(), reversed.end());
        
        int result = 0;
        for (int i = 0; i < reversed.size(); i++) {
            if (i + 1 < reversed.size() && reversed[i + 1].find(reversed[i]) == 0) {
                continue;
            }
            result += reversed[i].length() + 1;
        }
        return result;
    }
};
