// Problem: Substring with Concatenation of All Words
// Difficulty: Hard
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

func findSubstring(s string, words []string) []int {
    result := []int{}
    if len(s) == 0 || len(words) == 0 {
        return result
    }
    
    wordLen := len(words[0])
    wordCount := make(map[string]int)
    for _, word := range words {
        wordCount[word]++
    }
    
    for i := 0; i < wordLen; i++ {
        left := i
        seen := make(map[string]int)
        count := 0
        
        for j := i; j <= len(s)-wordLen; j += wordLen {
            word := s[j : j+wordLen]
            
            if val, exists := wordCount[word]; exists {
                seen[word]++
                count++
                
                for seen[word] > val {
                    leftWord := s[left : left+wordLen]
                    seen[leftWord]--
                    count--
                    left += wordLen
                }
                
                if count == len(words) {
                    result = append(result, left)
                    leftWord := s[left : left+wordLen]
                    seen[leftWord]--
                    count--
                    left += wordLen
                }
            } else {
                seen = make(map[string]int)
                count = 0
                left = j + wordLen
            }
        }
    }
    
    return result
}