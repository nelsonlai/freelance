import java.util.*;

class Solution {
    public int rotatedDigits(int n) {
        Set<Integer> invalid = new HashSet<>(Arrays.asList(3, 4, 7));
        Set<Integer> good = new HashSet<>(Arrays.asList(2, 5, 6, 9));
        int result = 0;
        
        for (int num = 1; num <= n; num++) {
            Set<Integer> digits = new HashSet<>();
            int temp = num;
            while (temp > 0) {
                digits.add(temp % 10);
                temp /= 10;
            }
            
            boolean hasInvalid = false;
            for (int d : digits) {
                if (invalid.contains(d)) {
                    hasInvalid = true;
                    break;
                }
            }
            if (hasInvalid) continue;
            
            boolean hasGood = false;
            for (int d : digits) {
                if (good.contains(d)) {
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
}
