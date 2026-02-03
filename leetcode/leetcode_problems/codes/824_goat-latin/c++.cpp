#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    string toGoatLatin(string sentence) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        stringstream ss(sentence);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        
        string result = "";
        for (int i = 0; i < words.size(); i++) {
            string newWord;
            if (vowels.find(words[i][0]) != vowels.end()) {
                newWord = words[i] + "ma";
            } else {
                newWord = words[i].substr(1) + words[i][0] + "ma";
            }
            newWord += string(i + 1, 'a');
            if (i > 0) {
                result += " ";
            }
            result += newWord;
        }
        return result;
    }
};
