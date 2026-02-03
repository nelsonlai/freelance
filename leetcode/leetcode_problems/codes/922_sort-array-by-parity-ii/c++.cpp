#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int evenIdx = 0;
        int oddIdx = 1;
        int n = nums.size();
        
        while (evenIdx < n && oddIdx < n) {
            if (nums[evenIdx] % 2 == 0) {
                evenIdx += 2;
            } else if (nums[oddIdx] % 2 == 1) {
                oddIdx += 2;
            } else {
                swap(nums[evenIdx], nums[oddIdx]);
                evenIdx += 2;
                oddIdx += 2;
            }
        }
        
        return nums;
    }
};
