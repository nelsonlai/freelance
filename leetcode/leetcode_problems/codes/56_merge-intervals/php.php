class Solution {

    /**
     * @param Integer[][] $intervals
     * @return Integer[][]
     */
    function merge($intervals) {
        if (empty($intervals)) {
            return [];
        }
        
        usort($intervals, function($a, $b) {
            return $a[0] - $b[0];
        });
        
        $result = [$intervals[0]];
        
        for ($i = 1; $i < count($intervals); $i++) {
            $current = $intervals[$i];
            $last = &$result[count($result) - 1];
            if ($current[0] <= $last[1]) {
                $last[1] = max($last[1], $current[1]);
            } else {
                $result[] = $current;
            }
        }
        
        return $result;
    }
}