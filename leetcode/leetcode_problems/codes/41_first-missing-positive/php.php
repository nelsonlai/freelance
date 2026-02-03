class Solution {

    /**
     * @param Integer[] $nums
     * @return Integer
     */
    function firstMissingPositive($nums) {
        $n = count($nums);
        
        // Place each number in its correct position
        $i = 0;
        while ($i < $n) {
            $num = $nums[$i];
            if ($num >= 1 && $num <= $n && $nums[$num - 1] != $num) {
                $temp = $nums[$num - 1];
                $nums[$num - 1] = $num;
                $nums[$i] = $temp;
            } else {
                $i++;
            }
        }
        
        // Find the first missing positive
        for ($i = 0; $i < $n; $i++) {
            if ($nums[$i] != $i + 1) {
                return $i + 1;
            }
        }
        
        return $n + 1;
    }
}