from collections import defaultdict

class Solution:
    def countOfAtoms(self, formula: str) -> str:
        def parse():
            count = defaultdict(int)
            while self.i < len(formula):
                if formula[self.i] == '(':
                    self.i += 1
                    inner = parse()
                    self.i += 1
                    num = getNum()
                    for atom, cnt in inner.items():
                        count[atom] += cnt * num
                elif formula[self.i] == ')':
                    break
                else:
                    atom = getAtom()
                    num = getNum()
                    count[atom] += num
            return count
        
        def getAtom():
            start = self.i
            self.i += 1
            while self.i < len(formula) and formula[self.i].islower():
                self.i += 1
            return formula[start:self.i]
        
        def getNum():
            if self.i >= len(formula) or not formula[self.i].isdigit():
                return 1
            num = 0
            while self.i < len(formula) and formula[self.i].isdigit():
                num = num * 10 + int(formula[self.i])
                self.i += 1
            return num
        
        self.i = 0
        count = parse()
        result = []
        for atom in sorted(count.keys()):
            result.append(atom)
            if count[atom] > 1:
                result.append(str(count[atom]))
        return ''.join(result)
