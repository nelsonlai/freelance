/**
 * DATA STRUCTURES - Lesson 2: Stack and Queue
 * 
 * This lesson covers:
 * - Stack implementation (Array and Linked List)
 * - Queue implementation (Array and Linked List)
 * - Applications of Stack and Queue
 */

import java.util.*;

// ========== STACK USING ARRAY ==========

class ArrayStack {
    private int[] stack;
    private int top;
    private int capacity;
    
    public ArrayStack(int capacity) {
        this.capacity = capacity;
        this.stack = new int[capacity];
        this.top = -1;
    }
    
    public void push(int data) {
        if (isFull()) {
            System.out.println("Stack is full!");
            return;
        }
        stack[++top] = data;
    }
    
    public int pop() {
        if (isEmpty()) {
            System.out.println("Stack is empty!");
            return -1;
        }
        return stack[top--];
    }
    
    public int peek() {
        if (isEmpty()) {
            return -1;
        }
        return stack[top];
    }
    
    public boolean isEmpty() {
        return top == -1;
    }
    
    public boolean isFull() {
        return top == capacity - 1;
    }
    
    public void display() {
        if (isEmpty()) {
            System.out.println("Stack is empty");
            return;
        }
        System.out.print("Stack: ");
        for (int i = top; i >= 0; i--) {
            System.out.print(stack[i] + " ");
        }
        System.out.println();
    }
}

// ========== STACK USING LINKED LIST ==========

class StackNode {
    int data;
    StackNode next;
    
