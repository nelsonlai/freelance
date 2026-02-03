#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> count;
        for (string cpdomain : cpdomains) {
            stringstream ss(cpdomain);
            int visits;
            string domain;
            ss >> visits >> domain;
            count[domain] += visits;
            for (int i = 0; i < domain.length(); i++) {
                if (domain[i] == '.') {
                    string subdomain = domain.substr(i + 1);
                    count[subdomain] += visits;
                }
            }
        }
        
        vector<string> result;
        for (auto& entry : count) {
            result.push_back(to_string(entry.second) + " " + entry.first);
        }
        return result;
    }
};
