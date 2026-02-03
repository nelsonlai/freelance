import java.util.*;

class Solution {
    public List<String> ipToCIDR(String ip, int n) {
        long start = ipToInt(ip);
        List<String> result = new ArrayList<>();
        
        while (n > 0) {
            int mask = Math.max(33 - Long.numberOfTrailingZeros(start), 33 - Integer.numberOfTrailingZeros(n));
            mask = Math.min(mask, 33 - Integer.numberOfTrailingZeros(n));
            result.add(intToIP(start) + "/" + mask);
            long step = 1L << (32 - mask);
            start += step;
            n -= step;
        }
        
        return result;
    }
    
    private long ipToInt(String ip) {
        String[] parts = ip.split("\\.");
        long result = 0;
        for (int i = 0; i < 4; i++) {
            result = result * 256 + Long.parseLong(parts[i]);
        }
        return result;
    }
    
    private String intToIP(long x) {
        return String.format("%d.%d.%d.%d", (x >> 24) & 255, (x >> 16) & 255, (x >> 8) & 255, x & 255);
    }
}