    public StackNode(int data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedStack {
    private StackNode top;
    
    public LinkedStack() {
        this.top = null;
    }
    
    public void push(int data) {
        StackNode newNode = new StackNode(data);
        newNode.next = top;
        top = newNode;
    }
    
    public int pop() {
        if (isEmpty()) {
            System.out.println("Stack is empty!");
            return -1;
        }
        int data = top.data;
        top = top.next;
        return data;
    }
    
    public int peek() {
        if (isEmpty()) {
            return -1;
        }
        return top.data;
    }
    
    public boolean isEmpty() {
        return top == null;
    }
    
    public void display() {
        if (isEmpty()) {
            System.out.println("Stack is empty");
            return;
        }
        System.out.print("Stack: ");
        StackNode current = top;
        while (current != null) {
            System.out.print(current.data + " ");
            current = current.next;
        }
        System.out.println();
    }
}

// ========== QUEUE USING ARRAY ==========

class ArrayQueue {
    private int[] queue;
    private int front;
    private int rear;
    private int size;
    private int capacity;
    
    public ArrayQueue(int capacity) {
        this.capacity = capacity;
        this.queue = new int[capacity];
        this.front = 0;
        this.rear = -1;
        this.size = 0;
    }
    
    public void enqueue(int data) {
        if (isFull()) {
            System.out.println("Queue is full!");
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = data;
        size++;
    }
    
    public int dequeue() {
        if (isEmpty()) {
            System.out.println("Queue is empty!");
            return -1;
        }
        int data = queue[front];
        front = (front + 1) % capacity;
        size--;
        return data;
    }
    
    public int peek() {
        if (isEmpty()) {
            return -1;
        }
        return queue[front];
    }
    
    public boolean isEmpty() {
        return size == 0;
    }
    
    public boolean isFull() {
        return size == capacity;
    }
    
    public void display() {
        if (isEmpty()) {
            System.out.println("Queue is empty");
            return;
        }
        System.out.print("Queue: ");
        int count = 0;
        int index = front;
        while (count < size) {
            System.out.print(queue[index] + " ");
            index = (index + 1) % capacity;
            count++;
        }
        System.out.println();
    }
}

// ========== QUEUE USING LINKED LIST ==========

class QueueNode {
    int data;
    QueueNode next;
    
    public QueueNode(int data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedQueue {
    private QueueNode front;
    private QueueNode rear;
    
    public LinkedQueue() {
        this.front = null;
        this.rear = null;
    }
    
    public void enqueue(int data) {
        QueueNode newNode = new QueueNode(data);
        if (rear == null) {
            front = rear = newNode;
            return;
        }
        rear.next = newNode;
        rear = newNode;
    }
    
    public int dequeue() {
        if (isEmpty()) {
            System.out.println("Queue is empty!");
            return -1;
        }
        int data = front.data;
        front = front.next;
        if (front == null) {
            rear = null;
        }
        return data;
    }
    
    public int peek() {
        if (isEmpty()) {
            return -1;
        }
        return front.data;
    }
    
    public boolean isEmpty() {
        return front == null;
    }
    
    public void display() {
        if (isEmpty()) {
            System.out.println("Queue is empty");
            return;
        }
        System.out.print("Queue: ");
        QueueNode current = front;
        while (current != null) {
            System.out.print(current.data + " ");
            current = current.next;
        }
        System.out.println();
    }
}

// ========== STACK APPLICATIONS ==========

import java.util.Stack;

class StackApplications {
    // Check if parentheses are balanced
    public static boolean isBalanced(String expression) {
        Stack<Character> stack = new Stack<>();
        for (char ch : expression.toCharArray()) {
            if (ch == '(' || ch == '[' || ch == '{') {
                stack.push(ch);
            } else if (ch == ')' || ch == ']' || ch == '}') {
                if (stack.isEmpty()) return false;
                char top = stack.pop();
                if ((ch == ')' && top != '(') ||
                    (ch == ']' && top != '[') ||
                    (ch == '}' && top != '{')) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }
    
    // Reverse a string using stack
    public static String reverseString(String str) {
        Stack<Character> stack = new Stack<>();
        for (char ch : str.toCharArray()) {
            stack.push(ch);
        }
        StringBuilder reversed = new StringBuilder();
        while (!stack.isEmpty()) {
            reversed.append(stack.pop());
        }
        return reversed.toString();
    }
}

// ========== MAIN CLASS ==========

public class StackAndQueue {
    public static void main(String[] args) {
        System.out.println("=== ARRAY STACK ===");
        ArrayStack arrayStack = new ArrayStack(5);
        arrayStack.push(10);
        arrayStack.push(20);
        arrayStack.push(30);
        arrayStack.display();
        System.out.println("Peek: " + arrayStack.peek());
        System.out.println("Pop: " + arrayStack.pop());
        arrayStack.display();
        
        System.out.println("\n=== LINKED STACK ===");
        LinkedStack linkedStack = new LinkedStack();
        linkedStack.push(100);
        linkedStack.push(200);
        linkedStack.push(300);
        linkedStack.display();
        System.out.println("Pop: " + linkedStack.pop());
        linkedStack.display();
        
        System.out.println("\n=== ARRAY QUEUE ===");
        ArrayQueue arrayQueue = new ArrayQueue(5);
        arrayQueue.enqueue(1);
        arrayQueue.enqueue(2);
        arrayQueue.enqueue(3);
        arrayQueue.display();
        System.out.println("Dequeue: " + arrayQueue.dequeue());
        arrayQueue.display();
        
        System.out.println("\n=== LINKED QUEUE ===");
        LinkedQueue linkedQueue = new LinkedQueue();
        linkedQueue.enqueue(10);
        linkedQueue.enqueue(20);
        linkedQueue.enqueue(30);
        linkedQueue.display();
        System.out.println("Dequeue: " + linkedQueue.dequeue());
        linkedQueue.display();
        
        System.out.println("\n=== STACK APPLICATIONS ===");
        System.out.println("Is '((()))' balanced? " + StackApplications.isBalanced("((()))"));
        System.out.println("Is '([{}])' balanced? " + StackApplications.isBalanced("([{}])"));
        System.out.println("Is '((())' balanced? " + StackApplications.isBalanced("((())"));
        
        System.out.println("Reverse 'Hello': " + StackApplications.reverseString("Hello"));
    }
}

