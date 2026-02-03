"""Simple binary search tree implementation with helpful comments.

This module provides a minimal Binary Search Tree (BST) implementation
with common operations: insert, build from list, several traversals,
balancing (rebuild from sorted order), and a balance check.

Notes / assumptions:
- Duplicate values are inserted into the right subtree (consistent with
    the original implementation's `else` branch on comparison).
- The `balance` method reconstructs the tree from the inorder (sorted)
    list of values and therefore produces a height-balanced BST, but it
    does not attempt to preserve the original tree shape or node identities.

Complexities (rough):
- insert: O(h) where h is tree height (worst-case O(n) for degenerate tree)
- traversals: O(n)
- balance (store inorder + rebuild): O(n)
"""


class Node:
        """A node in a binary tree.

        Attributes:
                value: The value stored at this node. The tree assumes values are
                        comparable using < and >= for ordering.
                left: Reference to left child Node or None.
                right: Reference to right child Node or None.

        This is a lightweight container object; it does not perform any tree
        operations itself. Keeping Node simple makes it easy to reason about
        the BinaryTree methods which operate on nodes.
        """

        def __init__(self, value):
                # The payload stored in this node.
                self.value = value
                # Left and right children start as None (leaf node).
                self.left = None
                self.right = None


class BinaryTree:
    def __init__(self):
        self.root = None

    # -----------------------------
    # Insert into BST
    # -----------------------------
    def insert(self, value):
        """Insert a value into the tree following binary search tree rules.

        If the tree is empty this becomes the root. Otherwise this delegates
        to the recursive helper `_insert`.

        Behavior on duplicates: values that are not strictly less than the
        current node's value are placed into the right subtree. This is a
        common, simple tie-breaking rule that keeps the tree deterministic.
        """

        if not self.root:
            # Fast path for empty tree.
            self.root = Node(value)
        else:
            # Delegate to recursive insertion routine.
            self._insert(self.root, value)

    def _insert(self, current, value):
        """Recursive helper that inserts `value` under `current` node.

        This function walks the tree comparing `value` to `current.value` and
        continues left or right until it finds a vacant child pointer where a
        new Node can be attached.

        Important: this implementation is not tail-recursive and will use O(h)
        stack frames where h is the tree height. For very unbalanced trees
        this can approach O(n) recursion depth.
        """

        # If the value is strictly smaller, it belongs in the left subtree.
        if value < current.value:
            if current.left:
                # Recurse down left branch.
                self._insert(current.left, value)
            else:
                # Found insertion point: create a new leaf node.
                current.left = Node(value)
        else:
            # Otherwise place it in the right subtree (duplicates included).
            if current.right:
                self._insert(current.right, value)
            else:
                current.right = Node(value)

    # -----------------------------
    # Build from list
    # -----------------------------
    def build_from_list(self, values):
        """Convenience method: insert each value from an iterable into tree.

        Note: the order of values strongly affects the shape of the tree. For
        example inserting sorted data will create a degenerate (linked-list)
        shaped tree unless balanced later.
        """

        for v in values:
            # Each insert follows BST insertion rules defined above.
            self.insert(v)

    # -----------------------------
    # Traversals
    # preorder: Root → Left → Right
    # inorder: Left → Root → Right
    # postorder: Left → Right → Root
    # level_order: BFS (using a simple list as queue).
    # -----------------------------
    def preorder(self, node):
        """Depth-first preorder traversal (Root, Left, Right).

        This prints node values to stdout separated by spaces and uses
        recursion. For very deep trees the recursion depth may be a
        limiting factor; an iterative implementation using an explicit
        stack avoids that limit.
        """

        if node:
            # Visit root
            print(node.value, end=" ")
            # Recurse left subtree
            self.preorder(node.left)
            # Recurse right subtree
            self.preorder(node.right)

    def inorder(self, node):
        """Depth-first inorder traversal (Left, Root, Right).

        For a Binary Search Tree, an inorder traversal yields values in
        non-decreasing (sorted) order. This property is used by the
        `balance` method to collect a sorted list of values.
        """

        if node:
            self.inorder(node.left)
            print(node.value, end=" ")
            self.inorder(node.right)

    def postorder(self, node):
        """Depth-first postorder traversal (Left, Right, Root).

        Postorder is useful for operations where children must be processed
        before their parent (for example: deleting/freeing nodes from memory
        in languages without GC). Here it simply prints node values.
        """

        if node:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.value, end=" ")

    def level_order(self):
        """Breadth-first traversal (level order).

        Uses a Python list as a queue. For larger trees or performance
        sensitive code prefer collections.deque which has O(1) popleft.
        The current implementation uses list.pop(0) which is O(n) per pop
        and makes the traversal overall O(n^2) in the worst case; for small
        toy examples this tradeoff is often acceptable.
        """

        if not self.root:
            return

        # Simple FIFO queue holding nodes to process. Start with root.
        queue = [self.root]
        while queue:
            # pop(0) removes and returns the front of the list (head of queue)
            node = queue.pop(0)   # simple but not optimal for large queues
            print(node.value, end=" ")
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    # -----------------------------
    # Balance the tree
    # -----------------------------
    def _store_inorder(self, node, arr):
        """Collect node values into `arr` using inorder traversal.

        Because inorder on a BST yields sorted order, the resulting list
        `arr` will be sorted (non-decreasing) and can be used to reconstruct
        a balanced BST.
        """

        if node:
            self._store_inorder(node.left, arr)
            arr.append(node.value)
            self._store_inorder(node.right, arr)

    def _build_balanced(self, arr, start, end):
        """Build a balanced BST from sorted array slice arr[start:end+1].

        Algorithm: choose the middle element as root, recursively build left
        and right subtrees from the left and right subarrays. This produces a
        tree with minimal height (as balanced as possible) given the sorted
        input list.

        Complexity: O(n) time to build the nodes and O(log n) recursion depth
        for well-balanced arrays (but O(n) depth if arr is empty / recursion
        base case misused). This routine assumes `arr` is the list of values
        gathered by `_store_inorder`.
        """

        if start > end:
            return None

        # Choose middle to keep tree balanced. Integer division yields a
        # left-leaning middle for even-length ranges which is fine.
        mid = (start + end) // 2
        node = Node(arr[mid])
        # Recursively attach left and right subtrees built from subranges.
        node.left = self._build_balanced(arr, start, mid - 1)
        node.right = self._build_balanced(arr, mid + 1, end)
        return node

    def balance(self):
        """Rebuild the tree into a height-balanced BST.

        Steps:
        1. Collect all values using inorder traversal (sorted order).
        2. Build a balanced BST from the sorted list using `_build_balanced`.

        Side effects: the old node objects are discarded and new Node objects
        are created for the balanced tree. If external code kept references
        to Node instances from before the balance operation, those references
        will point to nodes that are no longer inside `self.root`.
        """

        arr = []
        self._store_inorder(self.root, arr)
        # Reconstruct root from the sorted values (this yields a balanced
        # tree with roughly minimal height).
        self.root = self._build_balanced(arr, 0, len(arr) - 1)

    # -----------------------------
    # Check if balanced
    # -----------------------------
    def is_balanced(self):
        def check(node):
            """Return (height, balanced) for subtree rooted at `node`.

            The height is the number of nodes on the longest path from the
            node down to a leaf. The subtree is considered balanced if both
            children are balanced and the heights differ by at most 1. This
            is the classic definition of an AVL-style balance check.
            """

            if not node:
                # Empty subtree has height 0 and is balanced by definition.
                return 0, True

            # Recursively check left and right subtrees.
            left_height, left_bal = check(node.left)
            right_height, right_bal = check(node.right)

            # Height of current node is max child height plus 1.
            height = max(left_height, right_height) + 1

            # Balanced iff both children balanced and height difference <= 1.
            balanced = (
                left_bal and right_bal and abs(left_height - right_height) <= 1
            )
            return height, balanced

        _, balanced = check(self.root)
        return balanced


# -----------------------------
# Example usage
# -----------------------------
if __name__ == "__main__":
    values = [32, 23, 12, 56, 78, 12, 34, 5, 3, 2, 9, 7, 10]
    tree = BinaryTree()
    tree.build_from_list(values)
    # Quick smoke-run when executed as script: show balance status and
    # demonstrate traversals. This is helpful for manual testing.
    print("Is balanced before:", tree.is_balanced())

    print("\nBalancing tree...")
    tree.balance()

    print("Is balanced after:", tree.is_balanced())

    print("\nTree traversals:")
    print("Preorder:", end=" ")
    tree.preorder(tree.root)
    print("\nInorder:", end=" ")
    tree.inorder(tree.root)
    print("\nPostorder:", end=" ")
    tree.postorder(tree.root)
    print("\nLevel order:", end=" ")
    tree.level_order()