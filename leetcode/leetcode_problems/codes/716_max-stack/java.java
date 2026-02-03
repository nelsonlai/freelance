import java.util.*;

class MaxStack {
    private Stack<Integer> stack;
    private Stack<Integer> maxStack;

    public MaxStack() {
        stack = new Stack<>();
        maxStack = new Stack<>();
    }
    
    public void push(int x) {
        stack.push(x);
        if (maxStack.isEmpty() || x >= maxStack.peek()) {
            maxStack.push(x);
        }
    }
    
    public int pop() {
        int val = stack.pop();
        if (!maxStack.isEmpty() && val == maxStack.peek()) {
            maxStack.pop();
        }
        return val;
    }
    
    public int top() {
        return stack.peek();
    }
    
    public int peekMax() {
        return maxStack.peek();
    }
    
    public int popMax() {
        int maxVal = maxStack.peek();
        Stack<Integer> temp = new Stack<>();
        while (stack.peek() != maxVal) {
            temp.push(pop());
        }
        pop();
        while (!temp.isEmpty()) {
            push(temp.pop());
        }
        return maxVal;
    }
}
