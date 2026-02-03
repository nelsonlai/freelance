/*
 * Problem: Min Max Game
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        vector<int> arr = nums;
        
        while (arr.size() > 1) {
            vector<int> newArr;
            for (int i = 0; i < arr.size() / 2; i++) {
                if (i % 2 == 0) {
                    newArr.push_back(min(arr[2 * i], arr[2 * i + 1]));
                } else {
                    newArr.push_back(max(arr[2 * i], arr[2 * i + 1]));
                }
            }
            arr = newArr;
        }
        
        return arr[0];
    }
};