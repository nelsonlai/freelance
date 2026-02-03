class Solution:
    def calculate(self, s: str) -> int:
        def evaluate(expr, i):
            stack = []
            num = 0
            sign = '+'
            
            while i < len(expr):
                char = expr[i]
                if char.isdigit():
                    num = num * 10 + int(char)
                elif char == '(':
                    num, i = evaluate(expr, i + 1)
                elif char in '+-*/)':
                    if sign == '+':
                        stack.append(num)
                    elif sign == '-':
                        stack.append(-num)
                    elif sign == '*':
                        stack.append(stack.pop() * num)
                    elif sign == '/':
                        stack.append(int(stack.pop() / num))
                    
                    if char == ')':
                        return sum(stack), i
                    
                    sign = char
                    num = 0
                i += 1
            
            if sign == '+':
                stack.append(num)
            elif sign == '-':
                stack.append(-num)
            elif sign == '*':
                stack.append(stack.pop() * num)
            elif sign == '/':
                stack.append(int(stack.pop() / num))
            
            return sum(stack), i
        
        result, _ = evaluate(s, 0)
        return result
