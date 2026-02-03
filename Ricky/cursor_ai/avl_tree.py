"""
AVL Tree (Adelson-Velsky and Landis) - Self-balancing Binary Search Tree

An AVL tree maintains O(log n) height by ensuring that for every node,
the heights of its left and right subtrees differ by at most 1.
"""

from typing import Optional, List


class AVLNode:
    """Node for AVL tree. Stores key, left/right children, and height."""

    def __init__(self, key: int):
        self.key = key
        self.left: Optional[AVLNode] = None
        self.right: Optional[AVLNode] = None
        self.height = 1


class AVLTree:
    """
    AVL Tree: Binary Search Tree that stays balanced via rotations.
    - Insert: O(log n)
    - Search: O(log n)
    - Delete: O(log n)
    """

    def __init__(self):
        self.root: Optional[AVLNode] = None

    # ---------- Height & balance ----------

    def _height(self, node: Optional[AVLNode]) -> int:
        """Return height of node (0 for None)."""
        if node is None:
            return 0
        return node.height

    def _get_balance(self, node: Optional[AVLNode]) -> int:
        """
        Balance factor = height(left) - height(right).
        AVL requires |balance| <= 1 for every node.
        """
        if node is None:
            return 0
        return self._height(node.left) - self._height(node.right)

    def _update_height(self, node: AVLNode) -> None:
        """Recompute height from children."""
        node.height = 1 + max(
            self._height(node.left),
            self._height(node.right),
        )

    # ---------- Rotations (core of AVL algorithm) ----------

    def _rotate_right(self, z: AVLNode) -> AVLNode:
        """
        Right rotation (when left subtree is taller).
        Before:    z      After:   y
                  / \             / \
                 y   C     =>    A   z
                / \                 / \
               A   B               B   C
        """
        y = z.left
        if y is None:
            return z
        T2 = y.right

        y.right = z
        z.left = T2

        self._update_height(z)
        self._update_height(y)
        return y

    def _rotate_left(self, z: AVLNode) -> AVLNode:
        """
        Left rotation (when right subtree is taller).
        Before:  z        After:   y
                / \              / \
               A   y      =>    z   C
                  / \          / \
                 B   C        A   B
        """
        y = z.right
        if y is None:
            return z
        T2 = y.left

        y.left = z
        z.right = T2

        self._update_height(z)
        self._update_height(y)
        return y

    # ---------- Insert ----------

    def insert(self, key: int) -> None:
        """Insert key into AVL tree and rebalance."""
        self.root = self._insert(self.root, key)

    def _insert(self, node: Optional[AVLNode], key: int) -> AVLNode:
        """Recursive insert; returns new root of subtree after rebalance."""
        if node is None:
            return AVLNode(key)

        if key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        else:
            return node  # Duplicate keys not inserted

        self._update_height(node)
        balance = self._get_balance(node)

        # Left-Left: left subtree too tall, left child has left-heavy subtree
        if balance > 1 and key < (node.left.key if node.left else 0):
            return self._rotate_right(node)

        # Right-Right: right subtree too tall, right child has right-heavy subtree
        if balance < -1 and key > (node.right.key if node.right else 0):
            return self._rotate_left(node)

        # Left-Right: left subtree too tall, but key was inserted in left's right
        if balance > 1 and key > (node.left.key if node.left else 0):
            if node.left:
                node.left = self._rotate_left(node.left)
            return self._rotate_right(node)

        # Right-Left: right subtree too tall, but key was inserted in right's left
        if balance < -1 and key < (node.right.key if node.right else 0):
            if node.right:
                node.right = self._rotate_right(node.right)
            return self._rotate_left(node)

        return node

    # ---------- Delete ----------

    def delete(self, key: int) -> None:
        """Delete key from AVL tree and rebalance."""
        self.root = self._delete(self.root, key)

    def _min_value_node(self, node: AVLNode) -> AVLNode:
        """Return node with minimum key in this subtree (leftmost)."""
        current = node
        while current.left:
            current = current.left
        return current

    def _delete(self, node: Optional[AVLNode], key: int) -> Optional[AVLNode]:
        """Recursive delete; returns new root of subtree after rebalance."""
        if node is None:
            return None

        if key < node.key:
            node.left = self._delete(node.left, key)
        elif key > node.key:
            node.right = self._delete(node.right, key)
        else:
            if node.left is None:
                return node.right
            if node.right is None:
                return node.left
            # Two children: replace with inorder successor (min of right subtree)
            temp = self._min_value_node(node.right)
            node.key = temp.key
            node.right = self._delete(node.right, temp.key)

        if node is None:
            return None

        self._update_height(node)
        balance = self._get_balance(node)

        # Rebalance (same four cases as insert, mirrored)
        if balance > 1 and self._get_balance(node.left) >= 0:
            return self._rotate_right(node)
        if balance > 1 and self._get_balance(node.left) < 0:
            if node.left:
                node.left = self._rotate_left(node.left)
            return self._rotate_right(node)
        if balance < -1 and self._get_balance(node.right) <= 0:
            return self._rotate_left(node)
        if balance < -1 and self._get_balance(node.right) > 0:
            if node.right:
                node.right = self._rotate_right(node.right)
            return self._rotate_left(node)

        return node

    # ---------- Search ----------

    def search(self, key: int) -> bool:
        """Return True if key is in the tree."""
        return self._search(self.root, key)

    def _search(self, node: Optional[AVLNode], key: int) -> bool:
        if node is None:
            return False
        if key == node.key:
            return True
        if key < node.key:
            return self._search(node.left, key)
        return self._search(node.right, key)

    # ---------- Traversals (for display) ----------

    def inorder(self) -> List[int]:
        """Left -> Root -> Right (gives sorted order)."""
        result: List[int] = []

        def _inorder(n: Optional[AVLNode]) -> None:
            if n is None:
                return
            _inorder(n.left)
            result.append(n.key)
            _inorder(n.right)

        _inorder(self.root)
        return result

    def tree_display(self) -> str:
        """Simple text representation of tree (root at left, growing right)."""
        lines: List[str] = []

        def _display(node: Optional[AVLNode], prefix: str, is_tail: bool) -> None:
            if node is None:
                return
            connector = "└── " if is_tail else "├── "
            lines.append(prefix + connector + f"{node.key} (h={node.height}, b={self._get_balance(node)})")
            children_prefix = prefix + ("    " if is_tail else "│   ")
            if node.left or node.right:
                if node.left:
                    _display(node.left, children_prefix, node.right is None)
                if node.right:
                    _display(node.right, children_prefix, True)

        if self.root is None:
            return "(empty tree)"
        lines.append(f"{self.root.key} (h={self.root.height}, b={self._get_balance(self.root)})")
        if self.root.left:
            _display(self.root.left, "", self.root.right is None)
        if self.root.right:
            _display(self.root.right, "", True)
        return "\n".join(lines)


# ---------- Demo ----------

if __name__ == "__main__":
    tree = AVLTree()

    # Insert keys that would make a normal BST degenerate (e.g. sorted order)
    # AVL keeps it balanced
    keys = [10, 20, 30, 40, 50, 25]

    print("Inserting:", keys)
    for k in keys:
        tree.insert(k)

    print("\nTree structure (key, height, balance factor):")
    print(tree.tree_display())

    print("\nInorder (sorted):", tree.inorder())
    print("Search 25:", tree.search(25))
    print("Search 99:", tree.search(99))

    print("\n--- Delete 25 ---")
    tree.delete(25)
    print(tree.tree_display())
    print("Inorder after delete:", tree.inorder())
