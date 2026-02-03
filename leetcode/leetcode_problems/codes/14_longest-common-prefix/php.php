class Solution {

    /**
     * @param String[] $strs
     * @return String
     */
    function longestCommonPrefix($strs) {
        if (empty($strs)) {
            return "";
        }
        
        for ($i = 0; $i < strlen($strs[0]); $i++) {
            $char = $strs[0][$i];
            for ($j = 1; $j < count($strs); $j++) {
                if ($i >= strlen($strs[$j]) || $strs[$j][$i] != $char) {
                    return substr($strs[0], 0, $i);
                }
            }
        }
        
        return $strs[0];
    }
}