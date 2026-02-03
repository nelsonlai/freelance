class Solution {

    /**
     * @param String $digits
     * @return String[]
     */
    function letterCombinations($digits) {
        if (empty($digits)) {
            return [];
        }
        
        $phoneMap = [
            '2' => 'abc', '3' => 'def', '4' => 'ghi', '5' => 'jkl',
            '6' => 'mno', '7' => 'pqrs', '8' => 'tuv', '9' => 'wxyz'
        ];
        
        $result = [];
        
        $backtrack = function($index, $current) use (&$backtrack, &$result, $digits, $phoneMap) {
            if ($index == strlen($digits)) {
                $result[] = $current;
                return;
            }
            
            $letters = $phoneMap[$digits[$index]];
            for ($i = 0; $i < strlen($letters); $i++) {
                $backtrack($index + 1, $current . $letters[$i]);
            }
        };
        
        $backtrack(0, "");
        return $result;
    }
}