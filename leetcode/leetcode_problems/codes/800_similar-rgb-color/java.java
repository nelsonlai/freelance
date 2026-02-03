class Solution {
    public String similarRGB(String color) {
        return "#" + closest(color.substring(1, 3)) + 
               closest(color.substring(3, 5)) + 
               closest(color.substring(5, 7));
    }
    
    private String closest(String s) {
        int num = Integer.parseInt(s, 16);
        int q = num / 17;
        int r = num % 17;
        if (r > 8) {
            q++;
        }
        return String.format("%02x", q);
    }
}
