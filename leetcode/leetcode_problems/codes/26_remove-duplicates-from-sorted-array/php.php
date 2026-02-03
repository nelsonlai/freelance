class Solution {

    /**
     * @param Integer[] $nums
     * @return Integer
     */
    function removeDuplicates(&$nums) {
        if (empty($nums)) {
            return 0;
        }
        
        $writeIndex = 1;
        for ($i = 1; $i < count($nums); $i++) {
            if ($nums[$i] != $nums[$i - 1]) {
                $nums[$writeIndex] = $nums[$i];
                $writeIndex++;
            }
        }
        
        return $writeIndex;
    }
}