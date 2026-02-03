/*
 * Problem: Display Table of Food Orders in a Restaurant
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Group orders by table, count items per table, format output
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for orders map
 */

#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        map<int, map<string, int>> tables;
        set<string> foods;
        
        for (auto& order : orders) {
            int table = stoi(order[1]);
            string food = order[2];
            tables[table][food]++;
            foods.insert(food);
        }
        
        vector<vector<string>> result;
        vector<string> header;
        header.push_back("Table");
        for (string food : foods) {
            header.push_back(food);
        }
        result.push_back(header);
        
        for (auto& [table, foodCount] : tables) {
            vector<string> row;
            row.push_back(to_string(table));
            for (string food : foods) {
                row.push_back(to_string(foodCount[food]));
            }
            result.push_back(row);
        }
        
        return result;
    }
};