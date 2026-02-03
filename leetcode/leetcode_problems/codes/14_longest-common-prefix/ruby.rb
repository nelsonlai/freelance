# @param {String[]} strs
# @return {String}
def longest_common_prefix(strs)
    return "" if strs.empty?
    
    (0...strs[0].length).each do |i|
        char = strs[0][i]
        (1...strs.length).each do |j|
            if i >= strs[j].length || strs[j][i] != char
                return strs[0][0, i]
            end
        end
    end
    
    strs[0]
end