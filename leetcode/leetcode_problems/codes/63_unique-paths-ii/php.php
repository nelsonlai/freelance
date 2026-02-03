class Solution {

    /**
     * @param Integer[][] $obstacleGrid
     * @return Integer
     */
    function uniquePathsWithObstacles($obstacleGrid) {
        $m = count($obstacleGrid);
        $n = count($obstacleGrid[0]);
        
        if ($obstacleGrid[0][0] == 1 || $obstacleGrid[$m - 1][$n - 1] == 1) {
            return 0;
        }
        
        $dp = array_fill(0, $n, 0);
        $dp[0] = 1;
        
        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                if ($obstacleGrid[$i][$j] == 1) {
                    $dp[$j] = 0;
                } else if ($j > 0) {
                    $dp[$j] += $dp[$j - 1];
                }
            }
        }
        
        return $dp[$n - 1];
    }
}