// Problem: Integer to Roman
// Difficulty: Medium
// Tags: string, math, hash
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

func intToRoman(num int) string {
    values := []int{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}
    symbols := []string{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}
    
    var result strings.Builder
    for i := 0; i < len(values); i++ {
        count := num / values[i]
        for j := 0; j < count; j++ {
            result.WriteString(symbols[i])
        }
        num %= values[i]
    }
    
    return result.String()
}