# ==============================================================================
# Red-Black Tree Implementation in Python
# ==============================================================================
# A Red-Black Tree is a self-balancing Binary Search Tree. Each node has a color
# (red or black) that is used to enforce balance properties. This implementation
# includes methods for insertion and balancing.
#
# Key Properties:
# 1. Every node is either red or black.
# 2. The root is always black.
# 3. Every leaf (NIL node) is black.
# 4. If a node is red, both its children must be black.
# 5. Every simple path from a node to any of its descendant leaves has the
#    same number of black nodes.
#
# The implementation uses a sentinel 'NIL' node to represent empty children
# and leaves, simplifying boundary checks.

class Node:
    """
    A node in a Red-Black Tree.
    
    Attributes:
        value: The value stored in the node.
        color: The color of the node, either 'RED' or 'BLACK'.
        parent: A reference to the parent node.
        left: A reference to the left child node.
        right: A reference to the right child node.
    """
    def __init__(self, value, color='RED', parent=None, left=None, right=None):
        self.value = value
        self.color = color
        self.parent = parent
        self.left = left
        self.right = right

# Define a sentinel NIL node for leaves and empty children.
# This makes the code cleaner by avoiding constant checks for 'None'.
NIL = Node(None, color='BLACK')
NIL.left = NIL
NIL.right = NIL

