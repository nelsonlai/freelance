/*
 * Problem: Substring with Concatenation of All Words
 * Difficulty: Hard
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

using System.Collections.Generic;

public class Solution {
    public IList<int> FindSubstring(string s, string[] words) {
        IList<int> result = new List<int>();
        if (string.IsNullOrEmpty(s) || words == null || words.Length == 0) {
            return result;
        }
        
        int wordLen = words[0].Length;
        Dictionary<string, int> wordCount = new Dictionary<string, int>();
        foreach (string word in words) {
            wordCount[word] = wordCount.GetValueOrDefault(word, 0) + 1;
        }
        
        for (int i = 0; i < wordLen; i++) {
            int left = i;
            Dictionary<string, int> seen = new Dictionary<string, int>();
            int count = 0;
            
            for (int j = i; j <= s.Length - wordLen; j += wordLen) {
                string word = s.Substring(j, wordLen);
                
                if (wordCount.ContainsKey(word)) {
                    seen[word] = seen.GetValueOrDefault(word, 0) + 1;
                    count++;
                    
                    while (seen[word] > wordCount[word]) {
                        string leftWord = s.Substring(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                    
                    if (count == words.Length) {
                        result.Add(left);
                        string leftWord = s.Substring(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                } else {
                    seen.Clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return result;
    }
}