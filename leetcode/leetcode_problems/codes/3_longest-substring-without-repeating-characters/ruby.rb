# @param {String} s
# @return {Integer}
def length_of_longest_substring(s)
    char_index = {}
    left = 0
    max_len = 0
    
    s.each_char.with_index do |c, right|
        if char_index.key?(c) && char_index[c] >= left
            left = char_index[c] + 1
        end
        char_index[c] = right
        max_len = [max_len, right - left + 1].max
    end
    
    max_len
end