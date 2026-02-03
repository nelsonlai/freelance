/**
 * Problem: Flatten a Multilevel Doubly Linked List
 * Difficulty: Medium
 * Tags: search, linked_list
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/*
// Definition for a Node.
class Node {
    public int val;
    public Node prev;
    public Node next;
    public Node child;
};
*/

class Solution {
    public Node flatten(Node head) {
        if (head == null) {
            return null;
        }
        
        flattenHelper(head);
        return head;
    }
    
    private Node flattenHelper(Node node) {
        Node current = node;
        Node tail = node;
        
        while (current != null) {
            Node next = current.next;
            if (current.child != null) {
                Node childTail = flattenHelper(current.child);
                current.next = current.child;
                current.child.prev = current;
                childTail.next = next;
                if (next != null) {
                    next.prev = childTail;
                }
                current.child = null;
                tail = childTail;
            } else {
                tail = current;
            }
            current = next;
        }
        
        return tail;
    }
}