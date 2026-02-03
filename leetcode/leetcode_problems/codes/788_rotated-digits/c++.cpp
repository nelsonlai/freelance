#include <unordered_set>

using namespace std;

class Solution {
public:
    int rotatedDigits(int n) {
        unordered_set<int> invalid = {3, 4, 7};
        unordered_set<int> good = {2, 5, 6, 9};
        int result = 0;
        
        for (int num = 1; num <= n; num++) {
            unordered_set<int> digits;
            int temp = num;
            while (temp > 0) {
                digits.insert(temp % 10);
                temp /= 10;
            }
            
            bool hasInvalid = false;
            for (int d : digits) {
                if (invalid.find(d) != invalid.end()) {
                    hasInvalid = true;
                    break;
                }
            }
            if (hasInvalid) continue;
            
            bool hasGood = false;
            for (int d : digits) {
                if (good.find(d) != good.end()) {
                    hasGood = true;
                    break;
                }
            }
            if (hasGood) {
                result++;
            }
        }
        
        return result;
    }
};
