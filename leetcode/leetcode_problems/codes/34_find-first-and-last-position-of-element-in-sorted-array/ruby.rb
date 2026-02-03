# @param {Integer[]} nums
# @param {Integer} target
# @return {Integer[]}
def search_range(nums, target)
    first = find_first(nums, target)
    return [-1, -1] if first == -1
    last = find_last(nums, target)
    [first, last]
end

def find_first(nums, target)
    left = 0
    right = nums.length - 1
    result = -1
    while left <= right
        mid = (left + right) / 2
        if nums[mid] == target
            result = mid
            right = mid - 1
        elsif nums[mid] < target
            left = mid + 1
        else
            right = mid - 1
        end
    end
    result
end

def find_last(nums, target)
    left = 0
    right = nums.length - 1
    result = -1
    while left <= right
        mid = (left + right) / 2
        if nums[mid] == target
            result = mid
            left = mid + 1
        elsif nums[mid] < target
            left = mid + 1
        else
            right = mid - 1
        end
    end
    result
end