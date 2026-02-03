class Solution {

    /**
     * @param Integer $n
     * @return String[]
     */
    function generateParenthesis($n) {
        $result = [];
        
        $backtrack = function($current, $open, $close) use (&$backtrack, &$result, $n) {
            if (strlen($current) == 2 * $n) {
                $result[] = $current;
                return;
            }
            
            if ($open < $n) {
                $backtrack($current . '(', $open + 1, $close);
            }
            
            if ($close < $open) {
                $backtrack($current . ')', $open, $close + 1);
            }
        };
        
        $backtrack("", 0, 0);
        return $result;
    }
}