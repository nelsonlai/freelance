"""
Doubly Linked List (no dataclasses/typing/future)
=================================================

This module implements a classic doubly linked list with:
- sentinel head/tail nodes (dummy nodes that do not store user data),
- O(1) append/appendleft/pop/popleft,
- insert at index, remove (first/all), len(), iteration, reverse iteration,
- membership test (x in dll), indexing (dll[i]), assignment (dll[i]=v),
- slicing read (dll[i:j:k] -> Python list), to_list(), clear(), index(value).

Why sentinels?
--------------
Using two sentinel nodes (_head and _tail) means the list is *never* truly
empty internally: _head.next always points to something (either the first
real node or _tail), and _tail.prev likewise. That eliminates many boundary
checks (e.g., "if inserting at front and the list is empty...").

Complexity
----------
n = current number of elements
- append/appendleft/pop/popleft: O(1)
- insert/remove/find by value:   O(n)
- random access (dll[i]):        O(min(i, n-i))
- iteration:                     O(n)

Note about indexing/slicing:
----------------------------
Linked lists are poor for random access; __getitem__ walks from the nearest
end. Slicing returns a *regular Python list*, not a new linked list.
"""

# ------------------------------
# Node object for the list
# ------------------------------
class _Node(object):
    """
    Internal node for the doubly linked list.

    Attributes:
        value : the payload stored by this node (user data)
        prev  : reference to previous node (None only while detached)
        next  : reference to next node (None only while detached)

    We do NOT use @dataclass or type hints, to keep this dependency-free.
    """

    __slots__ = ("value", "prev", "next")  # reduce memory footprint (optional)

    def __init__(self, value=None):
        self.value = value
        self.prev = None
        self.next = None

    def detach(self):
        """Break links to neighbours (helps garbage collection)."""
        self.prev = None
        self.next = None


