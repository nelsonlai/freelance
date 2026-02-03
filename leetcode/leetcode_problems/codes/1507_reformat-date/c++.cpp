/*
 * Problem: Reformat Date
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

class Solution {
public:
    string reformatDate(string date) {
        map<string, string> months = {
            {"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"},
            {"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"},
            {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}
        };
        
        istringstream iss(date);
        string day_str, month_str, year;
        iss >> day_str >> month_str >> year;
        
        string day = day_str.substr(0, day_str.length() - 2);
        if (day.length() == 1) {
            day = "0" + day;
        }
        
        return year + "-" + months[month_str] + "-" + day;
    }
};