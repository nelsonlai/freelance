// Problem: Palindrome Number
// Difficulty: Easy
// Tags: string, math
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

func isPalindrome(x int) bool {
    if x < 0 || (x != 0 && x%10 == 0) {
        return false
    }
    
    reversedHalf := 0
    for x > reversedHalf {
        reversedHalf = reversedHalf*10 + x%10
        x /= 10
    }
    
    return x == reversedHalf || x == reversedHalf/10
}