class Solution {

    /**
     * @param Integer[] $nums
     * @param Integer $val
     * @return Integer
     */
    function removeElement(&$nums, $val) {
        $writeIndex = 0;
        for ($i = 0; $i < count($nums); $i++) {
            if ($nums[$i] != $val) {
                $nums[$writeIndex] = $nums[$i];
                $writeIndex++;
            }
        }
        return $writeIndex;
    }
}