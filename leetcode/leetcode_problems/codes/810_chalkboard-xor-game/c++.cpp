#include <vector>

using namespace std;

class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int xor_val = 0;
        for (int num : nums) {
            xor_val ^= num;
        }
        return xor_val == 0 || nums.size() % 2 == 0;
    }
};
