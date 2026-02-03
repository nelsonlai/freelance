// Problem: Letter Combinations of a Phone Number
// Difficulty: Medium
// Tags: string, hash
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(n) for hash map

impl Solution {
    pub fn letter_combinations(digits: String) -> Vec<String> {
        if digits.is_empty() {
            return Vec::new();
        }
        
        let phone_map: std::collections::HashMap<char, &str> = [
            ('2', "abc"), ('3', "def"), ('4', "ghi"), ('5', "jkl"),
            ('6', "mno"), ('7', "pqrs"), ('8', "tuv"), ('9', "wxyz")
        ].iter().cloned().collect();
        
        let mut result = Vec::new();
        let chars: Vec<char> = digits.chars().collect();
        
        fn backtrack(
            index: usize,
            current: String,
            digits: &[char],
            phone_map: &std::collections::HashMap<char, &str>,
            result: &mut Vec<String>
        ) {
            if index == digits.len() {
                result.push(current);
                return;
            }
            
            if let Some(letters) = phone_map.get(&digits[index]) {
                for letter in letters.chars() {
                    let mut new_current = current.clone();
                    new_current.push(letter);
                    backtrack(index + 1, new_current, digits, phone_map, result);
                }
            }
        }
        
        backtrack(0, String::new(), &chars, &phone_map, &mut result);
        result
    }
}