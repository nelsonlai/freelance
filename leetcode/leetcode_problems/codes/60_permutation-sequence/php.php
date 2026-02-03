class Solution {

    /**
     * @param Integer $n
     * @param Integer $k
     * @return String
     */
    function getPermutation($n, $k) {
        $nums = range(1, $n);
        $fact = [1];
        for ($i = 1; $i < $n; $i++) {
            $fact[$i] = $fact[$i - 1] * $i;
        }
        
        $k--; // Convert to 0-indexed
        $result = '';
        
        for ($i = $n - 1; $i >= 0; $i--) {
            $index = intval($k / $fact[$i]);
            $result .= (string)$nums[$index];
            array_splice($nums, $index, 1);
            $k %= $fact[$i];
        }
        
        return $result;
    }
}