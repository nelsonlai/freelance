from collections import ChainMap

class Solution:
    def evaluate(self, expression: str) -> int:
        def parse(expr, env):
            if expr[0] != '(':
                if expr[0].isdigit() or expr[0] == '-':
                    return int(expr)
                return env[expr]
            
            expr = expr[1:-1]
            tokens = tokenize(expr)
            
            if tokens[0] == 'add':
                return parse(tokens[1], env) + parse(tokens[2], env)
            elif tokens[0] == 'mult':
                return parse(tokens[1], env) * parse(tokens[2], env)
            else:
                newEnv = ChainMap({}, env)
                for i in range(1, len(tokens) - 1, 2):
                    newEnv[tokens[i]] = parse(tokens[i + 1], newEnv)
                return parse(tokens[-1], newEnv)
        
        def tokenize(expr):
            tokens = []
            i = 0
            while i < len(expr):
                if expr[i] == '(':
                    count = 0
                    j = i
                    while j < len(expr):
                        if expr[j] == '(':
                            count += 1
                        elif expr[j] == ')':
                            count -= 1
                        if count == 0:
                            break
                        j += 1
                    tokens.append(expr[i:j+1])
                    i = j + 2
                else:
                    j = i
                    while j < len(expr) and expr[j] != ' ':
                        j += 1
                    tokens.append(expr[i:j])
                    i = j + 1
            return tokens
        
        return parse(expression, {})
