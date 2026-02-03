// Problem: Roman to Integer
// Difficulty: Easy
// Tags: string, math, hash
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

func romanToInt(s string) int {
    romanMap := map[byte]int{
        'I': 1, 'V': 5, 'X': 10, 'L': 50,
        'C': 100, 'D': 500, 'M': 1000,
    }
    
    result := 0
    for i := 0; i < len(s); i++ {
        if i < len(s)-1 && romanMap[s[i]] < romanMap[s[i+1]] {
            result -= romanMap[s[i]]
        } else {
            result += romanMap[s[i]]
        }
    }
    
    return result
}