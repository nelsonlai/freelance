class Solution {

    /**
     * @param Integer[][] $matrix
     * @return Integer[]
     */
    function spiralOrder($matrix) {
        if (empty($matrix) || empty($matrix[0])) {
            return [];
        }
        
        $result = [];
        $top = 0;
        $bottom = count($matrix) - 1;
        $left = 0;
        $right = count($matrix[0]) - 1;
        
        while ($top <= $bottom && $left <= $right) {
            // Right
            for ($j = $left; $j <= $right; $j++) {
                $result[] = $matrix[$top][$j];
            }
            $top++;
            
            // Down
            for ($i = $top; $i <= $bottom; $i++) {
                $result[] = $matrix[$i][$right];
            }
            $right--;
            
            // Left
            if ($top <= $bottom) {
                for ($j = $right; $j >= $left; $j--) {
                    $result[] = $matrix[$bottom][$j];
                }
                $bottom--;
            }
            
            // Up
            if ($left <= $right) {
                for ($i = $bottom; $i >= $top; $i--) {
                    $result[] = $matrix[$i][$left];
                }
                $left++;
            }
        }
        
        return $result;
    }
}