/**
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
    public int id;
    public int importance;
    public List<Integer> subordinates;
};
*/

import java.util.*;

class Solution {
    public int getImportance(List<Employee> employees, int id) {
        Map<Integer, Employee> map = new HashMap<>();
        for (Employee emp : employees) {
            map.put(emp.id, emp);
        }
        
        return dfs(map, id);
    }
    
    private int dfs(Map<Integer, Employee> map, int id) {
        Employee emp = map.get(id);
        int total = emp.importance;
        
        for (int subId : emp.subordinates) {
            total += dfs(map, subId);
        }
        
        return total;
    }
}