class Solution {

    /**
     * @param Integer[][] $matrix
     * @return NULL
     */
    function rotate(&$matrix) {
        $n = count($matrix);
        // Transpose
        for ($i = 0; $i < $n; $i++) {
            for ($j = $i; $j < $n; $j++) {
                $temp = $matrix[$i][$j];
                $matrix[$i][$j] = $matrix[$j][$i];
                $matrix[$j][$i] = $temp;
            }
        }
        
        // Reverse each row
        for ($i = 0; $i < $n; $i++) {
            $matrix[$i] = array_reverse($matrix[$i]);
        }
    }
}