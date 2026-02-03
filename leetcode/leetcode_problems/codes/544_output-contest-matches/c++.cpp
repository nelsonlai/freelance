/*
 * Problem: Output Contest Matches
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string findContestMatch(int n) {
        vector<string> teams;
        for (int i = 1; i <= n; i++) {
            teams.push_back(to_string(i));
        }
        
        while (teams.size() > 1) {
            vector<string> newTeams;
            for (int i = 0; i < teams.size() / 2; i++) {
                newTeams.push_back("(" + teams[i] + "," + teams[teams.size() - 1 - i] + ")");
            }
            teams = newTeams;
        }
        
        return teams[0];
    }
};