class Solution {

    /**
     * @param String $s
     * @return Integer
     */
    function lengthOfLastWord($s) {
        $s = rtrim($s);
        $length = 0;
        for ($i = strlen($s) - 1; $i >= 0; $i--) {
            if ($s[$i] == ' ') {
                break;
            }
            $length++;
        }
        return $length;
    }
}