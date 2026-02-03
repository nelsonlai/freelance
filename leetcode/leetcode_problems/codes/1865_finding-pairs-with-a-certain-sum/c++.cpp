/*
 * Problem: Finding Pairs With a Certain Sum
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use hash map to count nums2, update on add
 * Time Complexity: O(1) for count, O(1) for add
 * Space Complexity: O(n)
 */

#include <vector>
#include <unordered_map>

using namespace std;

class FindSumPairs {
private:
    vector<int> nums1;
    vector<int> nums2;
    unordered_map<int, int> count2;
    
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this->nums1 = nums1;
        this->nums2 = nums2;
        for (int num : nums2) {
            count2[num]++;
        }
    }
    
    void add(int index, int val) {
        int oldVal = nums2[index];
        count2[oldVal]--;
        if (count2[oldVal] == 0) {
            count2.erase(oldVal);
        }
        
        int newVal = oldVal + val;
        nums2[index] = newVal;
        count2[newVal]++;
    }
    
    int count(int tot) {
        int result = 0;
        for (int num : nums1) {
            int target = tot - num;
            result += count2[target];
        }
        return result;
    }
};