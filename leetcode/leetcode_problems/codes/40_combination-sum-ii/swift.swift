class Solution {
    func combinationSum2(_ candidates: [Int], _ target: Int) -> [[Int]] {
        let sorted = candidates.sorted()
        var result: [[Int]] = []
        var path: [Int] = []
        
        func backtrack(_ start: Int, _ remaining: Int) {
            if remaining == 0 {
                result.append(path)
                return
            }
            if remaining < 0 {
                return
            }
            
            for i in start..<sorted.count {
                if i > start && sorted[i] == sorted[i - 1] {
                    continue
                }
                path.append(sorted[i])
                backtrack(i + 1, remaining - sorted[i])
                path.removeLast()
            }
        }
        
        backtrack(0, target)
        return result
    }
}