# @param {Integer} n
# @return {String}
def count_and_say(n)
    return "1" if n == 1
    
    result = "1"
    (n - 1).times do
        new_result = ""
        i = 0
        while i < result.length
            count = 1
            while i + 1 < result.length && result[i] == result[i + 1]
                count += 1
                i += 1
            end
            new_result += count.to_s
            new_result += result[i]
            i += 1
        end
        result = new_result
    end
    
    result
end