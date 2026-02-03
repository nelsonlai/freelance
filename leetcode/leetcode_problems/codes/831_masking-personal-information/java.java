import java.util.regex.*;

class Solution {
    public String maskPII(String s) {
        if (s.contains("@")) {
            s = s.toLowerCase();
            String[] parts = s.split("@");
            return parts[0].charAt(0) + "*****" + parts[0].charAt(parts[0].length() - 1) + "@" + parts[1];
        } else {
            String digits = s.replaceAll("[^0-9]", "");
            if (digits.length() == 10) {
                return "***-***-" + digits.substring(digits.length() - 4);
            } else {
                return "+" + "*".repeat(digits.length() - 10) + "-***-***-" + digits.substring(digits.length() - 4);
            }
        }
    }
}
