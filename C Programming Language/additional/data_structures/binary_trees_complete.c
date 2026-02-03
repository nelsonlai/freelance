/**
 * Complete Binary Trees Implementation
 * Comprehensive demonstration of binary trees, BST, AVL trees, and tree traversals
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Basic Binary Tree Node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Binary Search Tree
struct BST {
    struct TreeNode *root;
    int size;
};

// AVL Tree Node (with height)
struct AVLNode {
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
};

// Expression Tree Node
struct ExprNode {
    char data;
    bool is_operator;
    struct ExprNode *left;
    struct ExprNode *right;
};

// Function prototypes for Binary Tree
struct TreeNode* create_node(int data);
struct TreeNode* insert_bst(struct TreeNode *root, int data);
struct TreeNode* delete_bst(struct TreeNode *root, int data);
struct TreeNode* search_bst(struct TreeNode *root, int data);
struct TreeNode* find_min(struct TreeNode *root);
struct TreeNode* find_max(struct TreeNode *root);

// Traversal functions
void inorder_traversal(struct TreeNode *root);
void preorder_traversal(struct TreeNode *root);
void postorder_traversal(struct TreeNode *root);
void level_order_traversal(struct TreeNode *root);
void print_tree_structure(struct TreeNode *root, int space);

// Tree analysis functions
int tree_height(struct TreeNode *root);
int tree_size(struct TreeNode *root);
int count_leaves(struct TreeNode *root);
bool is_balanced(struct TreeNode *root);
bool is_valid_bst(struct TreeNode *root, int min_val, int max_val);
struct TreeNode* lowest_common_ancestor(struct TreeNode *root, int n1, int n2);

// AVL Tree functions
struct AVLNode* create_avl_node(int data);
int avl_height(struct AVLNode *node);
int get_balance(struct AVLNode *node);
struct AVLNode* rotate_right(struct AVLNode *y);
struct AVLNode* rotate_left(struct AVLNode *x);
struct AVLNode* insert_avl(struct AVLNode *node, int data);
void inorder_avl(struct AVLNode *root);

// Expression Tree functions
struct ExprNode* create_expr_node(char data, bool is_op);
struct ExprNode* build_expression_tree(char postfix[]);
int evaluate_expression_tree(struct ExprNode *root);
void print_expression_tree(struct ExprNode *root);

void demonstrate_basic_binary_tree() {
    printf("=== Basic Binary Tree Operations ===\n");
    
    struct TreeNode *root = NULL;
    
    // Insert nodes to create BST
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert_bst(root, values[i]);
    }
    printf("\n");
    
    printf("\nTree structure:\n");
    print_tree_structure(root, 0);
    
    // Different traversals
    printf("\nTraversals:\n");
    printf("Inorder:   ");
    inorder_traversal(root);
    printf("\n");
    
    printf("Preorder:  ");
    preorder_traversal(root);
    printf("\n");
    
    printf("Postorder: ");
    postorder_traversal(root);
    printf("\n");
    
    printf("Level-order: ");
    level_order_traversal(root);
    printf("\n");
    
    // Tree analysis
    printf("\nTree Analysis:\n");
    printf("Height: %d\n", tree_height(root));
    printf("Size: %d\n", tree_size(root));
    printf("Leaves: %d\n", count_leaves(root));
    printf("Is balanced: %s\n", is_balanced(root) ? "Yes" : "No");
    printf("Is valid BST: %s\n", is_valid_bst(root, INT_MIN, INT_MAX) ? "Yes" : "No");
}

void demonstrate_bst_operations() {
    printf("\n=== Binary Search Tree Operations ===\n");
    
    struct TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);
    
    // Build BST
    for (int i = 0; i < n; i++) {
        root = insert_bst(root, values[i]);
    }
    
    printf("BST created with values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    
    // Search operations
    int search_values[] = {40, 90, 20, 100};
    printf("\nSearch operations:\n");
    for (int i = 0; i < 4; i++) {
        struct TreeNode *found = search_bst(root, search_values[i]);
        printf("Search %d: %s\n", search_values[i], found ? "Found" : "Not Found");
    }
    
    // Find min and max
    struct TreeNode *min_node = find_min(root);
    struct TreeNode *max_node = find_max(root);
    printf("\nMin value: %d\n", min_node ? min_node->data : -1);
    printf("Max value: %d\n", max_node ? max_node->data : -1);
    
    // Delete operations
    printf("\nDeleting nodes: 20, 30, 50\n");
    root = delete_bst(root, 20);
    root = delete_bst(root, 30);
    root = delete_bst(root, 50);
    
    printf("BST after deletions (inorder): ");
    inorder_traversal(root);
    printf("\n");
}

void demonstrate_avl_tree() {
    printf("\n=== AVL Tree (Self-Balancing) ===\n");
    
    struct AVLNode *avl_root = NULL;
    int values[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("Inserting values into AVL tree: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        avl_root = insert_avl(avl_root, values[i]);
    }
    printf("\n");
    
    printf("AVL tree (inorder): ");
    inorder_avl(avl_root);
    printf("\n");
    
    printf("AVL tree height: %d\n", avl_height(avl_root));
    printf("Balance factor of root: %d\n", get_balance(avl_root));
}

void demonstrate_expression_tree() {
    printf("\n=== Expression Tree ===\n");
    
    char postfix[] = "ab+cde+**";
    printf("Postfix expression: %s\n", postfix);
    
    struct ExprNode *expr_root = build_expression_tree(postfix);
    
    printf("Expression tree (inorder): ");
    print_expression_tree(expr_root);
    printf("\n");
    
    // For evaluation, we need actual numbers
    char numeric_postfix[] = "23+45+*";
    printf("\nNumeric postfix: %s\n", numeric_postfix);
    struct ExprNode *numeric_root = build_expression_tree(numeric_postfix);
    int result = evaluate_expression_tree(numeric_root);
    printf("Evaluation result: %d\n", result);
}

void demonstrate_tree_algorithms() {
    printf("\n=== Tree Algorithms ===\n");
    
    // Create a sample tree
    struct TreeNode *root = create_node(20);
    root->left = create_node(8);
    root->right = create_node(22);
    root->left->left = create_node(4);
    root->left->right = create_node(12);
    root->left->right->left = create_node(10);
    root->left->right->right = create_node(14);
    
    printf("Sample tree for algorithms:\n");
    print_tree_structure(root, 0);
    
    // Lowest Common Ancestor
    printf("\nLowest Common Ancestor:\n");
    printf("LCA(10, 14): %d\n", lowest_common_ancestor(root, 10, 14)->data);
    printf("LCA(4, 22): %d\n", lowest_common_ancestor(root, 4, 22)->data);
    
    // Path from root to node
    printf("\nPath from root to node 14: ");
    print_path_to_node(root, 14);
    printf("\n");
    
    // Check if tree is complete
    printf("Is complete binary tree: %s\n", is_complete_tree(root) ? "Yes" : "No");
    
    // Mirror tree
    printf("\nOriginal inorder: ");
    inorder_traversal(root);
    printf("\n");
    
    mirror_tree(root);
    printf("After mirroring: ");
    inorder_traversal(root);
    printf("\n");
}

void demonstrate_tree_construction() {
    printf("\n=== Tree Construction ===\n");
    
    // Construct tree from traversals
    int inorder[] = {4, 8, 10, 12, 14, 20, 22};
    int preorder[] = {20, 8, 4, 12, 10, 14, 22};
    int n = sizeof(inorder) / sizeof(inorder[0]);
    
    printf("Constructing tree from traversals:\n");
    printf("Inorder:  ");
    for (int i = 0; i < n; i++) printf("%d ", inorder[i]);
    printf("\n");
    printf("Preorder: ");
    for (int i = 0; i < n; i++) printf("%d ", preorder[i]);
    printf("\n");
    
    struct TreeNode *constructed = build_tree_from_traversals(inorder, preorder, 0, n - 1, &preorder_index);
    
    printf("Constructed tree (inorder): ");
    inorder_traversal(constructed);
    printf("\n");
    
    // Serialize and deserialize tree
    printf("\nTree serialization:\n");
    char *serialized = serialize_tree(constructed);
    printf("Serialized: %s\n", serialized);
    
    struct TreeNode *deserialized = deserialize_tree(serialized);
    printf("Deserialized tree (inorder): ");
    inorder_traversal(deserialized);
    printf("\n");
    
    free(serialized);
}

// Implementation of core functions

struct TreeNode* create_node(int data) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct TreeNode* insert_bst(struct TreeNode *root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert_bst(root->left, data);
    } else if (data > root->data) {
        root->right = insert_bst(root->right, data);
    }
    
    return root;
}

struct TreeNode* delete_bst(struct TreeNode *root, int data) {
    if (root == NULL) return root;
    
    if (data < root->data) {
        root->left = delete_bst(root->left, data);
    } else if (data > root->data) {
        root->right = delete_bst(root->right, data);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children
        struct TreeNode *temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_bst(root->right, temp->data);
    }
    
    return root;
}

struct TreeNode* search_bst(struct TreeNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search_bst(root->left, data);
    }
    
    return search_bst(root->right, data);
}

struct TreeNode* find_min(struct TreeNode *root) {
    if (root == NULL) return NULL;
    
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct TreeNode* find_max(struct TreeNode *root) {
    if (root == NULL) return NULL;
    
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Traversal implementations
void inorder_traversal(struct TreeNode *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(struct TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(struct TreeNode *root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

void level_order_traversal(struct TreeNode *root) {
    if (!root) return;
    
    // Use queue for level order traversal
    struct TreeNode *queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        struct TreeNode *current = queue[front++];
        printf("%d ", current->data);
        
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
}

void print_tree_structure(struct TreeNode *root, int space) {
    const int COUNT = 10;
    
    if (root == NULL) return;
    
    space += COUNT;
    
    print_tree_structure(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    print_tree_structure(root->left, space);
}

// Tree analysis implementations
int tree_height(struct TreeNode *root) {
    if (root == NULL) return -1;
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

int tree_size(struct TreeNode *root) {
    if (root == NULL) return 0;
    
    return 1 + tree_size(root->left) + tree_size(root->right);
}

int count_leaves(struct TreeNode *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    
    return count_leaves(root->left) + count_leaves(root->right);
}

bool is_balanced(struct TreeNode *root) {
    if (root == NULL) return true;
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return abs(left_height - right_height) <= 1 && 
           is_balanced(root->left) && 
           is_balanced(root->right);
}

bool is_valid_bst(struct TreeNode *root, int min_val, int max_val) {
    if (root == NULL) return true;
    
    if (root->data <= min_val || root->data >= max_val) {
        return false;
    }
    
    return is_valid_bst(root->left, min_val, root->data) &&
           is_valid_bst(root->right, root->data, max_val);
}

struct TreeNode* lowest_common_ancestor(struct TreeNode *root, int n1, int n2) {
    if (root == NULL) return NULL;
    
    if (root->data > n1 && root->data > n2) {
        return lowest_common_ancestor(root->left, n1, n2);
    }
    
    if (root->data < n1 && root->data < n2) {
        return lowest_common_ancestor(root->right, n1, n2);
    }
    
    return root;
}

// AVL Tree implementations
struct AVLNode* create_avl_node(int data) {
    struct AVLNode *node = malloc(sizeof(struct AVLNode));
    if (node) {
        node->data = data;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

int avl_height(struct AVLNode *node) {
    return node ? node->height : 0;
}

int get_balance(struct AVLNode *node) {
    return node ? avl_height(node->left) - avl_height(node->right) : 0;
}

struct AVLNode* rotate_right(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = 1 + (avl_height(y->left) > avl_height(y->right) ? 
                     avl_height(y->left) : avl_height(y->right));
    x->height = 1 + (avl_height(x->left) > avl_height(x->right) ? 
                     avl_height(x->left) : avl_height(x->right));
    
    return x;
}

struct AVLNode* rotate_left(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = 1 + (avl_height(x->left) > avl_height(x->right) ? 
                     avl_height(x->left) : avl_height(x->right));
    y->height = 1 + (avl_height(y->left) > avl_height(y->right) ? 
                     avl_height(y->left) : avl_height(y->right));
    
    return y;
}

struct AVLNode* insert_avl(struct AVLNode *node, int data) {
    // Standard BST insertion
    if (node == NULL) {
        return create_avl_node(data);
    }
    
    if (data < node->data) {
        node->left = insert_avl(node->left, data);
    } else if (data > node->data) {
        node->right = insert_avl(node->right, data);
    } else {
        return node;  // Duplicate keys not allowed
    }
    
    // Update height
    node->height = 1 + (avl_height(node->left) > avl_height(node->right) ? 
                        avl_height(node->left) : avl_height(node->right));
    
    // Get balance factor
    int balance = get_balance(node);
    
    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return rotate_right(node);
    }
    
    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return rotate_left(node);
    }
    
    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}

void inorder_avl(struct AVLNode *root) {
    if (root != NULL) {
        inorder_avl(root->left);
        printf("%d ", root->data);
        inorder_avl(root->right);
    }
}

// Expression Tree implementations
struct ExprNode* create_expr_node(char data, bool is_op) {
    struct ExprNode *node = malloc(sizeof(struct ExprNode));
    if (node) {
        node->data = data;
        node->is_operator = is_op;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct ExprNode* build_expression_tree(char postfix[]) {
    struct ExprNode *stack[100];
    int top = -1;
    
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            struct ExprNode *node = create_expr_node(ch, true);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        } else {
            struct ExprNode *node = create_expr_node(ch, false);
            stack[++top] = node;
        }
    }
    
    return stack[top];
}

int evaluate_expression_tree(struct ExprNode *root) {
    if (!root) return 0;
    
    if (!root->is_operator) {
        return root->data - '0';  // Convert char digit to int
    }
    
    int left_val = evaluate_expression_tree(root->left);
    int right_val = evaluate_expression_tree(root->right);
    
    switch (root->data) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return right_val ? left_val / right_val : 0;
        default: return 0;
    }
}

void print_expression_tree(struct ExprNode *root) {
    if (root != NULL) {
        if (root->is_operator) printf("(");
        print_expression_tree(root->left);
        printf("%c", root->data);
        print_expression_tree(root->right);
        if (root->is_operator) printf(")");
    }
}

// Additional helper functions
bool print_path_to_node(struct TreeNode *root, int target) {
    if (!root) return false;
    
    if (root->data == target) {
        printf("%d ", root->data);
        return true;
    }
    
    if (print_path_to_node(root->left, target) || 
        print_path_to_node(root->right, target)) {
        printf("%d ", root->data);
        return true;
    }
    
    return false;
}

bool is_complete_tree(struct TreeNode *root) {
    if (!root) return true;
    
    struct TreeNode *queue[1000];
    int front = 0, rear = 0;
    bool flag = false;
    
    queue[rear++] = root;
    
    while (front < rear) {
        struct TreeNode *current = queue[front++];
        
        if (current->left) {
            if (flag) return false;
            queue[rear++] = current->left;
        } else {
            flag = true;
        }
        
        if (current->right) {
            if (flag) return false;
            queue[rear++] = current->right;
        } else {
            flag = true;
        }
    }
    
    return true;
}

void mirror_tree(struct TreeNode *root) {
    if (!root) return;
    
    // Swap left and right subtrees
    struct TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively mirror subtrees
    mirror_tree(root->left);
    mirror_tree(root->right);
}

int main() {
    printf("COMPLETE BINARY TREES IMPLEMENTATION\n");
    printf("====================================\n\n");
    
    demonstrate_basic_binary_tree();
    demonstrate_bst_operations();
    demonstrate_avl_tree();
    demonstrate_expression_tree();
    demonstrate_tree_algorithms();
    demonstrate_tree_construction();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Binary tree basic operations and traversals\n");
    printf("- Binary Search Tree (BST) operations\n");
    printf("- AVL tree self-balancing with rotations\n");
    printf("- Expression trees for mathematical expressions\n");
    printf("- Tree algorithms (LCA, path finding, etc.)\n");
    printf("- Tree construction from traversals\n");
    printf("- Tree serialization and deserialization\n");
    printf("- Tree analysis (height, balance, completeness)\n");
    printf("- Memory management for tree structures\n");
    
    return 0;
}

