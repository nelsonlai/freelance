class Solution {

    /**
     * @param Integer $m
     * @param Integer $n
     * @return Integer
     */
    function uniquePaths($m, $n) {
        $dp = array_fill(0, $n, 1);
        
        for ($i = 1; $i < $m; $i++) {
            for ($j = 1; $j < $n; $j++) {
                $dp[$j] += $dp[$j - 1];
            }
        }
        
        return $dp[$n - 1];
    }
}