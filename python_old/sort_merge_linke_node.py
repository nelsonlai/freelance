# Define Node class
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

# Define LinkedList class
class LinkedList:
    def __init__(self):
        self.head = None

    # Insert new node at the end
    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        cur = self.head
        while cur.next:
            cur = cur.next
        cur.next = new_node

    # Print the linked list
    def print_list(self):
        cur = self.head
        while cur:
            print(cur.data, end=" -> ")
            cur = cur.next
        print("None")

    # Merge Sort interface
    def merge_sort(self):
        self.head = self._merge_sort(self.head)

    # Recursive merge sort on linked list nodes
    def _merge_sort(self, head):
        if not head or not head.next:
            return head

        # Split the list into halves
        middle = self._get_middle(head)
        next_to_middle = middle.next
        middle.next = None

        # Recursively sort the halves
        left = self._merge_sort(head)
        right = self._merge_sort(next_to_middle)

        # Merge the sorted halves
        sorted_list = self._sorted_merge(left, right)
        return sorted_list

    # Merge two sorted linked lists
    def _sorted_merge(self, a, b):
        if not a:
            return b
        if not b:
            return a

        if a.data <= b.data:
            result = a
            result.next = self._sorted_merge(a.next, b)
        else:
            result = b
            result.next = self._sorted_merge(a, b.next)
        return result

    # Get middle of the linked list (slow/fast pointer)
    def _get_middle(self, head):
        if not head:
            return head

        slow = head
        fast = head

        while fast.next and fast.next.next:
            slow = slow.next
            fast = fast.next.next

        return slow

# Example usage
if __name__ == "__main__":
    ll = LinkedList()
    for value in [38, 27, 43, 3, 9, 82, 10]:
        ll.append(value)

    print("Original list:")
    ll.print_list()

    ll.merge_sort()

    print("\nSorted list:")
    ll.print_list()