class Solution {
    public int superpalindromesInRange(String left, String right) {
        long L = Long.parseLong(left);
        long R = Long.parseLong(right);
        int count = 0;
        
        for (int i = 1; i < 100000; i++) {
            String s = String.valueOf(i);
            String rev = new StringBuilder(s).reverse().toString();
            
            long p1 = Long.parseLong(s + rev);
            long p1Sq = p1 * p1;
            if (p1Sq > R) break;
            if (p1Sq >= L && isPalindrome(String.valueOf(p1Sq))) {
                count++;
            }
            
            String rev2 = new StringBuilder(s.substring(0, s.length() - 1)).reverse().toString();
            long p2 = Long.parseLong(s + rev2);
            long p2Sq = p2 * p2;
            if (p2Sq >= L && p2Sq <= R && isPalindrome(String.valueOf(p2Sq))) {
                count++;
            }
        }
        
        return count;
    }
    
    private boolean isPalindrome(String s) {
        return s.equals(new StringBuilder(s).reverse().toString());
    }
}
