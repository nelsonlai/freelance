class Solution {

    /**
     * @param Integer $n
     * @return String[][]
     */
    function solveNQueens($n) {
        $result = [];
        $board = array_fill(0, $n, array_fill(0, $n, '.'));
        $cols = [];
        $diag1 = [];
        $diag2 = [];
        
        $backtrack = function($row) use (&$result, &$board, &$cols, &$diag1, &$diag2, $n, &$backtrack) {
            if ($row == $n) {
                $solution = [];
                for ($i = 0; $i < $n; $i++) {
                    $solution[] = implode('', $board[$i]);
                }
                $result[] = $solution;
                return;
            }
            
            for ($col = 0; $col < $n; $col++) {
                if (isset($cols[$col]) || isset($diag1[$row - $col]) || isset($diag2[$row + $col])) {
                    continue;
                }
                
                $board[$row][$col] = 'Q';
                $cols[$col] = true;
                $diag1[$row - $col] = true;
                $diag2[$row + $col] = true;
                
                $backtrack($row + 1);
                
                $board[$row][$col] = '.';
                unset($cols[$col]);
                unset($diag1[$row - $col]);
                unset($diag2[$row + $col]);
            }
        };
        
        $backtrack(0);
        return $result;
    }
}