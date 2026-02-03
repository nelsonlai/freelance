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
     * @param ListNode $head
     * @return ListNode
     */
    function swapPairs($head) {
        $dummy = new ListNode(0);
        $dummy->next = $head;
        $prev = $dummy;
        
        while ($prev->next != null && $prev->next->next != null) {
            $first = $prev->next;
            $second = $prev->next->next;
            
            $prev->next = $second;
            $first->next = $second->next;
            $second->next = $first;
            
            $prev = $first;
        }
        
        return $dummy->next;
    }
}