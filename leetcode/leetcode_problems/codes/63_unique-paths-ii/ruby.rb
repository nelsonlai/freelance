# @param {Integer[][]} obstacle_grid
# @return {Integer}
def unique_paths_with_obstacles(obstacle_grid)
    m, n = obstacle_grid.length, obstacle_grid[0].length
    
    return 0 if obstacle_grid[0][0] == 1 || obstacle_grid[m - 1][n - 1] == 1
    
    dp = [0] * n
    dp[0] = 1
    
    (0...m).each do |i|
        (0...n).each do |j|
            if obstacle_grid[i][j] == 1
                dp[j] = 0
            elsif j > 0
                dp[j] += dp[j - 1]
            end
        end
    end
    
    dp[n - 1]
end