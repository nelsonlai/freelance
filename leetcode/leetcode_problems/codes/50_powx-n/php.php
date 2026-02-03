class Solution {

    /**
     * @param Float $x
     * @param Integer $n
     * @return Float
     */
    function myPow($x, $n) {
        if ($n == 0) {
            return 1.0;
        }
        $N = $n;
        if ($N < 0) {
            $x = 1 / $x;
            $N = -$N;
        }
        
        $result = 1.0;
        while ($N > 0) {
            if ($N % 2 == 1) {
                $result *= $x;
            }
            $x *= $x;
            $N = intval($N / 2);
        }
        
        return $result;
    }
}