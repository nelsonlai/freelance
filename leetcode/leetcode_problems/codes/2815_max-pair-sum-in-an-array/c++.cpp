/*
 * Problem: Max Pair Sum in an Array
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    int maxDigit(int num) {
        int max = 0;
        while (num > 0) {
            max = std::max(max, num % 10);
            num /= 10;
        }
        return max;
    }

public:
    int maxSum(vector<int>& nums) {
        unordered_map<int, int> maxDigitToNum;
        int result = -1;
        
        for (int num : nums) {
            int md = maxDigit(num);
            if (maxDigitToNum.find(md) != maxDigitToNum.end()) {
                result = max(result, maxDigitToNum[md] + num);
                maxDigitToNum[md] = max(maxDigitToNum[md], num);
            } else {
                maxDigitToNum[md] = num;
            }
        }
        
        return result;
    }
};