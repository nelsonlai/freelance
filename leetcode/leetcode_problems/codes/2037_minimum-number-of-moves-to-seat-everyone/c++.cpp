/*
 * Problem: Minimum Number of Moves to Seat Everyone
 * Difficulty: Easy
 * Tags: array, greedy, sort
 * 
 * Approach: Sort both arrays, match smallest student with smallest seat
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());
        
        int result = 0;
        for (int i = 0; i < seats.size(); i++) {
            result += abs(seats[i] - students[i]);
        }
        
        return result;
    }
};