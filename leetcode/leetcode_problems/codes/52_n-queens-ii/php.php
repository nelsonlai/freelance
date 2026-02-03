class Solution {

    /**
     * @param Integer $n
     * @return Integer
     */
    function totalNQueens($n) {
        $count = 0;
        $cols = [];
        $diag1 = [];
        $diag2 = [];
        
        $backtrack = function($row) use (&$count, &$cols, &$diag1, &$diag2, $n, &$backtrack) {
            if ($row == $n) {
                $count++;
                return;
            }
            
            for ($col = 0; $col < $n; $col++) {
                if (isset($cols[$col]) || isset($diag1[$row - $col]) || isset($diag2[$row + $col])) {
                    continue;
                }
                
                $cols[$col] = true;
                $diag1[$row - $col] = true;
                $diag2[$row + $col] = true;
                
                $backtrack($row + 1);
                
                unset($cols[$col]);
                unset($diag1[$row - $col]);
                unset($diag2[$row + $col]);
            }
        };
        
        $backtrack(0);
        return $count;
    }
}