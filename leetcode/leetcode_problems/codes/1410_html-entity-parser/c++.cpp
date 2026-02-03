/*
 * Problem: HTML Entity Parser
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: Replace HTML entities with characters, process longest first
 * Time Complexity: O(n) where n is length of text
 * Space Complexity: O(n) for result
 */

#include <string>

using namespace std;

class Solution {
public:
    string entityParser(string text) {
        string result = text;
        size_t pos;
        
        while ((pos = result.find("&quot;")) != string::npos) {
            result.replace(pos, 6, "\"");
        }
        while ((pos = result.find("&apos;")) != string::npos) {
            result.replace(pos, 6, "'");
        }
        while ((pos = result.find("&amp;")) != string::npos) {
            result.replace(pos, 5, "&");
        }
        while ((pos = result.find("&gt;")) != string::npos) {
            result.replace(pos, 4, ">");
        }
        while ((pos = result.find("&lt;")) != string::npos) {
            result.replace(pos, 4, "<");
        }
        while ((pos = result.find("&frasl;")) != string::npos) {
            result.replace(pos, 7, "/");
        }
        
        return result;
    }
};