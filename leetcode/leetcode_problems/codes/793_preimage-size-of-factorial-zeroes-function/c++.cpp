class Solution {
private:
    long trailingZeroes(long n) {
        long count = 0;
        while (n > 0) {
            n /= 5;
            count += n;
        }
        return count;
    }

public:
    int preimageSizeFZF(int k) {
        long left = 0, right = 5L * (k + 1);
        while (left < right) {
            long mid = (left + right) / 2;
            long zeros = trailingZeroes(mid);
            if (zeros < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        int count = 0;
        long n = left;
        while (trailingZeroes(n) == k) {
            count++;
            n++;
        }
        return count;
    }
};
