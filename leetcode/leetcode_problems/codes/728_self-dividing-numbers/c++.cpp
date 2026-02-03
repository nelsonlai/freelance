#include <vector>

using namespace std;

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> result;
        for (int num = left; num <= right; num++) {
            int temp = num;
            bool valid = true;
            while (temp > 0) {
                int digit = temp % 10;
                if (digit == 0 || num % digit != 0) {
                    valid = false;
                    break;
                }
                temp /= 10;
            }
            if (valid) {
                result.push_back(num);
            }
        }
        return result;
    }
};
