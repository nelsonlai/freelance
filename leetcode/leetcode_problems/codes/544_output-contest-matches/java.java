/**
 * Problem: Output Contest Matches
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String findContestMatch(int n) {
        List<String> teams = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            teams.add(String.valueOf(i));
        }
        
        while (teams.size() > 1) {
            List<String> newTeams = new ArrayList<>();
            for (int i = 0; i < teams.size() / 2; i++) {
                newTeams.add("(" + teams.get(i) + "," + teams.get(teams.size() - 1 - i) + ")");
            }
            teams = newTeams;
        }
        
        return teams.get(0);
    }
}