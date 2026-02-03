import heapq

class ExamRoom:
    def __init__(self, n: int):
        self.n = n
        self.heap = []
        heapq.heappush(self.heap, (-self.dist(-1, n), -1, n))
        self.valid = {(-1, n): True}

    def seat(self) -> int:
        while self.heap and not self.valid.get((self.heap[0][1], self.heap[0][2]), False):
            heapq.heappop(self.heap)
        
        _, left, right = heapq.heappop(self.heap)
        del self.valid[(left, right)]
        
        if left == -1:
            seat = 0
        elif right == self.n:
            seat = self.n - 1
        else:
            seat = (left + right) // 2
        
        heapq.heappush(self.heap, (-self.dist(left, seat), left, seat))
        heapq.heappush(self.heap, (-self.dist(seat, right), seat, right))
        self.valid[(left, seat)] = True
        self.valid[(seat, right)] = True
        
        return seat

    def leave(self, p: int) -> None:
        left = right = None
        for (l, r) in list(self.valid.keys()):
            if r == p:
                left = l
            if l == p:
                right = r
        
        del self.valid[(left, p)]
        del self.valid[(p, right)]
        heapq.heappush(self.heap, (-self.dist(left, right), left, right))
        self.valid[(left, right)] = True

    def dist(self, left, right):
        if left == -1:
            return right
        if right == self.n:
            return self.n - 1 - left
        return (right - left) // 2
