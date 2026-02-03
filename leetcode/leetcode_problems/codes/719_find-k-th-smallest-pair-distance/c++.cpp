#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int countPairs(vector<int>& nums, int mid) {
        int count = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); right++) {
            while (nums[right] - nums[left] > mid) {
                left++;
            }
            count += right - left;
        }
        return count;
    }

public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        
        int left = 0, right = nums[nums.size() - 1] - nums[0];
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (countPairs(nums, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};
