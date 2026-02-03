class Solution {

    /**
     * @param String[][] $board
     * @return NULL
     */
    function solveSudoku(&$board) {
        $this->solve($board);
    }
    
    private function solve(&$board) {
        for ($i = 0; $i < 9; $i++) {
            for ($j = 0; $j < 9; $j++) {
                if ($board[$i][$j] == '.') {
                    for ($num = '1'; $num <= '9'; $num++) {
                        if ($this->isValid($board, $i, $j, $num)) {
                            $board[$i][$j] = $num;
                            if ($this->solve($board)) {
                                return true;
                            }
                            $board[$i][$j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    private function isValid(&$board, $row, $col, $num) {
        for ($i = 0; $i < 9; $i++) {
            if ($board[$row][$i] == $num || $board[$i][$col] == $num) {
                return false;
            }
            if ($board[3 * intval($row / 3) + intval($i / 3)][3 * intval($col / 3) + $i % 3] == $num) {
                return false;
            }
        }
        return true;
    }
}