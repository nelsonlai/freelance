/*
 * Problem: Unique Email Addresses
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Normalize each email by removing dots before @ and ignoring content after +
 * Time Complexity: O(n * m) where n is number of emails, m is average length
 * Space Complexity: O(n) for set of unique emails
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> unique;
        for (string& email : emails) {
            int atPos = email.find('@');
            string local = email.substr(0, atPos);
            string domain = email.substr(atPos + 1);
            
            // Remove dots and ignore content after +
            int plusPos = local.find('+');
            if (plusPos != string::npos) {
                local = local.substr(0, plusPos);
            }
            local.erase(remove(local.begin(), local.end(), '.'), local.end());
            
            unique.insert(local + "@" + domain);
        }
        return unique.size();
    }
};