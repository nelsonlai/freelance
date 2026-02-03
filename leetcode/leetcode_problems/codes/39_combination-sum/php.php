class Solution {

    /**
     * @param Integer[] $candidates
     * @param Integer $target
     * @return Integer[][]
     */
    function combinationSum($candidates, $target) {
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
            $path[] = $candidates[$i];
            $this->backtrack($candidates, $target - $candidates[$i], $i, $path, $result);
            array_pop($path);
        }
    }
}