class RedBlackTree:
    """
    A class representing the Red-Black Tree data structure.
    
    Methods:
        insert(value): Inserts a new value into the tree.
        delete(value): Deletes a value from the tree.
        find_node(value): Finds a node with the given value.
        get_minimum(node): Gets the minimum value node in a subtree.
        transplant(u, v): Replaces subtree rooted at u with subtree rooted at v.
        fix_insert(node): Corrects any Red-Black Tree property violations after insertion.
        fix_delete(node): Corrects any Red-Black Tree property violations after deletion.
        left_rotate(node): Performs a left rotation to balance the tree.
        right_rotate(node): Performs a right rotation to balance the tree.
        __str__(): Provides a string representation of the tree for printing.
    """
    def __init__(self):
        # The root of the tree is initially the black NIL node.
        self.root = NIL

    def __str__(self):
        """
        Returns a formatted string representation of the tree.
        """
        return self._print_tree(self.root, "", True)

    def _print_tree(self, node, indent, last):
        """
        Helper method to recursively generate the tree's string representation.
        """
        if node is not NIL:
            result = self._print_tree(node.right, indent + (" " * 4 if last else "|   "), False)
            result += indent + ("└── " if last else "┌── ") + str(node.value) + f" ({node.color[0]})" + "\n"
            result += self._print_tree(node.left, indent + (" " * 4 if last else "|   "), True)
            return result
        return ""

    def insert(self, value):
        """
        Inserts a new value into the Red-Black Tree as if it were a standard
        Binary Search Tree, then calls a helper method to fix any violations.
        """
        # Create the new node, initially colored RED.
        new_node = Node(value, color='RED', left=NIL, right=NIL)
        
        parent = None
        current = self.root
        
        # Traverse the tree to find the correct position for the new node.
        while current is not NIL:
            parent = current
            if new_node.value < current.value:
                current = current.left
            else:
                current = current.right
        
        # Set the parent of the new node.
        new_node.parent = parent
        
        # Handle the case where the tree is empty.
        if parent is None:
            self.root = new_node
        # Place the new node as the left or right child of its parent.
        elif new_node.value < parent.value:
            parent.left = new_node
        else:
            parent.right = new_node
        
        # Now, fix any violations to restore the Red-Black Tree properties.
        self.fix_insert(new_node)
    
    def find_node(self, value):
        """
        Finds a node with the given value in the tree.
        Returns the node if found, otherwise returns NIL.
        """
        current = self.root
        while current is not NIL and current.value != value:
            if value < current.value:
                current = current.left
            else:
                current = current.right
        return current
    
    def get_minimum(self, node):
        """
        Gets the minimum value node in the subtree rooted at the given node.
        """
        while node.left is not NIL:
            node = node.left
        return node
    
    def transplant(self, u, v):
        """
        Replaces the subtree rooted at node u with the subtree rooted at node v.
        """
        if u.parent is None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent
    
    def delete(self, value):
        """
        Deletes a node with the given value from the Red-Black Tree.
        """
        z = self.find_node(value)
        if z is NIL:
            print(f"Value {value} not found in the tree.")
            return
        
        y = z
        y_original_color = y.color
        
        if z.left is NIL:
            x = z.right
            self.transplant(z, z.right)
        elif z.right is NIL:
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.get_minimum(z.right)
            y_original_color = y.color
            x = y.right
            if y.parent == z:
                x.parent = y
            else:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color
        
        if y_original_color == 'BLACK':
            self.fix_delete(x)
        
    def fix_delete(self, x):
        """
        Corrects Red-Black Tree properties after deletion by performing
        color changes and rotations.
        """
        while x != self.root and x.color == 'BLACK':
            if x == x.parent.left:
                w = x.parent.right  # Sibling of x
                if w.color == 'RED':
                    # Case 1: Sibling is red
                    w.color = 'BLACK'
                    x.parent.color = 'RED'
                    self.left_rotate(x.parent)
                    w = x.parent.right
                
                if w.left.color == 'BLACK' and w.right.color == 'BLACK':
                    # Case 2: Sibling is black and both its children are black
                    w.color = 'RED'
                    x = x.parent
                else:
                    if w.right.color == 'BLACK':
                        # Case 3: Sibling is black, left child is red, right child is black
                        w.left.color = 'BLACK'
                        w.color = 'RED'
                        self.right_rotate(w)
                        w = x.parent.right
                    # Case 4: Sibling is black, right child is red
                    w.color = x.parent.color
                    x.parent.color = 'BLACK'
                    w.right.color = 'BLACK'
                    self.left_rotate(x.parent)
                    x = self.root
            else:
                # Symmetric case where x is a right child
                w = x.parent.left  # Sibling of x
                if w.color == 'RED':
                    # Case 1: Sibling is red
                    w.color = 'BLACK'
                    x.parent.color = 'RED'
                    self.right_rotate(x.parent)
                    w = x.parent.left
                
                if w.right.color == 'BLACK' and w.left.color == 'BLACK':
                    # Case 2: Sibling is black and both its children are black
                    w.color = 'RED'
                    x = x.parent
                else:
                    if w.left.color == 'BLACK':
                        # Case 3: Sibling is black, right child is red, left child is black
                        w.right.color = 'BLACK'
                        w.color = 'RED'
                        self.left_rotate(w)
                        w = x.parent.left
                    # Case 4: Sibling is black, left child is red
                    w.color = x.parent.color
                    x.parent.color = 'BLACK'
                    w.left.color = 'BLACK'
                    self.right_rotate(x.parent)
                    x = self.root
        
        x.color = 'BLACK'
        
    def fix_insert(self, k):
        """
        Corrects Red-Black Tree properties after insertion by performing
        color changes and rotations.
        """
        # Ensure we don't dereference None when checking parent color.
        while k.parent is not None and k.parent.color == 'RED':
            if k.parent == k.parent.parent.right:
                # Case where parent is a right child
                u = k.parent.parent.left  # The uncle of the current node
                if u.color == 'RED':
                    # Case 1: Uncle is RED. Recolor and move up the tree.
                    u.color = 'BLACK'
                    k.parent.color = 'BLACK'
                    k.parent.parent.color = 'RED'
                    k = k.parent.parent
                else:
                    # Case 2: Uncle is BLACK. Perform rotations.
                    if k == k.parent.left:
                        # Case 2a: Left child of a right child.
                        # Perform a right rotation on the parent.
                        k = k.parent
                        self.right_rotate(k)
                    # Case 2b: Right child of a right child.
                    # Perform a left rotation on the grandparent.
                    k.parent.color = 'BLACK'
                    k.parent.parent.color = 'RED'
                    self.left_rotate(k.parent.parent)
            else:
                # Case where parent is a left child (symmetrical to the above).
                u = k.parent.parent.right  # The uncle
                if u.color == 'RED':
                    # Case 1: Uncle is RED. Recolor and move up.
                    u.color = 'BLACK'
                    k.parent.color = 'BLACK'
                    k.parent.parent.color = 'RED'
                    k = k.parent.parent
                else:
                    # Case 2: Uncle is BLACK. Perform rotations.
                    if k == k.parent.right:
                        # Case 2a: Right child of a left child.
                        k = k.parent
                        self.left_rotate(k)
                    # Case 2b: Left child of a left child.
                    k.parent.color = 'BLACK'
                    k.parent.parent.color = 'RED'
                    self.right_rotate(k.parent.parent)
            
            # If we reach the root, break the loop.
            if k == self.root:
                break
        
        # The root must always be black.
        self.root.color = 'BLACK'
        
    def left_rotate(self, x):
        """
        Performs a left rotation around node x.
        """
        y = x.right
        x.right = y.left
        if y.left is not NIL:
            y.left.parent = x
        
        y.parent = x.parent
        
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        
        y.left = x
        x.parent = y

    def right_rotate(self, x):
        """
        Performs a right rotation around node x.
        """
        y = x.left
        x.left = y.right
        if y.right is not NIL:
            y.right.parent = x
        
        y.parent = x.parent
        
        if x.parent is None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        
        y.right = x
        x.parent = y

# ==============================================================================
# Example Usage
# ==============================================================================

if __name__ == '__main__':
    rb_tree = RedBlackTree()
    
    # Values to insert into the tree.
    values_to_insert = [55, 40, 65, 60, 75, 57]
    
    print("Inserting values:", values_to_insert, "\n")
    
    # Insert each value and print the tree's state after all insertions.
    for val in values_to_insert:
        rb_tree.insert(val)
        print(f"Tree after inserting {val}:")
        print(rb_tree)
        print("-" * 20)
    
    print("Final Red-Black Tree structure after all insertions:")
    print(rb_tree)
    print("\n" + "="*50)
    
    # Demonstrate deletion
    values_to_delete = [60, 40, 55]
    
    print("\nDeleting values:", values_to_delete, "\n")
    
    for val in values_to_delete:
        print(f"Deleting {val}:")
        rb_tree.delete(val)
        print(rb_tree)
        print("-" * 20)
    
    print("Final Red-Black Tree structure after all deletions:")
    print(rb_tree)
    
    # Test deleting a non-existent value
    print("\nTesting deletion of non-existent value:")
    rb_tree.delete(99)