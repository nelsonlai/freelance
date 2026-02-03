#include <vector>

using namespace std;

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int ones = 0;
        for (int num : arr) {
            ones += num;
        }
        if (ones % 3 != 0) {
            return {-1, -1};
        }
        if (ones == 0) {
            return {0, 2};
        }
        
        int target = ones / 3;
        int first = -1, second = -1, third = -1;
        int count = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 1) {
                if (count == 0) first = i;
                else if (count == target) second = i;
                else if (count == 2 * target) third = i;
                count++;
            }
        }
        
        int n = arr.size();
        int length = n - third;
        
        if (first + length <= second && second + length <= third) {
            int i = first + length - 1;
            int j = second + length;
            if (equal(arr, first, second, length) && equal(arr, second, third, length)) {
                return {i, j};
            }
        }
        
        return {-1, -1};
    }
    
private:
    bool equal(vector<int>& arr, int i, int j, int length) {
        for (int k = 0; k < length; k++) {
            if (arr[i + k] != arr[j + k]) {
                return false;
            }
        }
        return true;
    }
};
