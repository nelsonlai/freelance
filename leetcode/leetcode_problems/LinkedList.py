'''
LinkedList problems and solutions
'''

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class LinkedList:
    def __init__(self, data=None):
        self.head = None
        if data and len(data) > 0:
            self.head = ListNode(data[0])
            current = self.head
            for i in range(1, len(data)):
                current.next = ListNode(data[i])
                current = current.next
        
    def append(self, val):
        new_node = ListNode(val)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node
        
    def insert(self, index, val):
        if index == 0:
            new_node = ListNode(val)
            new_node.next = self.head
            self.head = new_node
            return
        new_node = ListNode(val)
        current = self.head
        for _ in range(index - 1):
            if current is None:
                raise IndexError("Index out of range")
            current = current.next
        if current is None:
            raise IndexError("Index out of range")
        new_node.next = current.next
        current.next = new_node
        
    def delete(self, index):
        if self.head is None:
            raise IndexError("Index out of range")
        if index == 0:
            self.head = self.head.next
            return
        current = self.head
        for _ in range(index - 1):
            if current is None or current.next is None:
                raise IndexError("Index out of range")
            current = current.next
        if current.next is None:
            raise IndexError("Index out of range")
        current.next = current.next.next
        
    def print(self):
        current = self.head
        while current is not None:
            print(current.val, end=" ")
            current = current.next
        print()
        
    def reverse(self):
        prev = None
        current = self.head
        while current is not None:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.head = prev
        
    def find(self, val):
        current = self.head
        while current is not None:
            if current.val == val:
                return current
            current = current.next
        return None
    
    def length(self):
        current = self.head
        length = 0
        while current is not None:
            length += 1
            current = current.next
        return length
    
    def is_empty(self):
        return self.head is None
        
    def clear(self):
        self.head = None
        
    def get(self, index):
        current = self.head
        for _ in range(index):
            if current is None:
                raise IndexError("Index out of range")
            current = current.next
        if current is None:
            raise IndexError("Index out of range")
        return current.val
        
    def set(self, index, val):
        current = self.head
        for _ in range(index):
            if current is None:
                raise IndexError("Index out of range")
            current = current.next
        if current is None:
            raise IndexError("Index out of range")
        current.val = val

if __name__ == "__main__":
    linked_list = LinkedList([1, 2, 3, 4, 5])
    linked_list.print()
    print(linked_list.get(2))
    linked_list.set(2, 10)
    linked_list.print()
    print(linked_list.find(10))
    print(linked_list.length())
    print(linked_list.is_empty())
    linked_list.clear()
    linked_list.print()