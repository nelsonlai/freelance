class Solution {
    private int i;
    
    public int calculate(String s) {
        this.i = 0;
        return evaluate(s);
    }
    
    private int evaluate(String expr) {
        Stack<Integer> stack = new Stack<>();
        int num = 0;
        char sign = '+';
        
        while (i < expr.length()) {
            char c = expr.charAt(i);
            if (Character.isDigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '(') {
                i++;
                num = evaluate(expr);
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')') {
                if (sign == '+') {
                    stack.push(num);
                } else if (sign == '-') {
                    stack.push(-num);
                } else if (sign == '*') {
                    stack.push(stack.pop() * num);
                } else if (sign == '/') {
                    stack.push(stack.pop() / num);
                }
                
                if (c == ')') {
                    break;
                }
                
                sign = c;
                num = 0;
            }
            i++;
        }
        
        if (sign == '+') {
            stack.push(num);
        } else if (sign == '-') {
            stack.push(-num);
        } else if (sign == '*') {
            stack.push(stack.pop() * num);
        } else if (sign == '/') {
            stack.push(stack.pop() / num);
        }
        
        int result = 0;
        while (!stack.isEmpty()) {
            result += stack.pop();
        }
        return result;
    }
}
