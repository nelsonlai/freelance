#include <vector>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        int n = num.length();
        
        for (int i = 1; i < min(11, n); i++) {
            for (int j = i + 1; j < min(i + 11, n); j++) {
                string first = num.substr(0, i);
                string second = num.substr(i, j - i);
                
                if ((first.length() > 1 && first[0] == '0') || 
                    (second.length() > 1 && second[0] == '0')) {
                    continue;
                }
                
                long firstVal = stol(first);
                long secondVal = stol(second);
                if (firstVal > INT_MAX || secondVal > INT_MAX) {
                    continue;
                }
                
                vector<int> result = {(int)firstVal, (int)secondVal};
                int k = j;
                
                while (k < n) {
                    long nextVal = (long)result[result.size() - 1] + result[result.size() - 2];
                    if (nextVal > INT_MAX) {
                        break;
                    }
                    string nextStr = to_string(nextVal);
                    if (num.substr(k).find(nextStr) != 0) {
                        break;
                    }
                    result.push_back((int)nextVal);
                    k += nextStr.length();
                }
                
                if (k == n && result.size() >= 3) {
                    return result;
                }
            }
        }
        return {};
    }
};
