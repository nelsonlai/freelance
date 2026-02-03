class Solution {
    func lengthOfLastWord(_ s: String) -> Int {
        let trimmed = s.trimmingCharacters(in: .whitespaces)
        var length = 0
        for char in trimmed.reversed() {
            if char == " " {
                break
            }
            length += 1
        }
        return length
    }
}