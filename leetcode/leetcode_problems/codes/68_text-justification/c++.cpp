/*
 * Problem: Text Justification
 * Difficulty: Hard
 * Tags: array, string, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        
        while (i < words.size()) {
            vector<string> lineWords;
            int lineLength = 0;
            
            // Collect words for current line
            while (i < words.size() && lineLength + words[i].length() + lineWords.size() <= maxWidth) {
                lineWords.push_back(words[i]);
                lineLength += words[i].length();
                i++;
            }
            
            // Build the line
            if (i == words.size() || lineWords.size() == 1) {
                // Last line or single word: left-justified
                string line = lineWords[0];
                for (int j = 1; j < lineWords.size(); j++) {
                    line += ' ' + lineWords[j];
                }
                while (line.length() < maxWidth) {
                    line += ' ';
                }
                result.push_back(line);
            } else {
                // Distribute spaces
                int spacesNeeded = maxWidth - lineLength;
                int gaps = lineWords.size() - 1;
                int baseSpaces = spacesNeeded / gaps;
                int extraSpaces = spacesNeeded % gaps;
                
                string line = lineWords[0];
                for (int j = 1; j < lineWords.size(); j++) {
                    int spaces = baseSpaces + (j <= extraSpaces ? 1 : 0);
                    line += string(spaces, ' ') + lineWords[j];
                }
                result.push_back(line);
            }
        }
        
        return result;
    }
};