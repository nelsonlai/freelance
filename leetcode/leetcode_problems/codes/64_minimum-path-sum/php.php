class Solution {

    /**
     * @param Integer[][] $grid
     * @return Integer
     */
    function minPathSum($grid) {
        $m = count($grid);
        $n = count($grid[0]);
        $dp = array_fill(0, $n, PHP_INT_MAX);
        $dp[0] = 0;
        
        for ($i = 0; $i < $m; $i++) {
            $dp[0] += $grid[$i][0];
            for ($j = 1; $j < $n; $j++) {
                $dp[$j] = min($dp[$j], $dp[$j - 1]) + $grid[$i][$j];
            }
        }
        
        return $dp[$n - 1];
    }
}