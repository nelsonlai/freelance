# @param {Integer} n
# @param {Integer} k
# @return {String}
def get_permutation(n, k)
    nums = (1..n).to_a
    fact = [1]
    (1...n).each do |i|
        fact << fact[i - 1] * i
    end
    
    k -= 1  # Convert to 0-indexed
    result = []
    
    (n - 1).downto(0) do |i|
        index = k / fact[i]
        result << nums.delete_at(index).to_s
        k %= fact[i]
    end
    
    result.join('')
end