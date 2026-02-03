class Solution {

    /**
     * @param Integer[] $nums
     * @return Integer[][]
     */
    function permuteUnique($nums) {
        sort($nums);
        $result = [];
        $current = [];
        $used = array_fill(0, count($nums), false);
        
        $backtrack = function() use (&$result, &$current, &$used, &$nums, &$backtrack) {
            if (count($current) == count($nums)) {
                $result[] = $current;
                return;
            }
            
            for ($i = 0; $i < count($nums); $i++) {
                if ($used[$i] || ($i > 0 && $nums[$i] == $nums[$i-1] && !$used[$i-1])) {
                    continue;
                }
                $used[$i] = true;
                $current[] = $nums[$i];
                $backtrack();
                array_pop($current);
                $used[$i] = false;
            }
        };
        
        $backtrack();
        return $result;
    }
}