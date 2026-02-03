object Solution {
    def merge(intervals: Array[Array[Int]]): Array[Array[Int]] = {
        if (intervals.isEmpty) {
            return Array.empty
        }
        
        val sorted = intervals.sortBy(_(0))
        var result = List[Array[Int]](sorted(0))
        
        for (i <- 1 until sorted.length) {
            val current = sorted(i)
            val last = result.head
            if (current(0) <= last(1)) {
                result = Array(last(0), math.max(last(1), current(1))) :: result.tail
            } else {
                result = current :: result
            }
        }
        
        result.reverse.toArray
    }
}