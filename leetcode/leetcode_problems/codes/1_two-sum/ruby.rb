# @param {Integer[]} nums
# @param {Integer} target
# @return {Integer[]}
def two_sum(nums, target)
    map = {}
    nums.each_with_index do |num, i|
        complement = target - num
        if map.key?(complement)
            return [map[complement], i]
        end
        map[num] = i
    end
    []
end