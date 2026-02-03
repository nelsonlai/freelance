# Give me an example of linked list in python

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def print_list(self):
        current = self.head
        while current:
            print(current.data)
            current = current.next

    def search(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    def delete(self, data):
        current = self.head
        previous = None
        while current:
            if current.data == data:
                if previous:
                    previous.next = current.next
                    current.next = None
                else:
                    self.head = current.next
                return True
            previous = current
            current = current.next
        return False

    def reverse(self):
        prev = None
        current = self.head
        while current:
            next = current.next
            current.next = prev
            prev = current
            current = next
        self.head = prev

    def sort(self):         # O(n^2) - Bubble Sort
        current = self.head
        while current:
            next = current.next
            while next:
                if current.data > next.data:
                    current.data, next.data = next.data, current.data
                next = next.next
            current = current.next

    def length(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    def __del__(self):
        current = self.head
        while current:
            next = current.next
            del current
            current = next
    
if __name__ == "__main__":
    linked_list = LinkedList()
    linked_list.insert(1)
    linked_list.insert(2)
    linked_list.insert(3)
    linked_list.insert(2)
    linked_list.insert(1)
    linked_list.insert(4)
    linked_list.print_list()
