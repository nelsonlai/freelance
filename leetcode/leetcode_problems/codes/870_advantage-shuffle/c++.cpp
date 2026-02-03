#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        sort(nums1.begin(), nums1.end());
        vector<int> indices(n);
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return nums2[a] < nums2[b];
        });
        
        vector<int> result(n);
        int left = 0, right = n - 1;
        
        for (int num : nums1) {
            if (num > nums2[indices[left]]) {
                result[indices[left]] = num;
                left++;
            } else {
                result[indices[right]] = num;
                right--;
            }
        }
        
        return result;
    }
};
