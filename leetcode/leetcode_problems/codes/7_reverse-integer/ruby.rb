# @param {Integer} x
# @return {Integer}
def reverse(x)
    INT_MAX = 2**31 - 1
    INT_MIN = -2**31
    
    result = 0
    
    while x != 0
        digit = x % 10
        x = (x / 10.0).truncate
        
        if result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)
            return 0
        end
        if result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8)
            return 0
        end
        
        result = result * 10 + digit
    end
    
    result
end