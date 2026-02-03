from collections import Counter
import re

class Solution:
    def basicCalculatorIV(self, expression: str, evalvars: List[str], evalints: List[int]) -> List[str]:
        evalMap = dict(zip(evalvars, evalints))
        
        def evaluate(expr):
            expr = expr.replace(' ', '')
            i = 0
            n = len(expr)
            
            def parse():
                nonlocal i
                stack = [Counter()]
                sign = [1]
                
                while i < n:
                    if expr[i] == '(':
                        i += 1
                        stack.append(Counter())
                        sign.append(1)
                    elif expr[i] == ')':
                        i += 1
                        result = stack.pop() * sign.pop()
                        stack[-1] += result
                    elif expr[i] in '+-':
                        sign[-1] = 1 if expr[i] == '+' else -1
                        i += 1
                    else:
                        term = Counter()
                        if expr[i].isdigit():
                            num = 0
                            while i < n and expr[i].isdigit():
                                num = num * 10 + int(expr[i])
                                i += 1
                            term[''] = num
                        else:
                            var = ''
                            while i < n and expr[i].isalnum():
                                var += expr[i]
                                i += 1
                            if var in evalMap:
                                term[''] = evalMap[var]
                            else:
                                term[var] = 1
                        
                        if i < n and expr[i] == '*':
                            i += 1
                            if expr[i].isdigit():
                                num = 0
                                while i < n and expr[i].isdigit():
                                    num = num * 10 + int(expr[i])
                                    i += 1
                                for k in term:
                                    term[k] *= num
                            else:
                                var = ''
                                while i < n and expr[i].isalnum():
                                    var += expr[i]
                                    i += 1
                                if var in evalMap:
                                    num = evalMap[var]
                                    for k in term:
                                        term[k] *= num
                                else:
                                    newTerm = Counter()
                                    for k1 in term:
                                        for k2 in (var, ''):
                                            key = '*'.join(sorted(filter(None, [k1, k2]))) if k1 and k2 else (k1 or k2)
                                            newTerm[key] += term[k1]
                                    term = newTerm
                        
                        stack[-1] += term * sign[-1]
                
                return stack[0]
            
            return parse()
        
        poly = evaluate(expression)
        
        def formatTerm(term):
            if not term:
                return []
            items = sorted(term.items(), key=lambda x: (-len(x[0].split('*')), x[0]))
            result = []
            for key, coeff in items:
                if coeff == 0:
                    continue
                if key == '':
                    result.append(str(coeff))
                else:
                    result.append(f"{coeff}*{key}" if coeff != 1 else key)
            return result
        
        return formatTerm(poly)
