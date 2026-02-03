#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Solution {
private:
    string closest(string s) {
        int num = stoi(s, nullptr, 16);
        int q = num / 17;
        int r = num % 17;
        if (r > 8) {
            q++;
        }
        stringstream ss;
        ss << hex << setw(2) << setfill('0') << q;
        return ss.str();
    }

public:
    string similarRGB(string color) {
        return "#" + closest(color.substr(1, 2)) + 
               closest(color.substr(3, 2)) + 
               closest(color.substr(5, 2));
    }
};
