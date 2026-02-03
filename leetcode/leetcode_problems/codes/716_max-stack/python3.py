class MaxStack:

    def __init__(self):
        self.stack = []
        self.maxStack = []

    def push(self, x: int) -> None:
        self.stack.append(x)
        if not self.maxStack or x >= self.maxStack[-1]:
            self.maxStack.append(x)

    def pop(self) -> int:
        val = self.stack.pop()
        if self.maxStack and val == self.maxStack[-1]:
            self.maxStack.pop()
        return val

    def top(self) -> int:
        return self.stack[-1]

    def peekMax(self) -> int:
        return self.maxStack[-1]

    def popMax(self) -> int:
        maxVal = self.maxStack[-1]
        temp = []
        while self.stack[-1] != maxVal:
            temp.append(self.pop())
        self.pop()
        while temp:
            self.push(temp.pop())
        return maxVal
