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
    function rotateRight($head, $k) {
        if ($head == null || $head->next == null || $k == 0) {
            return $head;
        }
        
        // Find length and get tail
        $length = 1;
        $tail = $head;
        while ($tail->next != null) {
            $tail = $tail->next;
            $length++;
        }
        
        $k = $k % $length;
        if ($k == 0) {
            return $head;
        }
        
        // Find new tail
        $newTail = $head;
        for ($i = 0; $i < $length - $k - 1; $i++) {
            $newTail = $newTail->next;
        }
        
        // Rotate
        $newHead = $newTail->next;
        $newTail->next = null;
        $tail->next = $head;
        
        return $newHead;
    }
}