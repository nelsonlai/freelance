/*
 * Problem: Employee Importance
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    int dfs(unordered_map<int, Employee*>& map, int id) {
        Employee* emp = map[id];
        int total = emp->importance;
        
        for (int subId : emp->subordinates) {
            total += dfs(map, subId);
        }
        
        return total;
    }

public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, Employee*> map;
        for (Employee* emp : employees) {
            map[emp->id] = emp;
        }
        
        return dfs(map, id);
    }
};