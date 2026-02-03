#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morse = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
        unordered_set<string> seen;
        for (string word : words) {
            string code = "";
            for (char c : word) {
                code += morse[c - 'a'];
            }
            seen.insert(code);
        }
        return seen.size();
    }
};
