# @param {Integer[]} nums
# @return {Integer[][]}
def permute(nums)
    result = []
    current = []
    used = Array.new(nums.length, false)
    
    backtrack = lambda do
        if current.length == nums.length
            result << current.dup
            return
        end
        
        nums.each_with_index do |num, i|
            next if used[i]
            used[i] = true
            current << num
            backtrack.call
            current.pop
            used[i] = false
        end
    end
    
    backtrack.call
    result
end