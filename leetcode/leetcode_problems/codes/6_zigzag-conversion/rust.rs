// Problem: Zigzag Conversion
// Difficulty: Medium
// Tags: string
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

impl Solution {
    pub fn convert(s: String, num_rows: i32) -> String {
        let num_rows = num_rows as usize;
        if num_rows == 1 || num_rows >= s.len() {
            return s;
        }
        
        let mut rows: Vec<String> = vec![String::new(); num_rows];
        let mut current_row = 0;
        let mut going_down = false;
        
        for c in s.chars() {
            rows[current_row].push(c);
            if current_row == 0 || current_row == num_rows - 1 {
                going_down = !going_down;
            }
            if going_down {
                current_row += 1;
            } else {
                current_row -= 1;
            }
        }
        
        rows.join("")
    }
}