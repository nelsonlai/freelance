class Solution {

    /**
     * @param String[][] $board
     * @return Boolean
     */
    function isValidSudoku($board) {
        $seen = [];
        
        for ($i = 0; $i < 9; $i++) {
            for ($j = 0; $j < 9; $j++) {
                if ($board[$i][$j] != '.') {
                    $num = $board[$i][$j];
                    $rowKey = "row-$i-$num";
                    $colKey = "col-$j-$num";
                    $boxKey = "box-" . intval($i / 3) . "-" . intval($j / 3) . "-$num";
                    
                    if (isset($seen[$rowKey]) || isset($seen[$colKey]) || isset($seen[$boxKey])) {
                        return false;
                    }
                    
                    $seen[$rowKey] = true;
                    $seen[$colKey] = true;
                    $seen[$boxKey] = true;
                }
            }
        }
        
        return true;
    }
}