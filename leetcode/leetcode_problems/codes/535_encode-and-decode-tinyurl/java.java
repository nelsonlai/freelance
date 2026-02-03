/**
 * Problem: Encode and Decode TinyURL
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

public class Codec {
    private Map<String, String> urlMap = new HashMap<>();
    private String base = "http://tinyurl.com/";
    private String chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    private Random random = new Random();

    // Encodes a URL to a shortened URL.
    public String encode(String longUrl) {
        while (true) {
            StringBuilder shortUrl = new StringBuilder();
            for (int i = 0; i < 6; i++) {
                shortUrl.append(chars.charAt(random.nextInt(chars.length())));
            }
            String shortStr = shortUrl.toString();
            if (!urlMap.containsKey(shortStr)) {
                urlMap.put(shortStr, longUrl);
                return base + shortStr;
            }
        }
    }

    // Decodes a shortened URL to its original URL.
    public String decode(String shortUrl) {
        String shortStr = shortUrl.replace(base, "");
        return urlMap.getOrDefault(shortStr, "");
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.decode(codec.encode(url));