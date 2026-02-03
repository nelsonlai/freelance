# @param {Integer} x
# @return {Integer}
def my_sqrt(x)
    return x if x < 2
    
    # Newton's method: x_{n+1} = (x_n + S/x_n) / 2
    guess = x
    while guess * guess > x
        guess = (guess + x / guess) / 2
    end
    
    guess
end