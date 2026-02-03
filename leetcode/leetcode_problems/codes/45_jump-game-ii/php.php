class Solution {

    /**
     * @param Integer[] $nums
     * @return Integer
     */
    function jump($nums) {
        $jumps = 0;
        $currentEnd = 0;
        $farthest = 0;
        
        for ($i = 0; $i < count($nums) - 1; $i++) {
            $farthest = max($farthest, $i + $nums[$i]);
            if ($i == $currentEnd) {
                $jumps++;
                $currentEnd = $farthest;
            }
        }
        
        return $jumps;
    }
}