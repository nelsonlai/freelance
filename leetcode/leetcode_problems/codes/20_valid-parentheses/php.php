class Solution {

    /**
     * @param String $s
     * @return Boolean
     */
    function isValid($s) {
        $stack = [];
        $mapping = [
            ')' => '(',
            '}' => '{',
            ']' => '['
        ];
        
        for ($i = 0; $i < strlen($s); $i++) {
            $char = $s[$i];
            if (isset($mapping[$char])) {
                if (empty($stack) || array_pop($stack) !== $mapping[$char]) {
                    return false;
                }
            } else {
                array_push($stack, $char);
            }
        }
        
        return empty($stack);
    }
}