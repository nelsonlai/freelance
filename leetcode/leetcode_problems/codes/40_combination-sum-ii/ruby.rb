# @param {Integer[]} candidates
# @param {Integer} target
# @return {Integer[][]}
def combination_sum2(candidates, target)
    candidates.sort!
    result = []
    path = []
    
    backtrack = lambda do |start, remaining|
        if remaining == 0
            result << path.dup
            return
        end
        if remaining < 0
            return
        end
        
        (start...candidates.length).each do |i|
            if i > start && candidates[i] == candidates[i - 1]
                next
            end
            path << candidates[i]
            backtrack.call(i + 1, remaining - candidates[i])
            path.pop
        end
    end
    
    backtrack.call(0, target)
    result
end