# @param {String} num1
# @param {String} num2
# @return {String}
def multiply(num1, num2)
    return "0" if num1 == "0" || num2 == "0"
    
    m, n = num1.length, num2.length
    result = Array.new(m + n, 0)
    
    (m - 1).downto(0) do |i|
        (n - 1).downto(0) do |j|
            mul = num1[i].to_i * num2[j].to_i
            p1, p2 = i + j, i + j + 1
            total = mul + result[p2]
            
            result[p2] = total % 10
            result[p1] += total / 10
        end
    end
    
    # Remove leading zeros
    start = 0
    start += 1 while start < result.length && result[start] == 0
    
    result[start..-1].join
end