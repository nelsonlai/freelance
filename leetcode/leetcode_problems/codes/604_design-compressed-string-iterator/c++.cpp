/*
 * Problem: Design Compressed String Iterator
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>
#include <regex>

using namespace std;

class StringIterator {
private:
    vector<char> chars;
    vector<int> counts;
    int index;

public:
    StringIterator(string compressedString) {
        regex pattern("([a-zA-Z])(\\d+)");
        sregex_iterator iter(compressedString.begin(), compressedString.end(), pattern);
        sregex_iterator end;
        
        for (; iter != end; ++iter) {
            chars.push_back(iter->str(1)[0]);
            counts.push_back(stoi(iter->str(2)));
        }
        
        index = 0;
    }
    
    char next() {
        if (!hasNext()) {
            return ' ';
        }
        
        char result = chars[index];
        counts[index]--;
        
        if (counts[index] == 0) {
            index++;
        }
        
        return result;
    }
    
    bool hasNext() {
        return index < chars.size() && counts[index] > 0;
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */