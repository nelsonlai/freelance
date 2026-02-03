class Solution {

    /**
     * @param String $s
     * @return String
     */
    function longestPalindrome($s) {
        if (empty($s)) return "";
        
        $start = 0;
        $maxLen = 1;
        
        $expandAroundCenter = function($left, $right) use (&$s) {
            while ($left >= 0 && $right < strlen($s) && $s[$left] == $s[$right]) {
                $left--;
                $right++;
            }
            return $right - $left - 1;
        };
        
        for ($i = 0; $i < strlen($s); $i++) {
            $len1 = $expandAroundCenter($i, $i);
            $len2 = $expandAroundCenter($i, $i + 1);
            $len = max($len1, $len2);
            
            if ($len > $maxLen) {
                $start = $i - intval(($len - 1) / 2);
                $maxLen = $len;
            }
        }
        
        return substr($s, $start, $maxLen);
    }
}