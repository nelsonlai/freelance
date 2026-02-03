#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> anagramMappings(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> mapping;
        for (int i = 0; i < nums2.size(); i++) {
            mapping[nums2[i]] = i;
        }
        
        vector<int> result;
        for (int num : nums1) {
            result.push_back(mapping[num]);
        }
        return result;
    }
};
