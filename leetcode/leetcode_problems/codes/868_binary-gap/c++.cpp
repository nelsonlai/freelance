class Solution {
public:
    int binaryGap(int n) {
        int last = -1;
        int result = 0;
        int i = 0;
        while (n > 0) {
            if (n & 1) {
                if (last != -1) {
                    result = max(result, i - last);
                }
                last = i;
            }
            n >>= 1;
            i++;
        }
        return result;
    }
};
