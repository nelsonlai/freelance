/*
 * Problem: Design Log Storage System
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

class LogSystem {
private:
    vector<pair<int, string>> logs;
    unordered_map<string, int> granularityMap;

public:
    LogSystem() {
        granularityMap["Year"] = 4;
        granularityMap["Month"] = 7;
        granularityMap["Day"] = 10;
        granularityMap["Hour"] = 13;
        granularityMap["Minute"] = 16;
        granularityMap["Second"] = 19;
    }
    
    void put(int id, string timestamp) {
        logs.push_back({id, timestamp});
    }
    
    vector<int> retrieve(string start, string end, string granularity) {
        int idx = granularityMap[granularity];
        string startPrefix = start.substr(0, idx);
        string endPrefix = end.substr(0, idx);
        
        vector<int> result;
        for (auto& log : logs) {
            string prefix = log.second.substr(0, idx);
            if (prefix >= startPrefix && prefix <= endPrefix) {
                result.push_back(log.first);
            }
        }
        
        return result;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(start,end,granularity);
 */