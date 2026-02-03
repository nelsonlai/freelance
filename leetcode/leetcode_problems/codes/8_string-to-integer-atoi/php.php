class Solution {

    /**
     * @param String $s
     * @return Integer
     */
    function myAtoi($s) {
        $s = trim($s);
        if (empty($s)) {
            return 0;
        }
        
        $sign = 1;
        $i = 0;
        
        if ($s[0] == '-') {
            $sign = -1;
            $i = 1;
        } else if ($s[0] == '+') {
            $i = 1;
        }
        
        $INT_MAX = 2147483647;
        $INT_MIN = -2147483648;
        $result = 0;
        
        while ($i < strlen($s) && ctype_digit($s[$i])) {
            $digit = intval($s[$i]);
            if ($result > intval($INT_MAX / 10) || 
                ($result == intval($INT_MAX / 10) && $digit > 7)) {
                return $sign == 1 ? $INT_MAX : $INT_MIN;
            }
            $result = $result * 10 + $digit;
            $i++;
        }
        
        return $sign * $result;
    }
}