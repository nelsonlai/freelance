class Solution {

    /**
     * @param String $a
     * @param String $b
     * @return String
     */
    function addBinary($a, $b) {
        $result = [];
        $carry = 0;
        $i = strlen($a) - 1;
        $j = strlen($b) - 1;
        
        while ($i >= 0 || $j >= 0 || $carry > 0) {
            $total = $carry;
            if ($i >= 0) {
                $total += intval($a[$i--]);
            }
            if ($j >= 0) {
                $total += intval($b[$j--]);
            }
            array_unshift($result, strval($total % 2));
            $carry = intval($total / 2);
        }
        
        return implode('', $result);
    }
}