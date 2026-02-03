class Solution {

    /**
     * @param String $s
     * @return Integer
     */
    function longestValidParentheses($s) {
        $stack = [-1];
        $maxLen = 0;
        
        for ($i = 0; $i < strlen($s); $i++) {
            if ($s[$i] == '(') {
                $stack[] = $i;
            } else {
                array_pop($stack);
                if (empty($stack)) {
                    $stack[] = $i;
                } else {
                    $maxLen = max($maxLen, $i - end($stack));
                }
            }
        }
        
        return $maxLen;
    }
}