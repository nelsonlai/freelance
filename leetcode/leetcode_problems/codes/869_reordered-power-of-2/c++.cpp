#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> countDigits(int n) {
        vector<int> count(10, 0);
        while (n > 0) {
            count[n % 10]++;
            n /= 10;
        }
        return count;
    }

public:
    bool reorderedPowerOf2(int n) {
        vector<int> count = countDigits(n);
        for (int i = 0; i < 31; i++) {
            if (count == countDigits(1 << i)) {
                return true;
            }
        }
        return false;
    }
};
