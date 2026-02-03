/*
 * Problem: Number of Ways Where Square of Number Is Equal to Product of Two Numbers
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    long long countTriplets(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<long long, int> freq;
        for (long long num : arr2) {
            freq[num]++;
        }
        
        long long result = 0;
        for (long long num : arr1) {
            long long target = num * num;
            for (auto& [a, countA] : freq) {
                if (target % a == 0) {
                    long long b = target / a;
                    if (freq.find(b) != freq.end()) {
                        if (a == b) {
                            result += (long long)countA * (countA - 1);
                        } else {
                            result += (long long)countA * freq[b];
                        }
                    }
                }
            }
        }
        
        return result / 2;
    }
    
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        return (int)(countTriplets(nums1, nums2) + countTriplets(nums2, nums1));
    }
};