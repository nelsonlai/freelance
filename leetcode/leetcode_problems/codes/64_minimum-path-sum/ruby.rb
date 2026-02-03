# @param {Integer[][]} grid
# @return {Integer}
def min_path_sum(grid)
    m, n = grid.length, grid[0].length
    dp = [Float::INFINITY] * n
    dp[0] = 0
    
    (0...m).each do |i|
        dp[0] += grid[i][0]
        (1...n).each do |j|
            dp[j] = [dp[j], dp[j - 1]].min + grid[i][j]
        end
    end
    
    dp[n - 1]
end