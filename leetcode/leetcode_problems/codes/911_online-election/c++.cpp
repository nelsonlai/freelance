#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class TopVotedCandidate {
private:
    vector<int> times;
    vector<int> leaders;
    
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        this->times = times;
        leaders.resize(persons.size());
        unordered_map<int, int> count;
        int leader = -1;
        
        for (int i = 0; i < persons.size(); i++) {
            count[persons[i]]++;
            if (count[persons[i]] >= count[leader]) {
                leader = persons[i];
            }
            leaders[i] = leader;
        }
    }
    
    int q(int t) {
        int idx = upper_bound(times.begin(), times.end(), t) - times.begin() - 1;
        return leaders[idx];
    }
};
