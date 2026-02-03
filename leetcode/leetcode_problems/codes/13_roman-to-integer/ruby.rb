# @param {String} s
# @return {Integer}
def roman_to_int(s)
    roman_map = {
        'I' => 1, 'V' => 5, 'X' => 10, 'L' => 50,
        'C' => 100, 'D' => 500, 'M' => 1000
    }
    
    result = 0
    (0...s.length).each do |i|
        current = roman_map[s[i]]
        if i < s.length - 1
            next_val = roman_map[s[i + 1]]
            if current < next_val
                result -= current
            else
                result += current
            end
        else
            result += current
        end
    end
    
    result
end