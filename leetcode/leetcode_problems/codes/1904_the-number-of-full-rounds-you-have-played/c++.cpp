/*
 * Problem: The Number of Full Rounds You Have Played
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: Convert to minutes, round up login, round down logout, count 15-min intervals
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
private:
    int toMinutes(string time) {
        int pos = time.find(':');
        int h = stoi(time.substr(0, pos));
        int m = stoi(time.substr(pos + 1));
        return h * 60 + m;
    }
    
public:
    int numberOfRounds(string loginTime, string logoutTime) {
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
};