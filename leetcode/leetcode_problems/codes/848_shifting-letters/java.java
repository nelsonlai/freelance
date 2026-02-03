class Solution {
    public String shiftingLetters(String s, int[] shifts) {
        int n = s.length();
        long total = 0;
        char[] result = new char[n];
        
        for (int i = n - 1; i >= 0; i--) {
            total = (total + shifts[i]) % 26;
            result[i] = (char)((s.charAt(i) - 'a' + total) % 26 + 'a');
        }
        
        return new String(result);
    }
}
