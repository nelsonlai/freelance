# @param {Integer[]} candidates
# @param {Integer} target
# @return {Integer[][]}
def combination_sum(candidates, target)
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
            path << candidates[i]
            backtrack.call(i, remaining - candidates[i])
            path.pop
        end
    end
    
    backtrack.call(0, target)
    result
end