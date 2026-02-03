class Solution {

    /**
     * @param String $num1
     * @param String $num2
     * @return String
     */
    function multiply($num1, $num2) {
        if ($num1 == "0" || $num2 == "0") {
            return "0";
        }
        
        $m = strlen($num1);
        $n = strlen($num2);
        $result = array_fill(0, $m + $n, 0);
        
        for ($i = $m - 1; $i >= 0; $i--) {
            for ($j = $n - 1; $j >= 0; $j--) {
                $mul = intval($num1[$i]) * intval($num2[$j]);
                $p1 = $i + $j;
                $p2 = $i + $j + 1;
                $total = $mul + $result[$p2];
                
                $result[$p2] = $total % 10;
                $result[$p1] += intval($total / 10);
            }
        }
        
        // Remove leading zeros
        $start = 0;
        while ($start < count($result) && $result[$start] == 0) {
            $start++;
        }
        
        $res = "";
        for ($i = $start; $i < count($result); $i++) {
            $res .= strval($result[$i]);
        }
        
        return $res;
    }
}