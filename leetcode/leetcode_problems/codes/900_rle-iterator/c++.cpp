#include <vector>

using namespace std;

class RLEIterator {
private:
    vector<int> encoding;
    int index;

public:
    RLEIterator(vector<int>& encoding) {
        this->encoding = encoding;
        this->index = 0;
    }
    
    int next(int n) {
        while (index < encoding.size()) {
            if (encoding[index] >= n) {
                encoding[index] -= n;
                return encoding[index + 1];
            }
            n -= encoding[index];
            index += 2;
        }
        return -1;
    }
};
