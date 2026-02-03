# @param {String} s
# @return {Integer}
def length_of_last_word(s)
    s = s.rstrip
    length = 0
    (s.length - 1).downto(0) do |i|
        if s[i] == ' '
            break
        end
        length += 1
    end
    length
end