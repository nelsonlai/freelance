/**
 * Definition for a singly-linked list.
 * class ListNode {
 *     public $val = 0;
 *     public $next = null;
 *     function __construct($val = 0, $next = null) {
 *         $this->val = $val;
 *         $this->next = $next;
 *     }
 * }
 */
class Solution {

    /**
     * @param ListNode[] $lists
     * @return ListNode
     */
    function mergeKLists($lists) {
        if (empty($lists)) {
            return null;
        }
        
        while (count($lists) > 1) {
            $merged = [];
            for ($i = 0; $i < count($lists); $i += 2) {
                $l1 = $lists[$i];
                $l2 = ($i + 1 < count($lists)) ? $lists[$i + 1] : null;
                $merged[] = $this->mergeTwo($l1, $l2);
            }
            $lists = $merged;
        }
        
        return $lists[0];
    }
    
    private function mergeTwo($l1, $l2) {
        $dummy = new ListNode(0);
        $current = $dummy;
        
        while ($l1 != null && $l2 != null) {
            if ($l1->val <= $l2->val) {
                $current->next = $l1;
                $l1 = $l1->next;
            } else {
                $current->next = $l2;
                $l2 = $l2->next;
            }
            $current = $current->next;
        }
        
        $current->next = $l1 != null ? $l1 : $l2;
        return $dummy->next;
    }
}