object Solution {
    def insert(intervals: Array[Array[Int]], newInterval: Array[Int]): Array[Array[Int]] = {
        var result = List[Array[Int]]()
        var i = 0
        var newInterval = newInterval.clone()
        
        // Add all intervals before newInterval
        while (i < intervals.length && intervals(i)(1) < newInterval(0)) {
            result = intervals(i) :: result
            i += 1
        }
        
        // Merge overlapping intervals
        while (i < intervals.length && intervals(i)(0) <= newInterval(1)) {
            newInterval(0) = math.min(newInterval(0), intervals(i)(0))
            newInterval(1) = math.max(newInterval(1), intervals(i)(1))
            i += 1
        }
        
        result = newInterval :: result
        
        // Add remaining intervals
        while (i < intervals.length) {
            result = intervals(i) :: result
            i += 1
        }
        
        result.reverse.toArray
    }
}