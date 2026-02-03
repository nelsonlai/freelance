/*
 * Problem: Rearrange Spaces Between Words
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    string reorderSpaces(string text) {
        vector<string> words;
        istringstream iss(text);
        string word;
        while (iss >> word) {
            words.push_back(word);
        }
        
        int totalSpaces = 0;
        for (char c : text) {
            if (c == ' ') {
                totalSpaces++;
            }
        }
        
        if (words.size() == 1) {
            return words[0] + string(totalSpaces, ' ');
        }
        
        int spacesBetween = totalSpaces / (words.size() - 1);
        int spacesRemaining = totalSpaces % (words.size() - 1);
        
        string result;
        string spaceStr(spacesBetween, ' ');
        for (int i = 0; i < words.size(); i++) {
            if (i > 0) {
                result += spaceStr;
            }
            result += words[i];
        }
        result += string(spacesRemaining, ' ');
        
        return result;
    }
};