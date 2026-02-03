class Solution {
    func merge(_ intervals: [[Int]]) -> [[Int]] {
        if intervals.isEmpty {
            return []
        }
        
        let sorted = intervals.sorted { $0[0] < $1[0] }
        var result = [sorted[0]]
        
        for i in 1..<sorted.count {
            let current = sorted[i]
            var last = result[result.count - 1]
            if current[0] <= last[1] {
                last[1] = max(last[1], current[1])
                result[result.count - 1] = last
            } else {
                result.append(current)
            }
        }
        
        return result
    }
}