# -----------------------------------
# Doubly linked list implementation
# -----------------------------------
class DoublyLinkedList(object):
    """
    Public container class.

    The real elements live *between* the sentinels:
        _head <-> first <-> ... <-> last <-> _tail

    Invariants (must always hold when list is healthy):
        _head.prev is None
        _tail.next is None
        _head.next.prev is _head  (if list empty, _head.next is _tail)
        _tail.prev.next is _tail  (if list empty, _tail.prev is _head)
        _size is the count of real nodes between sentinels
    """

    # ------------- construction -------------

    def __init__(self, iterable=None):
        # Create two dummy/sentinel nodes with no user value
        self._head = _Node()
        self._tail = _Node()

        # Link them together (empty list invariant)
        self._head.next = self._tail
        self._tail.prev = self._head

        # Track number of real elements
        self._size = 0

        # Optionally populate from any iterable (list, tuple, generator, etc.)
        if iterable is not None:
            for item in iterable:
                self.append(item)

    # ------------- basic protocol -------------

    def __len__(self):
        """Return number of real elements."""
        return self._size

    def __bool__(self):
        """Truthiness: empty list is False; non-empty is True."""
        return self._size != 0

    # For Python 2 compatibility (optional): __nonzero__ = __bool__

    def __repr__(self):
        """Developer-friendly string representation."""
        return "DoublyLinkedList({})".format(self.to_list())

    # ------------- iteration -------------

    def __iter__(self):
        """
        Forward iteration from first element to last.
        Yields values only (not nodes).
        """
        cur = self._head.next
        while cur is not self._tail:
            yield cur.value
            cur = cur.next

    def __reversed__(self):
        """
        Reverse iteration from last element to first.
        """
        cur = self._tail.prev
        while cur is not self._head:
            yield cur.value
            cur = cur.prev

    # ------------- membership -------------

    def __contains__(self, value):
        """Return True if any node holds `value` (uses == for comparison)."""
        for v in self:
            if v == value:
                return True
        return False

    # ------------- random access (O(n)) -------------

    def __getitem__(self, index):
        """
        Support dll[i] and dll[i:j:k].

        - If index is an int: return the element at that position (0-based).
          Negative indexes are supported (like Python lists).
        - If index is a slice: return a *new Python list* of the selected items.
          (We don't return a new linked list; this keeps the API simple.)
        """
        if isinstance(index, slice):
            # Convert the whole list to a Python list, then apply slice semantics.
            # This is simple and correct, though not the most memory-efficient.
            data = self.to_list()
            return data[index]

        # Normalize negative index
        if index < 0:
            index += self._size

        if index < 0 or index >= self._size:
            raise IndexError("index out of range")

        node = self._node_at(index)
        return node.value

    def __setitem__(self, index, value):
        """
        Assign dll[i] = value (O(n)).
        Negative indexes are supported.
        """
        if index < 0:
            index += self._size
        if index < 0 or index >= self._size:
            raise IndexError("index out of range")

        node = self._node_at(index)
        node.value = value

    # ------------- public mutators -------------

    def append(self, value):
        """
        Insert at the end (just before _tail). O(1)

        Internally, this is equivalent to inserting between (_tail.prev, _tail).
        """
        self._insert_between(value, self._tail.prev, self._tail)

    def appendleft(self, value):
        """
        Insert at the front (just after _head). O(1)
        """
        self._insert_between(value, self._head, self._head.next)

    def pop(self):
        """
        Remove and return the last element. O(1)
        Raises IndexError if empty.
        """
        if self._size == 0:
            raise IndexError("pop from empty DoublyLinkedList")
        return self._unlink(self._tail.prev)

    def popleft(self):
        """
        Remove and return the first element. O(1)
        Raises IndexError if empty.
        """
        if self._size == 0:
            raise IndexError("popleft from empty DoublyLinkedList")
        return self._unlink(self._head.next)

    def clear(self):
        """
        Remove all elements. O(n)

        We walk through all real nodes to break their links to neighbours,
        helping the garbage collector reclaim memory promptly.
        """
        cur = self._head.next
        while cur is not self._tail:
            nxt = cur.next
            cur.detach()  # prev/next -> None
            cur = nxt

        # Reconnect sentinels to the empty state
        self._head.next = self._tail
        self._tail.prev = self._head
        self._size = 0

    def insert(self, index, value):
        """
        Insert `value` *before* the element currently at `index`.

        Behaviour matches list.insert:
          - if index <= 0: insert at front
          - if index >= len: insert at end
          - otherwise: insert so that new element lands at position `index`

        Complexity: O(min(index, n-index)) due to walking to that position.
        """
        if index <= 0 or self._size == 0:
            left = self._head
            right = self._head.next
        elif index >= self._size:
            left = self._tail.prev
            right = self._tail
        else:
            right = self._node_at(index)   # node currently at 'index'
            left = right.prev

        self._insert_between(value, left, right)

    def remove(self, value):
        """
        Remove the *first* occurrence of `value`. O(n)
        Raises ValueError if not present.
        """
        cur = self._head.next
        while cur is not self._tail:
            if cur.value == value:
                self._unlink(cur)
                return
            cur = cur.next
        raise ValueError("%r not in DoublyLinkedList" % (value,))

    def remove_all(self, value):
        """
        Remove *all* occurrences of `value`. Returns the number removed. O(n)
        """
        count = 0
        cur = self._head.next
        while cur is not self._tail:
            nxt = cur.next
            if cur.value == value:
                self._unlink(cur)
                count += 1
            cur = nxt
        return count

    # ------------- convenience -------------

    def index(self, value):
        """
        Return the index (0-based) of the first occurrence of `value`.
        Raises ValueError if not present.
        """
        i = 0
        cur = self._head.next
        while cur is not self._tail:
            if cur.value == value:
                return i
            i += 1
            cur = cur.next
        raise ValueError("%r not in DoublyLinkedList" % (value,))

    def to_list(self):
        """Materialize as a plain Python list (useful for testing/printing)."""
        out = []
        cur = self._head.next
        while cur is not self._tail:
            out.append(cur.value)
            cur = cur.next
        return out

    # ============================
    # Internal helper operations
    # ============================

    def _insert_between(self, value, left, right):
        """
        Insert a new node with `value` between existing adjacent nodes
        `left` and `right`.

        Precondition (must hold): left.next is right AND right.prev is left.
        These assertions help catch bugs during development.
        """
        # Defensive checks to ensure caller passed true neighbours
        assert left is not None and right is not None, "Neighbours cannot be None"
        assert left.next is right and right.prev is left, "Non-adjacent neighbours"

        node = _Node(value)
        node.prev = left
        node.next = right
        left.next = node
        right.prev = node
        self._size += 1

    def _unlink(self, node):
        """
        Physically remove `node` from the list and return its value.
        Precondition: `node` is a real element, not a sentinel.
        """
        # Sanity checks: never unlink sentinels
        assert node is not self._head and node is not self._tail, "Cannot unlink sentinel nodes"

        left = node.prev
        right = node.next
        # Neighbours must exist while the node is in the list
        assert left is not None and right is not None, "Broken links around node"

        # Stitch neighbours together, skipping over `node`
        left.next = right
        right.prev = left

        # Isolate the node to help GC and prevent accidental reuse
        val = node.value
        node.detach()

        self._size -= 1
        return val

    def _node_at(self, index):
        """
        Return the *node object* located at position `index` (0-based).

        We choose the closer end to walk from:
          - if index is in the first half, start at _head and go forward
          - else, start at _tail and go backward

        This halves the average traversal distance.
        """
        n = self._size
        # (Public callers validate the index. This function assumes 0 <= index < n.)
        if index <= n // 2:
            cur = self._head.next
            for _ in range(index):
                cur = cur.next
        else:
            cur = self._tail.prev
            for _ in range(n - 1 - index):
                cur = cur.prev

        # At this point, `cur` should be a real node (not a sentinel).
        assert cur is not self._head and cur is not self._tail, "Index traversal landed on a sentinel"
        return cur


