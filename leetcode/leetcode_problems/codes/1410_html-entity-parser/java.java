/**
 * Problem: HTML Entity Parser
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: Replace HTML entities with characters, process longest first
 * Time Complexity: O(n) where n is length of text
 * Space Complexity: O(n) for result
 */

class Solution {
    public String entityParser(String text) {
        return text.replace("&quot;", "\"")
                   .replace("&apos;", "'")
                   .replace("&amp;", "&")
                   .replace("&gt;", ">")
                   .replace("&lt;", "<")
                   .replace("&frasl;", "/");
    }
}