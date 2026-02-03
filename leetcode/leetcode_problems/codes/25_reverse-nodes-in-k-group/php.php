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
     * @param Integer $k
     * @return ListNode
     */
    function reverseKGroup($head, $k) {
        $current = $head;
        $count = 0;
        
        while ($current != null && $count < $k) {
            $current = $current->next;
            $count++;
        }
        
        if ($count == $k) {
            $current = $this->reverseKGroup($current, $k);
            
            while ($count > 0) {
                $next = $head->next;
                $head->next = $current;
                $current = $head;
                $head = $next;
                $count--;
            }
            $head = $current;
        }
        
        return $head;
    }
}