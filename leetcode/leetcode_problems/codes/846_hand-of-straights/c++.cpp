#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) {
            return false;
        }
        
        map<int, int> count;
        for (int card : hand) {
            count[card]++;
        }
        
        for (auto& entry : count) {
            if (entry.second > 0) {
                int need = entry.second;
                for (int i = 0; i < groupSize; i++) {
                    if (count[entry.first + i] < need) {
                        return false;
                    }
                    count[entry.first + i] -= need;
                }
            }
        }
        return true;
    }
};
