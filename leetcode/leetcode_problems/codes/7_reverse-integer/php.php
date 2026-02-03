class Solution {

    /**
     * @param Integer $x
     * @return Integer
     */
    function reverse($x) {
        $INT_MAX = 2147483647;
        $INT_MIN = -2147483648;
        $result = 0;
        
        while ($x != 0) {
            $digit = $x % 10;
            $x = intval($x / 10);
            
            if ($result > intval($INT_MAX / 10) || 
                ($result == intval($INT_MAX / 10) && $digit > 7)) {
                return 0;
            }
            if ($result < intval($INT_MIN / 10) || 
                ($result == intval($INT_MIN / 10) && $digit < -8)) {
                return 0;
            }
            
            $result = $result * 10 + $digit;
        }
        
        return $result;
    }
}