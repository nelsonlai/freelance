class Solution {

    /**
     * @param Integer[] $nums
     * @return NULL
     */
    function nextPermutation(&$nums) {
        $i = count($nums) - 2;
        while ($i >= 0 && $nums[$i] >= $nums[$i + 1]) {
            $i--;
        }
        
        if ($i >= 0) {
            $j = count($nums) - 1;
            while ($nums[$j] <= $nums[$i]) {
                $j--;
            }
            list($nums[$i], $nums[$j]) = [$nums[$j], $nums[$i]];
        }
        
        $left = $i + 1;
        $right = count($nums) - 1;
        while ($left < $right) {
            list($nums[$left], $nums[$right]) = [$nums[$right], $nums[$left]];
            $left++;
            $right--;
        }
    }
}