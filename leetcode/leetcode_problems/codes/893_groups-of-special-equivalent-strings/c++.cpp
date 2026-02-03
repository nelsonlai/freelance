#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numSpecialEquivGroups(vector<string>& words) {
        unordered_set<string> seen;
        for (string word : words) {
            string even = "", odd = "";
            for (int i = 0; i < word.length(); i++) {
                if (i % 2 == 0) {
                    even += word[i];
                } else {
                    odd += word[i];
                }
            }
            sort(even.begin(), even.end());
            sort(odd.begin(), odd.end());
            seen.insert(even + odd);
        }
        return seen.size();
    }
};
