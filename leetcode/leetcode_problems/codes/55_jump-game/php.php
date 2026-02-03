class Solution {

    /**
     * @param Integer[] $nums
     * @return Boolean
     */
    function canJump($nums) {
        $farthest = 0;
        for ($i = 0; $i < count($nums); $i++) {
            if ($i > $farthest) {
                return false;
            }
            $farthest = max($farthest, $i + $nums[$i]);
            if ($farthest >= count($nums) - 1) {
                return true;
            }
        }
        return true;
    }
}