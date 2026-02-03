class Solution {
    func combinationSum(_ candidates: [Int], _ target: Int) -> [[Int]] {
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
            
            for i in start..<candidates.count {
                path.append(candidates[i])
                backtrack(i, remaining - candidates[i])
                path.removeLast()
            }
        }
        
        backtrack(0, target)
        return result
    }
}