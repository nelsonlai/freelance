# @param {Integer} dividend
# @param {Integer} divisor
# @return {Integer}
def divide(dividend, divisor)
    if dividend == -2**31 && divisor == -1
        return 2**31 - 1
    end
    
    negative = (dividend < 0) != (divisor < 0)
    dvd = dividend.abs
    dvs = divisor.abs
    
    quotient = 0
    while dvd >= dvs
        temp = dvs
        multiple = 1
        while dvd >= (temp << 1)
            temp <<= 1
            multiple <<= 1
        end
        dvd -= temp
        quotient += multiple
    end
    
    negative ? -quotient : quotient
end