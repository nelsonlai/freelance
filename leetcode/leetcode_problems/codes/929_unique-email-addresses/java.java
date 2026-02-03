/**
 * Problem: Unique Email Addresses
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Normalize each email by removing dots before @ and ignoring content after +
 * Time Complexity: O(n * m) where n is number of emails, m is average length
 * Space Complexity: O(n) for set of unique emails
 */

import java.util.*;

class Solution {
    public int numUniqueEmails(String[] emails) {
        Set<String> unique = new HashSet<>();
        for (String email : emails) {
            String[] parts = email.split("@");
            String local = parts[0];
            String domain = parts[1];
            
            // Remove dots and ignore content after +
            int plusIndex = local.indexOf('+');
            if (plusIndex != -1) {
                local = local.substring(0, plusIndex);
            }
            local = local.replace(".", "");
            
            unique.add(local + "@" + domain);
        }
        return unique.size();
    }
}