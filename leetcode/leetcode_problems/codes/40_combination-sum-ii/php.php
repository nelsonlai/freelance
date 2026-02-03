class Solution {

    /**
     * @param Integer[] $candidates
     * @param Integer $target
     * @return Integer[][]
     */
    function combinationSum2($candidates, $target) {
        sort($candidates);
        $result = [];
        $path = [];
        $this->backtrack($candidates, $target, 0, $path, $result);
        return $result;
    }
    
    private function backtrack($candidates, $target, $start, &$path, &$result) {
        if ($target == 0) {
            $result[] = $path;
            return;
        }
        if ($target < 0) {
            return;
        }
        
        for ($i = $start; $i < count($candidates); $i++) {
            if ($i > $start && $candidates[$i] == $candidates[$i - 1]) {
                continue;
            }
            $path[] = $candidates[$i];
            $this->backtrack($candidates, $target - $candidates[$i], $i + 1, $path, $result);
            array_pop($path);
        }
    }
}