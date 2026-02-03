class Solution {

    /**
     * @param Integer[] $prices
     * @return Integer
     */
    function maxProfit($prices) {
        if (empty($prices)) {
            return 0;
        }
        
        $minPrice = $prices[0];
        $maxProfit = 0;
        
        for ($i = 1; $i < count($prices); $i++) {
            $maxProfit = max($maxProfit, $prices[$i] - $minPrice);
            $minPrice = min($minPrice, $prices[$i]);
        }
        
        return $maxProfit;
    }
}