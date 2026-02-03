class Solution {
    public int primePalindrome(int n) {
        if (n <= 2) return 2;
        if (n <= 3) return 3;
        if (n <= 5) return 5;
        if (n <= 7) return 7;
        if (n <= 11) return 11;
        
        int length = String.valueOf(n).length();
        for (int l = length; l < 10; l++) {
            int start = (int)Math.pow(10, l / 2);
            int end = (int)Math.pow(10, (l + 1) / 2);
            for (int root = start; root < end; root++) {
                String s = String.valueOf(root);
                String palindrome = l % 2 == 0 ? s + new StringBuilder(s).reverse().toString() 
                                                : s + new StringBuilder(s.substring(0, s.length() - 1)).reverse().toString();
                int num = Integer.parseInt(palindrome);
                if (num >= n && isPrime(num)) {
                    return num;
                }
            }
        }
        return -1;
    }
    
    private boolean isPrime(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }
}
