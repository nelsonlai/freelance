# @param {Float} x
# @param {Integer} n
# @return {Float}
def my_pow(x, n)
    return 1.0 if n == 0
    
    if n < 0
        x = 1.0 / x
        n = -n
    end
    
    result = 1.0
    while n > 0
        if n % 2 == 1
            result *= x
        end
        x *= x
        n /= 2
    end
    
    result
end