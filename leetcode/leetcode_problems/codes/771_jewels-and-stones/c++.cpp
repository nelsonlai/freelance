#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        unordered_set<char> jewelSet(jewels.begin(), jewels.end());
        int count = 0;
        for (char c : stones) {
            if (jewelSet.find(c) != jewelSet.end()) {
                count++;
            }
        }
        return count;
    }
};
