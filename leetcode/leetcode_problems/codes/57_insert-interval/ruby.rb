# @param {Integer[][]} intervals
# @param {Integer[]} new_interval
# @return {Integer[][]}
def insert(intervals, new_interval)
    result = []
    i = 0
    new_interval = new_interval.dup
    
    # Add all intervals before newInterval
    while i < intervals.length && intervals[i][1] < new_interval[0]
        result << intervals[i]
        i += 1
    end
    
    # Merge overlapping intervals
    while i < intervals.length && intervals[i][0] <= new_interval[1]
        new_interval[0] = [new_interval[0], intervals[i][0]].min
        new_interval[1] = [new_interval[1], intervals[i][1]].max
        i += 1
    end
    
    result << new_interval
    
    # Add remaining intervals
    while i < intervals.length
        result << intervals[i]
        i += 1
    end
    
    result
end