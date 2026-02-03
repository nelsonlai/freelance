# @param {Integer[][]} intervals
# @return {Integer[][]}
def merge(intervals)
    return [] if intervals.empty?
    
    intervals.sort_by! { |x| x[0] }
    result = [intervals[0]]
    
    (1...intervals.length).each do |i|
        current = intervals[i]
        last = result[-1]
        if current[0] <= last[1]
            last[1] = [last[1], current[1]].max
        else
            result << current
        end
    end
    
    result
end