/**
 * DATA STRUCTURES - Lesson 3: Binary Tree
 * 
 * This lesson covers:
 * - Binary Tree implementation
 * - Tree traversal (Inorder, Preorder, Postorder, Level-order)
 * - Binary Search Tree (BST)
 * - Tree operations (insert, delete, search)
 */

import java.util.*;

// ========== BINARY TREE NODE ==========

class TreeNode {
    int data;
    TreeNode left;
    TreeNode right;
    
    public TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

// ========== BINARY TREE ==========

class BinaryTree {
    TreeNode root;
    
    public BinaryTree() {
        this.root = null;
    }
    
    // Insert a node (level order insertion)
    public void insert(int data) {
        TreeNode newNode = new TreeNode(data);
        if (root == null) {
            root = newNode;
            return;
        }
        
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            
            if (current.left == null) {
                current.left = newNode;
                return;
            } else {
                queue.offer(current.left);
            }
            
            if (current.right == null) {
                current.right = newNode;
                return;
            } else {
                queue.offer(current.right);
            }
        }
    }
    
    // Inorder traversal (Left, Root, Right)
    public void inorder(TreeNode node) {
        if (node != null) {
            inorder(node.left);
            System.out.print(node.data + " ");
            inorder(node.right);
        }
    }
    
    // Preorder traversal (Root, Left, Right)
    public void preorder(TreeNode node) {
        if (node != null) {
            System.out.print(node.data + " ");
            preorder(node.left);
            preorder(node.right);
        }
    }
    
    // Postorder traversal (Left, Right, Root)
    public void postorder(TreeNode node) {
        if (node != null) {
            postorder(node.left);
            postorder(node.right);
            System.out.print(node.data + " ");
        }
    }
    
    // Level-order traversal (BFS)
    public void levelOrder() {
        if (root == null) return;
        
        Queue<TreeNode> queue = new java.util.LinkedList<>();
        queue.offer(root);
        
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            System.out.print(current.data + " ");
            
            if (current.left != null) {
                queue.offer(current.left);
            }
            if (current.right != null) {
                queue.offer(current.right);
            }
        }
    }
    
    // Search for a value
    public boolean search(int data) {
        return searchHelper(root, data);
    }
    
    private boolean searchHelper(TreeNode node, int data) {
        if (node == null) return false;
        if (node.data == data) return true;
        return searchHelper(node.left, data) || searchHelper(node.right, data);
    }
    
    // Get height of tree
    public int height(TreeNode node) {
        if (node == null) return -1;
        return 1 + Math.max(height(node.left), height(node.right));
    }
    
    // Count nodes
    public int countNodes(TreeNode node) {
        if (node == null) return 0;
        return 1 + countNodes(node.left) + countNodes(node.right);
    }
}

// ========== BINARY SEARCH TREE ==========

class BinarySearchTree {
    TreeNode root;
    
    public BinarySearchTree() {
        this.root = null;
    }
    
    // Insert in BST
    public void insert(int data) {
        root = insertHelper(root, data);
    }
    
    private TreeNode insertHelper(TreeNode node, int data) {
        if (node == null) {
            return new TreeNode(data);
        }
        
        if (data < node.data) {
            node.left = insertHelper(node.left, data);
        } else if (data > node.data) {
            node.right = insertHelper(node.right, data);
        }
        
        return node;
    }
    
    // Search in BST
    public boolean search(int data) {
        return searchHelper(root, data);
    }
    
    private boolean searchHelper(TreeNode node, int data) {
        if (node == null) return false;
        if (node.data == data) return true;
        if (data < node.data) return searchHelper(node.left, data);
        return searchHelper(node.right, data);
    }
    
    // Delete from BST
    public void delete(int data) {
        root = deleteHelper(root, data);
    }
    
    private TreeNode deleteHelper(TreeNode node, int data) {
        if (node == null) return null;
        
        if (data < node.data) {
            node.left = deleteHelper(node.left, data);
        } else if (data > node.data) {
            node.right = deleteHelper(node.right, data);
        } else {
            // Node to delete found
            if (node.left == null) {
                return node.right;
            } else if (node.right == null) {
                return node.left;
            }
            
            // Node with two children: get inorder successor
            node.data = minValue(node.right);
            node.right = deleteHelper(node.right, node.data);
        }
        return node;
    }
    
    private int minValue(TreeNode node) {
        int min = node.data;
        while (node.left != null) {
            min = node.left.data;
            node = node.left;
        }
        return min;
    }
    
    // Inorder traversal (gives sorted order for BST)
    public void inorder() {
        inorderHelper(root);
        System.out.println();
    }
    
    private void inorderHelper(TreeNode node) {
        if (node != null) {
            inorderHelper(node.left);
            System.out.print(node.data + " ");
            inorderHelper(node.right);
        }
    }
    
    // Find minimum value
    public int findMin() {
        if (root == null) return -1;
        TreeNode current = root;
        while (current.left != null) {
            current = current.left;
        }
        return current.data;
    }
    
    // Find maximum value
    public int findMax() {
        if (root == null) return -1;
        TreeNode current = root;
        while (current.right != null) {
            current = current.right;
        }
        return current.data;
    }
}

// ========== MAIN CLASS ==========

public class BinaryTreeExample {
    public static void main(String[] args) {
        System.out.println("=== BINARY TREE ===");
        
        BinaryTree tree = new BinaryTree();
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);
        
        System.out.print("Inorder: ");
        tree.inorder(tree.root);
        System.out.println();
        
        System.out.print("Preorder: ");
        tree.preorder(tree.root);
        System.out.println();
        
        System.out.print("Postorder: ");
        tree.postorder(tree.root);
        System.out.println();
        
        System.out.print("Level-order: ");
        tree.levelOrder();
        System.out.println();
        
        System.out.println("Height: " + tree.height(tree.root));
        System.out.println("Node count: " + tree.countNodes(tree.root));
        System.out.println("Search 5: " + tree.search(5));
        System.out.println("Search 10: " + tree.search(10));
        
        System.out.println("\n=== BINARY SEARCH TREE ===");
        
        BinarySearchTree bst = new BinarySearchTree();
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);
        
        System.out.print("Inorder (sorted): ");
        bst.inorder();
        
        System.out.println("Min: " + bst.findMin());
        System.out.println("Max: " + bst.findMax());
        System.out.println("Search 40: " + bst.search(40));
        System.out.println("Search 100: " + bst.search(100));
        
        System.out.println("\nDeleting 30...");
        bst.delete(30);
        System.out.print("Inorder after deletion: ");
        bst.inorder();
    }
}

