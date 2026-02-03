/**
 * Problem: The Number of Full Rounds You Have Played
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: Convert to minutes, round up login, round down logout, count 15-min intervals
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

class Solution {
    public int numberOfRounds(String loginTime, String logoutTime) {
        int login = toMinutes(loginTime);
        int logout = toMinutes(logoutTime);
        
        if (logout < login) {
            logout += 24 * 60;
        }
        
        login = ((login + 14) / 15) * 15;
        logout = (logout / 15) * 15;
        
        if (logout < login) {
            return 0;
        }
        
        return (logout - login) / 15;
    }
    
    private int toMinutes(String time) {
        String[] parts = time.split(":");
        return Integer.parseInt(parts[0]) * 60 + Integer.parseInt(parts[1]);
    }
}