class Solution {

    /**
     * @param String $s
     * @return Integer
     */
    function lengthOfLongestSubstring($s) {
        $charIndex = [];
        $left = 0;
        $maxLen = 0;
        
        for ($right = 0; $right < strlen($s); $right++) {
            $c = $s[$right];
            if (isset($charIndex[$c]) && $charIndex[$c] >= $left) {
                $left = $charIndex[$c] + 1;
            }
            $charIndex[$c] = $right;
            $maxLen = max($maxLen, $right - $left + 1);
        }
        
        return $maxLen;
    }
}