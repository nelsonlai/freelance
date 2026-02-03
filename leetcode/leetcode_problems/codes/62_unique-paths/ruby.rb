# @param {Integer} m
# @param {Integer} n
# @return {Integer}
def unique_paths(m, n)
    dp = [1] * n
    
    (1...m).each do |i|
        (1...n).each do |j|
            dp[j] += dp[j - 1]
        end
    end
    
    dp[n - 1]
end