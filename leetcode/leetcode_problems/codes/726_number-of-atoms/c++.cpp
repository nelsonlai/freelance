#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int i;
    string formula;
    
    map<string, int> parse() {
        map<string, int> count;
        while (i < formula.length()) {
            if (formula[i] == '(') {
                i++;
                map<string, int> inner = parse();
                i++;
                int num = getNum();
                for (auto& entry : inner) {
                    count[entry.first] += entry.second * num;
                }
            } else if (formula[i] == ')') {
                break;
            } else {
                string atom = getAtom();
                int num = getNum();
                count[atom] += num;
            }
        }
        return count;
    }
    
    string getAtom() {
        int start = i;
        i++;
        while (i < formula.length() && islower(formula[i])) {
            i++;
        }
        return formula.substr(start, i - start);
    }
    
    int getNum() {
        if (i >= formula.length() || !isdigit(formula[i])) {
            return 1;
        }
        int num = 0;
        while (i < formula.length() && isdigit(formula[i])) {
            num = num * 10 + (formula[i] - '0');
            i++;
        }
        return num;
    }

public:
    string countOfAtoms(string formula) {
        this->formula = formula;
        this->i = 0;
        map<string, int> count = parse();
        
        string result = "";
        for (auto& entry : count) {
            result += entry.first;
            if (entry.second > 1) {
                result += to_string(entry.second);
            }
        }
        return result;
    }
};