# ----------------------------------------
# Example usage and quick sanity checks
# ----------------------------------------
if __name__ == "__main__":
    dll = DoublyLinkedList()

    # --- Basic append/appendleft ---
    dll.append(2)           # [2]
    dll.appendleft(1)       # [1, 2]
    dll.append(3)           # [1, 2, 3]
    dll.append(4)           # [1, 2, 3, 4]
    print("Start:", dll)    # DoublyLinkedList([1, 2, 3, 4])

    # --- Insert at position ---
    dll.insert(2, 99)       # before index 2 -> [1, 2, 99, 3, 4]
    print("After insert:", dll)

    # --- Indexing / assignment ---
    print("dll[2] =", dll[2])   # 99
    dll[2] = 42                 # [1, 2, 42, 3, 4]
    print("After setitem:", dll)

    # --- Iteration ---
    print("Forward:", list(dll))               # [1, 2, 42, 3, 4]
    print("Reverse:", list(reversed(dll)))     # [4, 3, 42, 2, 1]

    # --- Membership / index() ---
    print("42 in dll?", 42 in dll)             # True
    print("Index of 42:", dll.index(42))       # 2

    # --- Remove / remove_all ---
    dll.remove(42)                              # [1, 2, 3, 4]
    dll.append(3)                               # [1, 2, 3, 4, 3]
    removed = dll.remove_all(3)                 # remove all 3s -> [1, 2, 4]
    print("Removed 3s:", removed, dll)

    # --- Pop / popleft ---
    last = dll.pop()                            # pops 4 -> [1, 2]
    first = dll.popleft()                       # pops 1 -> [2]
    print("Pop results:", first, last, dll)

    # --- Slicing (returns a Python list) ---
    dll.append(10)                              # [2, 10]
    dll.append(20)                              # [2, 10, 20]
    dll.append(30)                              # [2, 10, 20, 30]
    print("Slice [1:4:2]:", dll[1:4:2])        # [10, 30]

    # --- Clear ---
    dll.clear()
    print("Cleared:", dll, "len=", len(dll))