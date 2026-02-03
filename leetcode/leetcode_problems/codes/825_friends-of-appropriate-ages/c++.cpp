#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        unordered_map<int, int> count;
        for (int age : ages) {
            count[age]++;
        }
        
        int result = 0;
        for (auto& entryA : count) {
            int ageA = entryA.first;
            int countA = entryA.second;
            for (auto& entryB : count) {
                int ageB = entryB.first;
                int countB = entryB.second;
                if (ageB <= 0.5 * ageA + 7 || ageB > ageA || (ageB > 100 && ageA < 100)) {
                    continue;
                }
                result += countA * countB;
                if (ageA == ageB) {
                    result -= countA;
                }
            }
        }
        return result;
    }
};
