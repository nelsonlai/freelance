/**
 * Problem: Copy List with Random Pointer
 * Difficulty: Medium
 * Tags: hash, linked_list
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

import java.util.*;

/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

class Solution {
    public Node copyRandomList(Node head) {
        if (head == null) {
            return null;
        }
        
        Map<Node, Node> oldToNew = new HashMap<>();
        Node current = head;
        
        while (current != null) {
            oldToNew.put(current, new Node(current.val));
            current = current.next;
        }
        
        current = head;
        while (current != null) {
            oldToNew.get(current).next = oldToNew.get(current.next);
            oldToNew.get(current).random = oldToNew.get(current.random);
            current = current.next;
        }
        
        return oldToNew.get(head);
    }
}