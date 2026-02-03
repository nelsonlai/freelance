#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
private:
    long ipToInt(string ip) {
        stringstream ss(ip);
        string part;
        long result = 0;
        for (int i = 0; i < 4; i++) {
            getline(ss, part, '.');
            result = result * 256 + stol(part);
        }
        return result;
    }
    
    string intToIP(long x) {
        return to_string((x >> 24) & 255) + "." + 
               to_string((x >> 16) & 255) + "." + 
               to_string((x >> 8) & 255) + "." + 
               to_string(x & 255);
    }

public:
    vector<string> ipToCIDR(string ip, int n) {
        long start = ipToInt(ip);
        vector<string> result;
        
        while (n > 0) {
            int mask = max(33 - __builtin_ctzl(start), 33 - __builtin_ctz(n));
            mask = min(mask, 33 - __builtin_ctz(n));
            result.push_back(intToIP(start) + "/" + to_string(mask));
            long step = 1L << (32 - mask);
            start += step;
            n -= step;
        }
        
        return result;
    }
};
