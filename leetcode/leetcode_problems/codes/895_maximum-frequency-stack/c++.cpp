#include <unordered_map>
#include <stack>

using namespace std;

class FreqStack {
private:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> group;
    int maxFreq;

public:
    FreqStack() {
        maxFreq = 0;
    }
    
    void push(int val) {
        freq[val]++;
        int f = freq[val];
        maxFreq = max(maxFreq, f);
        group[f].push(val);
    }
    
    int pop() {
        int x = group[maxFreq].top();
        group[maxFreq].pop();
        freq[x]--;
        if (group[maxFreq].empty()) {
            maxFreq--;
        }
        return x;
    }
};
