/*
 * Problem: Number of Segments in a String
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    int countSegments(string s) {
        if (s.empty()) {
            return 0;
        }
        stringstream ss(s);
        string word;
        int count = 0;
        while (ss >> word) {
            count++;
        }
        return count;
    }
};