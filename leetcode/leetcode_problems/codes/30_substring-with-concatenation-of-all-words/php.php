class Solution {

    /**
     * @param String $s
     * @param String[] $words
     * @return Integer[]
     */
    function findSubstring($s, $words) {
        $result = [];
        if (empty($s) || empty($words)) {
            return $result;
        }
        
        $wordLen = strlen($words[0]);
        $wordCount = [];
        foreach ($words as $word) {
            $wordCount[$word] = isset($wordCount[$word]) ? $wordCount[$word] + 1 : 1;
        }
        
        for ($i = 0; $i < $wordLen; $i++) {
            $left = $i;
            $seen = [];
            $count = 0;
            
            for ($j = $i; $j <= strlen($s) - $wordLen; $j += $wordLen) {
                $word = substr($s, $j, $wordLen);
                
                if (isset($wordCount[$word])) {
                    $seen[$word] = isset($seen[$word]) ? $seen[$word] + 1 : 1;
                    $count++;
                    
                    while ($seen[$word] > $wordCount[$word]) {
                        $leftWord = substr($s, $left, $wordLen);
                        $seen[$leftWord]--;
                        $count--;
                        $left += $wordLen;
                    }
                    
                    if ($count == count($words)) {
                        $result[] = $left;
                        $leftWord = substr($s, $left, $wordLen);
                        $seen[$leftWord]--;
                        $count--;
                        $left += $wordLen;
                    }
                } else {
                    $seen = [];
                    $count = 0;
                    $left = $j + $wordLen;
                }
            }
        }
        
        return $result;
    }
}