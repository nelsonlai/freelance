#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int maxVal = -1;
        for (int i = 0; i < nums.size() - 2; i++) {
            maxVal = max(maxVal, nums[i]);
            if (maxVal > nums[i + 2]) {
                return false;
            }
        }
        return true;
    }
};
