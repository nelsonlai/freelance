# @param {String} a
# @param {String} b
# @return {String}
def add_binary(a, b)
    result = []
    carry = 0
    i, j = a.length - 1, b.length - 1
    
    while i >= 0 || j >= 0 || carry > 0
        total = carry
        if i >= 0
            total += a[i].to_i
            i -= 1
        end
        if j >= 0
            total += b[j].to_i
            j -= 1
        end
        result << (total % 2).to_s
        carry = total / 2
    end
    
    result.reverse.join('')
end