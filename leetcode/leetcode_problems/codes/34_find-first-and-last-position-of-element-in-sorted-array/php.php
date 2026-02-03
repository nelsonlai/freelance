class Solution {

    /**
     * @param Integer[] $nums
     * @param Integer $target
     * @return Integer[]
     */
    function searchRange($nums, $target) {
        $first = $this->findFirst($nums, $target);
        if ($first == -1) {
            return [-1, -1];
        }
        $last = $this->findLast($nums, $target);
        return [$first, $last];
    }
    
    private function findFirst($nums, $target) {
        $left = 0;
        $right = count($nums) - 1;
        $result = -1;
        while ($left <= $right) {
            $mid = intval(($left + $right) / 2);
            if ($nums[$mid] == $target) {
                $result = $mid;
                $right = $mid - 1;
            } else if ($nums[$mid] < $target) {
                $left = $mid + 1;
            } else {
                $right = $mid - 1;
            }
        }
        return $result;
    }
    
    private function findLast($nums, $target) {
        $left = 0;
        $right = count($nums) - 1;
        $result = -1;
        while ($left <= $right) {
            $mid = intval(($left + $right) / 2);
            if ($nums[$mid] == $target) {
                $result = $mid;
                $left = $mid + 1;
            } else if ($nums[$mid] < $target) {
                $left = $mid + 1;
            } else {
                $right = $mid - 1;
            }
        }
        return $result;
    }
}