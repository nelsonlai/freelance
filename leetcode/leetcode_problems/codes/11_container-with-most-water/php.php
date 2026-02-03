class Solution {

    /**
     * @param Integer[] $height
     * @return Integer
     */
    function maxArea($height) {
        $left = 0;
        $right = count($height) - 1;
        $maxArea = 0;
        
        while ($left < $right) {
            $width = $right - $left;
            $area = $width * min($height[$left], $height[$right]);
            $maxArea = max($maxArea, $area);
            
            if ($height[$left] < $height[$right]) {
                $left++;
            } else {
                $right--;
            }
        }
        
        return $maxArea;
    }
}