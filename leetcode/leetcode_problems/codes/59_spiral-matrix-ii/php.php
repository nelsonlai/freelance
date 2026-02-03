class Solution {

    /**
     * @param Integer $n
     * @return Integer[][]
     */
    function generateMatrix($n) {
        $matrix = array_fill(0, $n, array_fill(0, $n, 0));
        $num = 1;
        $top = 0;
        $bottom = $n - 1;
        $left = 0;
        $right = $n - 1;
        
        while ($top <= $bottom && $left <= $right) {
            // Right
            for ($j = $left; $j <= $right; $j++) {
                $matrix[$top][$j] = $num++;
            }
            $top++;
            
            // Down
            for ($i = $top; $i <= $bottom; $i++) {
                $matrix[$i][$right] = $num++;
            }
            $right--;
            
            // Left
            if ($top <= $bottom) {
                for ($j = $right; $j >= $left; $j--) {
                    $matrix[$bottom][$j] = $num++;
                }
                $bottom--;
            }
            
            // Up
            if ($left <= $right) {
                for ($i = $bottom; $i >= $top; $i--) {
                    $matrix[$i][$left] = $num++;
                }
                $left++;
            }
        }
        
        return $matrix;
    }
}