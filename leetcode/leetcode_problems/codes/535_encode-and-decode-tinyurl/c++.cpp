/*
 * Problem: Encode and Decode TinyURL
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>
#include <random>

using namespace std;

class Solution {
private:
    unordered_map<string, string> urlMap;
    string base = "http://tinyurl.com/";
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    mt19937 gen;
    uniform_int_distribution<int> dis;

public:
    Solution() : gen(random_device{}()), dis(0, chars.length() - 1) {}

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        while (true) {
            string shortStr = "";
            for (int i = 0; i < 6; i++) {
                shortStr += chars[dis(gen)];
            }
            if (urlMap.find(shortStr) == urlMap.end()) {
                urlMap[shortStr] = longUrl;
                return base + shortStr;
            }
        }
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        string shortStr = shortUrl.substr(base.length());
        return urlMap.count(shortStr) ? urlMap[shortStr] : "";
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));