"""AVL tree implementation (self-balancing binary search tree) with
extensive inline documentation.

This module implements the core AVL operations: insertion and deletion
with automatic rebalancing using rotations. The implementation intentionally
keeps node objects lightweight (value, left, right, height). Height is the
number of nodes on the longest path from the node to a leaf; leaves have
height 1 in this implementation.

Behavioral notes / assumptions:
- Duplicate values are placed in the right subtree (consistent `else`
    insertion branch).
- All tree-modifying methods (insert/delete) return the (possibly new)
    subtree root so they are usable in recursive assignments like
    `root.left = insert(root.left, value)`.

Complexities (rough):
- insert/delete: O(log n) amortized for balanced AVL trees; worst-case
    single operation involves O(1) rotations and O(log n) height updates.
- traversal: O(n)
"""


class Node:
        """A node in an AVL tree.

        Attributes:
                value: Comparable payload stored at the node.
                left: Left child Node or None.
                right: Right child Node or None.
                height: Height of the subtree rooted at this node. A leaf has
                        height 1. Heights are updated by the tree methods after
                        structural changes.
        """

        def __init__(self, value):
                self.value = value
                self.left = None
                self.right = None
                # Height initialized to 1 for leaf node semantics.
                self.height = 1

class AVLTree:
    """
    An AVL tree implementation supporting insertion, deletion, and balancing.
    """
    def __init__(self):
        self.root = None

    def get_height(self, node):
        """Return height of `node`.

        Convention: None has height 0, leaf nodes have height 1. Using 0 for
        None simplifies height math (height of parent = 1 + max(child heights)).
        """

        if not node:
            return 0
        return node.height

    def get_balance(self, node):
        """Return balance factor of `node` defined as (height(left) - height(right)).

        Balance factor > 1 means left-heavy, < -1 means right-heavy. AVL trees
        maintain balance factors in {-1, 0, 1} for every node.
        """

        if not node:
            return 0
        return self.get_height(node.left) - self.get_height(node.right)
    
    def update_height(self, node):
        """Recompute and assign the height for `node`.

        Should be called after the node's children pointers have been
        modified (insertions/deletions/rotations). This keeps heights
        consistent for subsequent balance calculations.
        """

        if node:
            node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))

    def right_rotate(self, y):
        """Right rotation around node `y`.

        Rotation diagram (y is root of rotation):

             y                       x
            / \                     / \
           x   T3   -->           T1  y
          / \                         / \
         T1  T2                      T2 T3

        Steps:
        - Promote left child `x` to be new subtree root.
        - Make `y` the right child of `x` and `T2` the left child of `y`.
        - Update heights of affected nodes in bottom-up order.

        Returns the new root (`x`) of the rotated subtree.
        """

        x = y.left
        T2 = x.right

        # Perform rotation: link nodes appropriately.
        x.right = y
        y.left = T2

        # Update heights: update lower node first (y), then x.
        self.update_height(y)
        self.update_height(x)

        return x

    def left_rotate(self, x):
        """Left rotation around node `x`.

        Mirror operation of right_rotate. Diagram:

        x                            y
       / \                          / \
      T1  y        -->            x  T3
         / \                      / \
        T2 T3                   T1  T2

        Returns new subtree root (`y`).
        """

        y = x.right
        T2 = y.left

        # Perform rotation
        y.left = x
        x.right = T2

        # Update heights: update lower node first (x), then y.
        self.update_height(x)
        self.update_height(y)

        return y

    def insert(self, root, value):
        """Insert `value` into subtree rooted at `root` and rebalance as needed.

        Algorithm outline:
        1) Perform standard BST insert to place the new value as a leaf.
        2) Update height of `root` and compute its balance factor.
        3) If the node becomes unbalanced (balance factor not in {-1,0,1}),
           identify the case (LL, LR, RR, RL) and perform one or two
           rotations to restore AVL property.

        The method returns the new root of the subtree which allows callers
        to write: `root = avl.insert(root, value)` and keep the tree anchored.
        """

        # 1. Standard BST insertion (recursive): place value in left/right subtree
        if not root:
            return Node(value)
        elif value < root.value:
            root.left = self.insert(root.left, value)
        else:
            # duplicates go to the right subtree with this policy
            root.right = self.insert(root.right, value)

        # 2. Update height of this ancestor node
        self.update_height(root)

        # 3. Check balance factor to see if this node became unbalanced
        balance = self.get_balance(root)

        # 4. Handle imbalance cases using rotation(s)
        # Left-Left Case (heavy on left, new value in left-left subtree)
        if balance > 1 and value < root.left.value:
            return self.right_rotate(root)

        # Right-Right Case (heavy on right, new value in right-right subtree)
        if balance < -1 and value > root.right.value:
            return self.left_rotate(root)

        # Left-Right Case (heavy on left, new value in left-right subtree)
        if balance > 1 and value > root.left.value:
            # First do left rotation on left child, then right rotate root
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        # Right-Left Case (heavy on right, new value in right-left subtree)
        if balance < -1 and value < root.right.value:
            # First right rotate on right child, then left rotate root
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        # If already balanced, return unchanged root.
        return root

    def delete(self, root, value):
        """Delete `value` from subtree rooted at `root` and rebalance.

        Steps:
        1) Perform standard BST deletion to remove the node (three cases: leaf,
           single-child, two-children).
        2) Update height and balance factor on the path back up.
        3) Use rotations to restore AVL property where violated.

        Returns the new root of the subtree after deletion.
        """

        # 1. Standard BST deletion
        if not root:
            return root
        elif value < root.value:
            root.left = self.delete(root.left, value)
        elif value > root.value:
            root.right = self.delete(root.right, value)
        else:
            # Found node to delete
            # Case: node with only right child or no child
            if not root.left:
                temp = root.right
                root = None
                return temp
            # Case: node with only left child
            elif not root.right:
                temp = root.left
                root = None
                return temp

            # Case: node with two children. Find inorder successor (smallest in
            # right subtree), copy its value to current node, and delete successor.
            temp = self._get_min_value_node(root.right)
            root.value = temp.value
            root.right = self.delete(root.right, temp.value)

        # If the tree had only one node and it was deleted
        if not root:
            return root

        # 2. Update height of the current node after deletion
        self.update_height(root)

        # 3. Get the balance factor to check whether this node became unbalanced
        balance = self.get_balance(root)

        # 4. If unbalanced, there are 4 cases to handle (mirror of insertion cases)
        # Left-Left Case: left subtree heavier and left child is left-heavy or balanced
        if balance > 1 and self.get_balance(root.left) >= 0:
            return self.right_rotate(root)

        # Left-Right Case: left subtree heavier but left child is right-heavy
        if balance > 1 and self.get_balance(root.left) < 0:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        # Right-Right Case: right subtree heavier and right child is right-heavy or balanced
        if balance < -1 and self.get_balance(root.right) <= 0:
            return self.left_rotate(root)

        # Right-Left Case: right subtree heavier but right child is left-heavy
        if balance < -1 and self.get_balance(root.right) > 0:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    def _get_min_value_node(self, node):
        """Return node with minimum value in subtree (left-most node).

        Used by delete() to find inorder successor (smallest node in right
        subtree) when replacing a node with two children.
        """

        current = node
        while current.left is not None:
            current = current.left
        return current

    def preorder_traversal(self, root):
        """Return list of node values in preorder (Root, Left, Right).

        This helper is useful for small tests and visual verification of tree
        structure after inserts/deletes. It is recursive; for very deep trees
        consider an iterative version using an explicit stack.
        """

        if not root:
            return []

        result = [root.value]
        result += self.preorder_traversal(root.left)
        result += self.preorder_traversal(root.right)
        return result

# --- Example Usage ---
if __name__ == '__main__':
    avl_tree = AVLTree()
    root = None
    
    # Insert values into the tree. The tree will self-balance after each insertion.
    values_to_insert = [10, 20, 30, 40, 50, 25]
    for val in values_to_insert:
        root = avl_tree.insert(root, val)
    
    print("Preorder traversal after inserting values:")
    print(avl_tree.preorder_traversal(root)) 
    # The output shows the new, balanced structure of the tree.
    
    # Delete a value from the tree. The tree will rebalance after deletion.
    value_to_delete = 20
    root = avl_tree.delete(root, value_to_delete)
    
    print(f"\nPreorder traversal after deleting {value_to_delete}:")
    print(avl_tree.preorder_traversal(root))
    # The output confirms the node is gone and the tree remains balanced.