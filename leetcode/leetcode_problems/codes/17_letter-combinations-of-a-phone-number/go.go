// Problem: Letter Combinations of a Phone Number
// Difficulty: Medium
// Tags: string, hash
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

func letterCombinations(digits string) []string {
    if len(digits) == 0 {
        return []string{}
    }
    
    phoneMap := map[byte]string{
        '2': "abc", '3': "def", '4': "ghi", '5': "jkl",
        '6': "mno", '7': "pqrs", '8': "tuv", '9': "wxyz",
    }
    
    var result []string
    
    var backtrack func(int, string)
    backtrack = func(index int, current string) {
        if index == len(digits) {
            result = append(result, current)
            return
        }
        
        letters := phoneMap[digits[index]]
        for i := 0; i < len(letters); i++ {
            backtrack(index+1, current+string(letters[i]))
        }
    }
    
    backtrack(0, "")
    return result
}