# @param {String} s
# @return {Integer}
def my_atoi(s)
    s = s.strip
    return 0 if s.empty?
    
    sign = 1
    i = 0
    
    if s[0] == '-'
        sign = -1
        i = 1
    elsif s[0] == '+'
        i = 1
    end
    
    INT_MAX = 2**31 - 1
    INT_MIN = -2**31
    result = 0
    
    while i < s.length && s[i].match?(/\d/)
        digit = s[i].to_i
        if result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)
            return sign == 1 ? INT_MAX : INT_MIN
        end
        result = result * 10 + digit
        i += 1
    end
    
    sign * result
end