#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    int match(string& a, string& b) {
        int count = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] == b[i]) {
                count++;
            }
        }
        return count;
    }

public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        vector<string> words = wordlist;
        int matches = 0;
        while (matches < 6) {
            string guess = words[0];
            matches = master.guess(guess);
            vector<string> next;
            for (string word : words) {
                if (match(guess, word) == matches) {
                    next.push_back(word);
                }
            }
            words = next;
        }
    }
};
