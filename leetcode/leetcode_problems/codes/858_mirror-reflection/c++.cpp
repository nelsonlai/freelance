class Solution {
private:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

public:
    int mirrorReflection(int p, int q) {
        int g = gcd(p, q);
        p /= g;
        q /= g;
        
        if (q % 2 == 0) {
            return 0;
        }
        if (p % 2 == 0) {
            return 2;
        }
        return 1;
    }
};
