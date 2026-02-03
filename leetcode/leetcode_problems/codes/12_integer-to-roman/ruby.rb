# @param {Integer} num
# @return {String}
def int_to_roman(num)
    values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
    symbols = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
    
    result = ""
    values.each_with_index do |value, i|
        count = num / value
        result += symbols[i] * count
        num %= value
    end
    
    result
end