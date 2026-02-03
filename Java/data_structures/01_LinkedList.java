/**
 * DATA STRUCTURES - Lesson 1: Linked List Implementation
 * 
 * This lesson covers:
 * - Singly Linked List
 * - Doubly Linked List
 * - Basic operations (insert, delete, search, traverse)
 */

// ========== SINGLY LINKED LIST ==========

class Node {
    int data;
    Node next;
    
    public Node(int data) {
        this.data = data;
        this.next = null;
    }
}

class SinglyLinkedList {
    private Node head;
    
    public SinglyLinkedList() {
        this.head = null;
    }
    
    // Insert at the beginning
    public void insertAtBeginning(int data) {
        Node newNode = new Node(data);
        newNode.next = head;
        head = newNode;
    }
    
    // Insert at the end
    public void insertAtEnd(int data) {
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;
            return;
        }
        Node current = head;
        while (current.next != null) {
            current = current.next;
        }
        current.next = newNode;
    }
    
    // Insert at specific position
    public void insertAtPosition(int data, int position) {
        Node newNode = new Node(data);
        if (position == 0) {
            insertAtBeginning(data);
            return;
        }
        Node current = head;
        for (int i = 0; i < position - 1 && current != null; i++) {
            current = current.next;
        }
        if (current != null) {
            newNode.next = current.next;
            current.next = newNode;
        }
    }
    
    // Delete by value
    public boolean delete(int data) {
        if (head == null) return false;
        if (head.data == data) {
            head = head.next;
            return true;
        }
        Node current = head;
        while (current.next != null) {
            if (current.next.data == data) {
                current.next = current.next.next;
                return true;
            }
            current = current.next;
        }
        return false;
    }
    
    // Search
    public boolean search(int data) {
        Node current = head;
        while (current != null) {
            if (current.data == data) {
                return true;
            }
            current = current.next;
        }
        return false;
    }
    
    // Display
    public void display() {
        Node current = head;
        System.out.print("List: ");
        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }
    
    // Get size
    public int size() {
        int count = 0;
        Node current = head;
        while (current != null) {
            count++;
            current = current.next;
        }
        return count;
    }
    
    // Reverse the list
    public void reverse() {
        Node prev = null;
        Node current = head;
        Node next = null;
        
        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
}

// ========== DOUBLY LINKED LIST ==========

class DoublyNode {
    int data;
    DoublyNode next;
    DoublyNode prev;
    
    public DoublyNode(int data) {
        this.data = data;
        this.next = null;
        this.prev = null;
    }
}

class DoublyLinkedList {
    private DoublyNode head;
    private DoublyNode tail;
    
    public DoublyLinkedList() {
        this.head = null;
        this.tail = null;
    }
    
    // Insert at beginning
    public void insertAtBeginning(int data) {
        DoublyNode newNode = new DoublyNode(data);
        if (head == null) {
            head = tail = newNode;
            return;
        }
        newNode.next = head;
        head.prev = newNode;
        head = newNode;
    }
    
    // Insert at end
    public void insertAtEnd(int data) {
        DoublyNode newNode = new DoublyNode(data);
        if (tail == null) {
            head = tail = newNode;
            return;
        }
        newNode.prev = tail;
        tail.next = newNode;
        tail = newNode;
    }
    
    public void insertAtPosition(int data, int position) {
        DoublyNode newNode = new DoublyNode(data);
        if (position == 0) {
            insertAtBeginning(data);
            return;
        }
        DoublyNode current = head;
        for (int i = 0; i < position - 1 && current != null; i++) {
            current = current.next;
        }
        if (current != null) {
            newNode.next = current.next;
            newNode.prev = current;
            if (current.next != null) {
                current.next.prev = newNode;
            } else {
                tail = newNode; // Update tail if at the end
            }
            current.next = newNode;
        }
    }
    // Delete by value
    public boolean delete(int data) {
        DoublyNode current = head;
        while (current != null) {
            if (current.data == data) {
                if (current.prev != null) {
                    current.prev.next = current.next;
                } else {
                    head = current.next;
                }
                if (current.next != null) {
                    current.next.prev = current.prev;
                } else {
                    tail = current.prev;
                }
                return true;
            }
            current = current.next;
        }
        return false;
    }
    
    // Display forward
    public void displayForward() {
        DoublyNode current = head;
        System.out.print("Forward: ");
        while (current != null) {
            System.out.print(current.data + " <-> ");
            current = current.next;
        }
        System.out.println("null");
    }
    
    // Display backward
    public void displayBackward() {
        DoublyNode current = tail;
        System.out.print("Backward: ");
        while (current != null) {
            System.out.print(current.data + " <-> ");
            current = current.prev;
        }
        System.out.println("null");
    }
}

// ========== MAIN CLASS ==========

public class LinkedListExample {
    public static void main(String[] args) {
        System.out.println("=== SINGLY LINKED LIST ===");
        
        SinglyLinkedList sll = new SinglyLinkedList();
        sll.insertAtEnd(10);
        sll.insertAtEnd(20);
        sll.insertAtEnd(30);
        sll.insertAtBeginning(5);
        sll.insertAtPosition(15, 2);
        sll.display();
        System.out.println("Size: " + sll.size());
        
        System.out.println("\nSearch 20: " + sll.search(20));
        System.out.println("Search 100: " + sll.search(100));
        
        sll.delete(15);
        sll.display();
        
        System.out.println("\nReversing list...");
        sll.reverse();
        sll.display();
        
        System.out.println("\n=== DOUBLY LINKED LIST ===");
        
        DoublyLinkedList dll = new DoublyLinkedList();
        dll.insertAtEnd(10);
        dll.insertAtEnd(20);
        dll.insertAtEnd(30);
        dll.insertAtBeginning(5);
        dll.displayForward();
        dll.displayBackward();
        
        dll.delete(20);
        dll.displayForward();
    }
}

