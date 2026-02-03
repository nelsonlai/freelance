# @param {String} s
# @return {Boolean}
def is_valid(s)
    stack = []
    mapping = {
        ')' => '(',
        '}' => '{',
        ']' => '['
    }
    
    s.each_char do |char|
        if mapping.key?(char)
            return false if stack.empty? || stack.pop != mapping[char]
        else
            stack.push(char)
        end
    end
    
    stack.empty?
end