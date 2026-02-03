class Solution {

    /**
     * @param Integer $n
     * @return String
     */
    function countAndSay($n) {
        if ($n == 1) {
            return "1";
        }
        
        $result = "1";
        for ($i = 1; $i < $n; $i++) {
            $newResult = "";
            $j = 0;
            while ($j < strlen($result)) {
                $count = 1;
                while ($j + 1 < strlen($result) && $result[$j] == $result[$j + 1]) {
                    $count++;
                    $j++;
                }
                $newResult .= $count;
                $newResult .= $result[$j];
                $j++;
            }
            $result = $newResult;
        }
        
        return $result;
    }
}