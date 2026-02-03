/*
LinkedList problems and solutions
 */

class LinkedList {
    // Define ListNode class
    static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) { val = x; }
    }

    // Append ListNode method
    public void appendNode(ListNode head, int val) {
        ListNode newNode = new ListNode(val);
        ListNode current = head;
        while (current.next != null) {
            current = current.next;
        }
        current.next = newNode;
    }

    // Insert new ListNode after value method
    public void insertAfter(ListNode head, int targetVal, int newVal) {
        ListNode current = head;
        while (current != null) {
            if (current.val == targetVal) {
                ListNode newNode = new ListNode(newVal);
                newNode.next = current.next;
                current.next = newNode;
                return;
            }
            current = current.next;
        }
    }
    
    // Delete ListNode method
    public ListNode deleteNode(ListNode head, int val) {
        if (head == null) return null;
        if (head.val == val) return head.next;
        ListNode current = head;
        while (current.next != null) {
            if (current.next.val == val) {
                current.next = current.next.next;
                return head;
            }
            current = current.next;
        }
        return head;
    }

    // Print ListNode method
    public void printList(ListNode head) {
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }

    // Example method: Reverse a linked list
    public ListNode reverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode nextTemp = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }
}