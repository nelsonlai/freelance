// Problem: Multiply Strings
// Difficulty: Medium
// Tags: string, math
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn multiply(num1: String, num2: String) -> String {
        if num1 == "0" || num2 == "0" {
            return "0".to_string();
        }
        
        let num1_bytes = num1.as_bytes();
        let num2_bytes = num2.as_bytes();
        let m = num1_bytes.len();
        let n = num2_bytes.len();
        let mut result = vec![0; m + n];
        
        for i in (0..m).rev() {
            for j in (0..n).rev() {
                let mul = (num1_bytes[i] - b'0') as i32 * (num2_bytes[j] - b'0') as i32;
                let p1 = i + j;
                let p2 = i + j + 1;
                let total = mul + result[p2];
                
                result[p2] = total % 10;
                result[p1] += total / 10;
            }
        }
        
        // Remove leading zeros
        let start = result.iter().position(|&x| x != 0).unwrap_or(0);
        result[start..].iter().map(|&x| (x as u8 + b'0') as char).collect()
    }
}