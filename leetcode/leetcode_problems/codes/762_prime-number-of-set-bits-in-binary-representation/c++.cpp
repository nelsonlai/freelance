#include <unordered_set>

using namespace std;

class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
        int result = 0;
        
        for (int num = left; num <= right; num++) {
            int bits = __builtin_popcount(num);
            if (primes.find(bits) != primes.end()) {
                result++;
            }
        }
        
        return result;
    }
};
