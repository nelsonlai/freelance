class Solution {
    fun insert(intervals: Array<IntArray>, newInterval: IntArray): Array<IntArray> {
        val result = mutableListOf<IntArray>()
        var i = 0
        val newInterval = newInterval.copyOf()
        
        // Add all intervals before newInterval
        while (i < intervals.size && intervals[i][1] < newInterval[0]) {
            result.add(intervals[i])
            i++
        }
        
        // Merge overlapping intervals
        while (i < intervals.size && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = minOf(newInterval[0], intervals[i][0])
            newInterval[1] = maxOf(newInterval[1], intervals[i][1])
            i++
        }
        
        result.add(newInterval)
        
        // Add remaining intervals
        while (i < intervals.size) {
            result.add(intervals[i])
            i++
        }
        
        return result.toTypedArray()
    }
}