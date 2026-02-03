/*
 * Problem: Letter Combinations of a Phone Number
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

using System.Collections.Generic;
using System.Text;

public class Solution {
    private Dictionary<char, string> phoneMap = new Dictionary<char, string> {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
    };
    
    public IList<string> LetterCombinations(string digits) {
        IList<string> result = new List<string>();
        if (string.IsNullOrEmpty(digits)) {
            return result;
        }
        
        Backtrack(digits, 0, new StringBuilder(), result);
        return result;
    }
    
    private void Backtrack(string digits, int index, StringBuilder current, IList<string> result) {
        if (index == digits.Length) {
            result.Add(current.ToString());
            return;
        }
        
        string letters = phoneMap[digits[index]];
        foreach (char letter in letters) {
            current.Append(letter);
            Backtrack(digits, index + 1, current, result);
            current.Remove(current.Length - 1, 1);
        }
    }
}