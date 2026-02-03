/*
 * Problem: Group Anagrams
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

using System.Collections.Generic;
using System.Linq;

public class Solution {
    public IList<IList<string>> GroupAnagrams(string[] strs) {
        Dictionary<string, List<string>> groups = new Dictionary<string, List<string>>();
        foreach (string s in strs) {
            char[] chars = s.ToCharArray();
            System.Array.Sort(chars);
            string key = new string(chars);
            if (!groups.ContainsKey(key)) {
                groups[key] = new List<string>();
            }
            groups[key].Add(s);
        }
        return groups.Values.ToList<IList<string>>();
    }
}