class Solution {

    /**
     * @param String[] $strs
     * @return String[][]
     */
    function groupAnagrams($strs) {
        $groups = [];
        foreach ($strs as $s) {
            $chars = str_split($s);
            sort($chars);
            $key = implode('', $chars);
            if (!isset($groups[$key])) {
                $groups[$key] = [];
            }
            $groups[$key][] = $s;
        }
        return array_values($groups);
    }
}