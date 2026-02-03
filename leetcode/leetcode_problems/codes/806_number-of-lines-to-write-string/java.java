class Solution {
    public int[] numberOfLines(int[] widths, String s) {
        int lines = 1;
        int current = 0;
        for (char c : s.toCharArray()) {
            int width = widths[c - 'a'];
            if (current + width > 100) {
                lines++;
                current = width;
            } else {
                current += width;
            }
        }
        return new int[]{lines, current};
    }
}
