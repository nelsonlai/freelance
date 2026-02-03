class Solution {
    func getPermutation(_ n: Int, _ k: Int) -> String {
        var nums = Array(1...n)
        var fact = [1]
        for i in 1..<n {
            fact.append(fact[i - 1] * i)
        }
        
        var k = k - 1 // Convert to 0-indexed
        var result = ""
        
        for i in stride(from: n - 1, through: 0, by: -1) {
            let index = k / fact[i]
            result += String(nums[index])
            nums.remove(at: index)
            k %= fact[i]
        }
        
        return result
    }
}