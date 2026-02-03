import java.util.*;

class Solution {
    public List<Integer> splitIntoFibonacci(String num) {
        int n = num.length();
        
        for (int i = 1; i < Math.min(11, n); i++) {
            for (int j = i + 1; j < Math.min(i + 11, n); j++) {
                String first = num.substring(0, i);
                String second = num.substring(i, j);
                
                if ((first.length() > 1 && first.startsWith("0")) || 
                    (second.length() > 1 && second.startsWith("0"))) {
                    continue;
                }
                
                List<Integer> result = new ArrayList<>();
                try {
                    result.add(Integer.parseInt(first));
                    result.add(Integer.parseInt(second));
                } catch (NumberFormatException e) {
                    continue;
                }
                
                int k = j;
                while (k < n) {
                    long nextVal = (long)result.get(result.size() - 1) + result.get(result.size() - 2);
                    if (nextVal > Integer.MAX_VALUE) {
                        break;
                    }
                    String nextStr = String.valueOf(nextVal);
                    if (!num.substring(k).startsWith(nextStr)) {
                        break;
                    }
                    result.add((int)nextVal);
                    k += nextStr.length();
                }
                
                if (k == n && result.size() >= 3) {
                    return result;
                }
            }
        }
        return new ArrayList<>();
    }
}
