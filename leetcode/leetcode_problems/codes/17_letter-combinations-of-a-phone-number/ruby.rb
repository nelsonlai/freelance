# @param {String} digits
# @return {String[]}
def letter_combinations(digits)
    return [] if digits.empty?
    
    phone_map = {
        '2' => 'abc', '3' => 'def', '4' => 'ghi', '5' => 'jkl',
        '6' => 'mno', '7' => 'pqrs', '8' => 'tuv', '9' => 'wxyz'
    }
    
    result = []
    
    backtrack = lambda do |index, current|
        if index == digits.length
            result << current
            return
        end
        
        phone_map[digits[index]].each_char do |char|
            backtrack.call(index + 1, current + char)
        end
    end
    
    backtrack.call(0, "")
    result
end