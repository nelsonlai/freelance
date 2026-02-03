class Solution {

    /**
     * @param Integer[] $nums
     * @param Integer $target
     * @return Integer
     */
    function threeSumClosest($nums, $target) {
        sort($nums);
        $closestSum = $nums[0] + $nums[1] + $nums[2];
        
        for ($i = 0; $i < count($nums) - 2; $i++) {
            $left = $i + 1;
            $right = count($nums) - 1;
            
            while ($left < $right) {
                $currentSum = $nums[$i] + $nums[$left] + $nums[$right];
                if (abs($currentSum - $target) < abs($closestSum - $target)) {
                    $closestSum = $currentSum;
                }
                
                if ($currentSum < $target) {
                    $left++;
                } else if ($currentSum > $target) {
                    $right--;
                } else {
                    return $currentSum;
                }
            }
        }
        
        return $closestSum;
    }
}