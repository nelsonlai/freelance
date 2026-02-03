/*
 * Problem: Sliding Window Median
 * Difficulty: Hard
 * Tags: array, hash, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<int> window(nums.begin(), nums.begin() + k);
        sort(window.begin(), window.end());
        
        vector<double> result;
        result.push_back(getMedian(window, k));
        
        for (int i = k; i < nums.size(); i++) {
            window.erase(find(window.begin(), window.end(), nums[i - k]));
            window.insert(lower_bound(window.begin(), window.end(), nums[i]), nums[i]);
            result.push_back(getMedian(window, k));
        }
        
        return result;
    }
    
private:
    double getMedian(vector<int>& window, int k) {
        if (k % 2 == 0) {
            return ((double)window[k/2-1] + window[k/2]) / 2.0;
        } else {
            return (double)window[k/2];
        }
    }
};