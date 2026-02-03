class Solution {

    /**
     * @param Integer $dividend
     * @param Integer $divisor
     * @return Integer
     */
    function divide($dividend, $divisor) {
        if ($dividend == -2147483648 && $divisor == -1) {
            return 2147483647;
        }
        
        $negative = ($dividend < 0) != ($divisor < 0);
        $dvd = abs($dividend);
        $dvs = abs($divisor);
        
        $quotient = 0;
        while ($dvd >= $dvs) {
            $temp = $dvs;
            $multiple = 1;
            while ($dvd >= ($temp << 1)) {
                $temp <<= 1;
                $multiple <<= 1;
            }
            $dvd -= $temp;
            $quotient += $multiple;
        }
        
        return $negative ? -$quotient : $quotient;
    }
}