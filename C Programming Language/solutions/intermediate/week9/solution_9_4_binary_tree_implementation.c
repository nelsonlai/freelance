/**
 * Solution 9.4: Binary Tree Implementation
 * Week 9 - Advanced Data Structures
 * 
 * Description: Comprehensive binary tree implementation with AVL balancing,
 * traversal methods, and advanced tree operations.
 * 
 * Learning Objectives:
 * - Binary tree data structure implementation
 * - AVL tree balancing algorithms
 * - Tree traversal methods (inorder, preorder, postorder)
 * - Tree operations (insert, delete, search)
 * - Tree visualization and analysis
 * - Memory management for tree structures
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// BINARY TREE STRUCTURES
// ============================================================================

/**
 * Structure representing a node in the binary tree
 * Contains data and pointers to left and right children
 */
typedef struct TreeNode {
    int data;                   // Data stored in the node
    struct TreeNode *left;      // Pointer to left child
    struct TreeNode *right;     // Pointer to right child
    int height;                 // Height of the node (for AVL balancing)
    int balance_factor;         // Balance factor (left_height - right_height)
} TreeNode;

/**
 * Structure representing the entire binary tree
 * Contains root pointer and metadata
 */
typedef struct BinaryTree {
    TreeNode *root;             // Root of the tree
    int size;                   // Number of nodes in the tree
    int height;                 // Height of the tree
} BinaryTree;

/**
 * Structure for tree traversal results
 * Stores nodes in traversal order
 */
typedef struct TraversalResult {
    int *data;                  // Array of data values
    int count;                  // Number of nodes
    int capacity;               // Current capacity
} TraversalResult;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Tree creation and destruction
BinaryTree* create_binary_tree(void);
TreeNode* create_tree_node(int data);
void destroy_tree(BinaryTree *tree);
void destroy_tree_node(TreeNode *node);

// Basic tree operations
bool insert_node(BinaryTree *tree, int data);
bool delete_node(BinaryTree *tree, int data);
TreeNode* search_node(BinaryTree *tree, int data);
TreeNode* find_min_node(TreeNode *node);
TreeNode* find_max_node(TreeNode *node);

// AVL tree balancing
TreeNode* balance_node(TreeNode *node);
TreeNode* rotate_left(TreeNode *node);
TreeNode* rotate_right(TreeNode *node);
TreeNode* rotate_left_right(TreeNode *node);
TreeNode* rotate_right_left(TreeNode *node);
void update_height(TreeNode *node);
int get_height(TreeNode *node);
int get_balance_factor(TreeNode *node);

// Tree traversal methods
TraversalResult* inorder_traversal(BinaryTree *tree);
TraversalResult* preorder_traversal(BinaryTree *tree);
TraversalResult* postorder_traversal(BinaryTree *tree);
TraversalResult* level_order_traversal(BinaryTree *tree);
void inorder_recursive(TreeNode *node, TraversalResult *result);
void preorder_recursive(TreeNode *node, TraversalResult *result);
void postorder_recursive(TreeNode *node, TraversalResult *result);

// Tree analysis functions
int get_tree_size(BinaryTree *tree);
int get_tree_height(BinaryTree *tree);
bool is_empty(BinaryTree *tree);
bool is_balanced(BinaryTree *tree);
bool is_complete(BinaryTree *tree);
bool is_full(BinaryTree *tree);
bool is_perfect(BinaryTree *tree);

// Tree visualization
void print_tree_structure(BinaryTree *tree);
void print_tree_level(TreeNode *node, int level, int max_level);
void print_tree_horizontal(TreeNode *node, int depth, char *prefix, bool is_last);

// Utility functions
void free_traversal_result(TraversalResult *result);
void print_traversal_result(const TraversalResult *result, const char *type);
int max(int a, int b);
int min(int a, int b);

// ============================================================================
// TREE CREATION AND DESTRUCTION IMPLEMENTATION
// ============================================================================

/**
 * Create a new binary tree
 * 
 * Returns:
 * - Pointer to new BinaryTree on success
 * - NULL on failure
 */
BinaryTree* create_binary_tree(void) {
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    if (!tree) {
        printf("[ERROR] Memory allocation failed for binary tree\n");
        return NULL;
    }
    
    tree->root = NULL;
    tree->size = 0;
    tree->height = 0;
    
    printf("[CREATE_TREE] Created new binary tree\n");
    return tree;
}

/**
 * Create a new tree node
 * 
 * Parameters:
 * - data: Data to store in the node
 * 
 * Returns:
 * - Pointer to new TreeNode on success
 * - NULL on failure
 */
TreeNode* create_tree_node(int data) {
    TreeNode *node = malloc(sizeof(TreeNode));
    if (!node) {
        printf("[ERROR] Memory allocation failed for tree node\n");
        return NULL;
    }
    
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->balance_factor = 0;
    
    printf("[CREATE_NODE] Created node with data: %d\n", data);
    return node;
}

/**
 * Destroy entire tree and free all memory
 * 
 * Parameters:
 * - tree: Tree to destroy
 */
void destroy_tree(BinaryTree *tree) {
    if (!tree) {
        printf("[ERROR] Cannot destroy NULL tree\n");
        return;
    }
    
    destroy_tree_node(tree->root);
    free(tree);
    printf("[DESTROY_TREE] Destroyed entire tree\n");
}

/**
 * Recursively destroy tree nodes
 * 
 * Parameters:
 * - node: Root of subtree to destroy
 */
void destroy_tree_node(TreeNode *node) {
    if (!node) {
        return;
    }
    
    destroy_tree_node(node->left);
    destroy_tree_node(node->right);
    free(node);
}

// ============================================================================
// BASIC TREE OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Insert a new node into the tree
 * 
 * Parameters:
 * - tree: Tree to insert into
 * - data: Data to insert
 * 
 * Returns:
 * - true on success
 * - false on failure or duplicate
 */
bool insert_node(BinaryTree *tree, int data) {
    if (!tree) {
        printf("[ERROR] Cannot insert into NULL tree\n");
        return false;
    }
    
    // Check if data already exists
    if (search_node(tree, data)) {
        printf("[WARNING] Data %d already exists in tree\n", data);
        return false;
    }
    
    // Insert recursively
    tree->root = insert_node_recursive(tree->root, data);
    if (tree->root) {
        tree->size++;
        tree->height = get_height(tree->root);
        printf("[INSERT_NODE] Inserted %d into tree\n", data);
        return true;
    }
    
    return false;
}

/**
 * Recursive helper for node insertion
 * 
 * Parameters:
 * - node: Current node
 * - data: Data to insert
 * 
 * Returns:
 * - New root of subtree
 */
TreeNode* insert_node_recursive(TreeNode *node, int data) {
    // Base case: create new node
    if (!node) {
        return create_tree_node(data);
    }
    
    // Recursive insertion
    if (data < node->data) {
        node->left = insert_node_recursive(node->left, data);
    } else if (data > node->data) {
        node->right = insert_node_recursive(node->right, data);
    } else {
        // Duplicate data
        printf("[WARNING] Duplicate data %d not inserted\n", data);
        return node;
    }
    
    // Update height and balance
    update_height(node);
    
    // Balance the tree
    return balance_node(node);
}

/**
 * Delete a node from the tree
 * 
 * Parameters:
 * - tree: Tree to delete from
 * - data: Data to delete
 * 
 * Returns:
 * - true on success
 * - false if data not found
 */
bool delete_node(BinaryTree *tree, int data) {
    if (!tree || !tree->root) {
        printf("[ERROR] Cannot delete from empty tree\n");
        return false;
    }
    
    // Check if data exists
    if (!search_node(tree, data)) {
        printf("[WARNING] Data %d not found in tree\n", data);
        return false;
    }
    
    // Delete recursively
    tree->root = delete_node_recursive(tree->root, data);
    tree->size--;
    tree->height = tree->root ? get_height(tree->root) : 0;
    
    printf("[DELETE_NODE] Deleted %d from tree\n", data);
    return true;
}

/**
 * Recursive helper for node deletion
 * 
 * Parameters:
 * - node: Current node
 * - data: Data to delete
 * 
 * Returns:
 * - New root of subtree
 */
TreeNode* delete_node_recursive(TreeNode *node, int data) {
    if (!node) {
        return NULL;
    }
    
    if (data < node->data) {
        node->left = delete_node_recursive(node->left, data);
    } else if (data > node->data) {
        node->right = delete_node_recursive(node->right, data);
    } else {
        // Node to delete found
        if (!node->left) {
            TreeNode *temp = node->right;
            free(node);
            return temp;
        } else if (!node->right) {
            TreeNode *temp = node->left;
            free(node);
            return temp;
        } else {
            // Node has two children
            TreeNode *temp = find_min_node(node->right);
            node->data = temp->data;
            node->right = delete_node_recursive(node->right, temp->data);
        }
    }
    
    // Update height and balance
    update_height(node);
    return balance_node(node);
}

/**
 * Search for a node in the tree
 * 
 * Parameters:
 * - tree: Tree to search in
 * - data: Data to search for
 * 
 * Returns:
 * - Pointer to node if found
 * - NULL if not found
 */
TreeNode* search_node(BinaryTree *tree, int data) {
    if (!tree || !tree->root) {
        return NULL;
    }
    
    TreeNode *current = tree->root;
    while (current) {
        if (data == current->data) {
            printf("[SEARCH_NODE] Found %d in tree\n", data);
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    printf("[SEARCH_NODE] %d not found in tree\n", data);
    return NULL;
}

/**
 * Find minimum node in subtree
 * 
 * Parameters:
 * - node: Root of subtree
 * 
 * Returns:
 * - Pointer to minimum node
 */
TreeNode* find_min_node(TreeNode *node) {
    if (!node) {
        return NULL;
    }
    
    while (node->left) {
        node = node->left;
    }
    
    return node;
}

/**
 * Find maximum node in subtree
 * 
 * Parameters:
 * - node: Root of subtree
 * 
 * Returns:
 * - Pointer to maximum node
 */
TreeNode* find_max_node(TreeNode *node) {
    if (!node) {
        return NULL;
    }
    
    while (node->right) {
        node = node->right;
    }
    
    return node;
}

// ============================================================================
// AVL TREE BALANCING IMPLEMENTATION
// ============================================================================

/**
 * Update height of a node
 * 
 * Parameters:
 * - node: Node to update
 */
void update_height(TreeNode *node) {
    if (!node) {
        return;
    }
    
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    
    node->height = 1 + max(left_height, right_height);
    node->balance_factor = left_height - right_height;
}

/**
 * Get height of a node
 * 
 * Parameters:
 * - node: Node to get height of
 * 
 * Returns:
 * - Height of node (0 for NULL)
 */
int get_height(TreeNode *node) {
    return node ? node->height : 0;
}

/**
 * Get balance factor of a node
 * 
 * Parameters:
 * - node: Node to get balance factor of
 * 
 * Returns:
 * - Balance factor
 */
int get_balance_factor(TreeNode *node) {
    return node ? node->balance_factor : 0;
}

/**
 * Balance a node using AVL rotations
 * 
 * Parameters:
 * - node: Node to balance
 * 
 * Returns:
 * - Balanced node
 */
TreeNode* balance_node(TreeNode *node) {
    if (!node) {
        return NULL;
    }
    
    update_height(node);
    
    // Left heavy
    if (node->balance_factor > 1) {
        if (get_balance_factor(node->left) >= 0) {
            return rotate_right(node);
        } else {
            return rotate_left_right(node);
        }
    }
    
    // Right heavy
    if (node->balance_factor < -1) {
        if (get_balance_factor(node->right) <= 0) {
            return rotate_left(node);
        } else {
            return rotate_right_left(node);
        }
    }
    
    return node;
}

/**
 * Perform left rotation
 * 
 * Parameters:
 * - node: Node to rotate
 * 
 * Returns:
 * - New root after rotation
 */
TreeNode* rotate_left(TreeNode *node) {
    TreeNode *new_root = node->right;
    TreeNode *subtree = new_root->left;
    
    // Perform rotation
    new_root->left = node;
    node->right = subtree;
    
    // Update heights
    update_height(node);
    update_height(new_root);
    
    printf("[ROTATE_LEFT] Performed left rotation\n");
    return new_root;
}

/**
 * Perform right rotation
 * 
 * Parameters:
 * - node: Node to rotate
 * 
 * Returns:
 * - New root after rotation
 */
TreeNode* rotate_right(TreeNode *node) {
    TreeNode *new_root = node->left;
    TreeNode *subtree = new_root->right;
    
    // Perform rotation
    new_root->right = node;
    node->left = subtree;
    
    // Update heights
    update_height(node);
    update_height(new_root);
    
    printf("[ROTATE_RIGHT] Performed right rotation\n");
    return new_root;
}

/**
 * Perform left-right rotation
 * 
 * Parameters:
 * - node: Node to rotate
 * 
 * Returns:
 * - New root after rotation
 */
TreeNode* rotate_left_right(TreeNode *node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

/**
 * Perform right-left rotation
 * 
 * Parameters:
 * - node: Node to rotate
 * 
 * Returns:
 * - New root after rotation
 */
TreeNode* rotate_right_left(TreeNode *node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

// ============================================================================
// TREE TRAVERSAL IMPLEMENTATION
// ============================================================================

/**
 * Perform inorder traversal (left, root, right)
 * 
 * Parameters:
 * - tree: Tree to traverse
 * 
 * Returns:
 * - TraversalResult containing nodes in inorder
 */
TraversalResult* inorder_traversal(BinaryTree *tree) {
    if (!tree) {
        printf("[ERROR] Cannot traverse NULL tree\n");
        return NULL;
    }
    
    TraversalResult *result = malloc(sizeof(TraversalResult));
    if (!result) {
        printf("[ERROR] Memory allocation failed for traversal result\n");
        return NULL;
    }
    
    result->data = malloc(tree->size * sizeof(int));
    if (!result->data) {
        printf("[ERROR] Memory allocation failed for traversal data\n");
        free(result);
        return NULL;
    }
    
    result->count = 0;
    result->capacity = tree->size;
    
    inorder_recursive(tree->root, result);
    
    printf("[INORDER_TRAVERSAL] Traversed %d nodes\n", result->count);
    return result;
}

/**
 * Recursive helper for inorder traversal
 * 
 * Parameters:
 * - node: Current node
 * - result: Result structure to store data
 */
void inorder_recursive(TreeNode *node, TraversalResult *result) {
    if (!node) {
        return;
    }
    
    inorder_recursive(node->left, result);
    result->data[result->count++] = node->data;
    inorder_recursive(node->right, result);
}

/**
 * Perform preorder traversal (root, left, right)
 * 
 * Parameters:
 * - tree: Tree to traverse
 * 
 * Returns:
 * - TraversalResult containing nodes in preorder
 */
TraversalResult* preorder_traversal(BinaryTree *tree) {
    if (!tree) {
        printf("[ERROR] Cannot traverse NULL tree\n");
        return NULL;
    }
    
    TraversalResult *result = malloc(sizeof(TraversalResult));
    if (!result) {
        printf("[ERROR] Memory allocation failed for traversal result\n");
        return NULL;
    }
    
    result->data = malloc(tree->size * sizeof(int));
    if (!result->data) {
        printf("[ERROR] Memory allocation failed for traversal data\n");
        free(result);
        return NULL;
    }
    
    result->count = 0;
    result->capacity = tree->size;
    
    preorder_recursive(tree->root, result);
    
    printf("[PREORDER_TRAVERSAL] Traversed %d nodes\n", result->count);
    return result;
}

/**
 * Recursive helper for preorder traversal
 * 
 * Parameters:
 * - node: Current node
 * - result: Result structure to store data
 */
void preorder_recursive(TreeNode *node, TraversalResult *result) {
    if (!node) {
        return;
    }
    
    result->data[result->count++] = node->data;
    preorder_recursive(node->left, result);
    preorder_recursive(node->right, result);
}

/**
 * Perform postorder traversal (left, right, root)
 * 
 * Parameters:
 * - tree: Tree to traverse
 * 
 * Returns:
 * - TraversalResult containing nodes in postorder
 */
TraversalResult* postorder_traversal(BinaryTree *tree) {
    if (!tree) {
        printf("[ERROR] Cannot traverse NULL tree\n");
        return NULL;
    }
    
    TraversalResult *result = malloc(sizeof(TraversalResult));
    if (!result) {
        printf("[ERROR] Memory allocation failed for traversal result\n");
        return NULL;
    }
    
    result->data = malloc(tree->size * sizeof(int));
    if (!result->data) {
        printf("[ERROR] Memory allocation failed for traversal data\n");
        free(result);
        return NULL;
    }
    
    result->count = 0;
    result->capacity = tree->size;
    
    postorder_recursive(tree->root, result);
    
    printf("[POSTORDER_TRAVERSAL] Traversed %d nodes\n", result->count);
    return result;
}

/**
 * Recursive helper for postorder traversal
 * 
 * Parameters:
 * - node: Current node
 * - result: Result structure to store data
 */
void postorder_recursive(TreeNode *node, TraversalResult *result) {
    if (!node) {
        return;
    }
    
    postorder_recursive(node->left, result);
    postorder_recursive(node->right, result);
    result->data[result->count++] = node->data;
}

/**
 * Print traversal result
 * 
 * Parameters:
 * - result: Result to print
 * - type: Type of traversal
 */
void print_traversal_result(const TraversalResult *result, const char *type) {
    if (!result) {
        printf("[ERROR] Cannot print NULL traversal result\n");
        return;
    }
    
    printf("\n=== %s TRAVERSAL ===\n", type);
    printf("Number of nodes: %d\n", result->count);
    printf("Traversal order: ");
    
    for (int i = 0; i < result->count; i++) {
        printf("%d", result->data[i]);
        if (i < result->count - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

/**
 * Free traversal result memory
 * 
 * Parameters:
 * - result: Result to free
 */
void free_traversal_result(TraversalResult *result) {
    if (result) {
        free(result->data);
        free(result);
        printf("[FREE_TRAVERSAL_RESULT] Freed traversal result\n");
    }
}

// ============================================================================
// TREE ANALYSIS FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Get number of nodes in tree
 * 
 * Parameters:
 * - tree: Tree to analyze
 * 
 * Returns:
 * - Number of nodes
 */
int get_tree_size(BinaryTree *tree) {
    return tree ? tree->size : 0;
}

/**
 * Get height of tree
 * 
 * Parameters:
 * - tree: Tree to analyze
 * 
 * Returns:
 * - Height of tree
 */
int get_tree_height(BinaryTree *tree) {
    return tree ? tree->height : 0;
}

/**
 * Check if tree is empty
 * 
 * Parameters:
 * - tree: Tree to check
 * 
 * Returns:
 * - true if empty
 * - false otherwise
 */
bool is_empty(BinaryTree *tree) {
    return !tree || !tree->root;
}

/**
 * Check if tree is balanced
 * 
 * Parameters:
 * - tree: Tree to check
 * 
 * Returns:
 * - true if balanced
 * - false otherwise
 */
bool is_balanced(BinaryTree *tree) {
    if (!tree || !tree->root) {
        return true;
    }
    
    return abs(get_balance_factor(tree->root)) <= 1;
}

// ============================================================================
// TREE VISUALIZATION IMPLEMENTATION
// ============================================================================

/**
 * Print tree structure
 * 
 * Parameters:
 * - tree: Tree to print
 */
void print_tree_structure(BinaryTree *tree) {
    if (!tree || !tree->root) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("\n=== TREE STRUCTURE ===\n");
    printf("Tree size: %d nodes\n", tree->size);
    printf("Tree height: %d levels\n", tree->height);
    printf("Tree is balanced: %s\n", is_balanced(tree) ? "Yes" : "No");
    
    printf("\nTree visualization:\n");
    print_tree_horizontal(tree->root, 0, "", true);
}

/**
 * Print tree horizontally with proper indentation
 * 
 * Parameters:
 * - node: Current node
 * - depth: Current depth
 * - prefix: Prefix for this line
 * - is_last: Whether this is the last child
 */
void print_tree_horizontal(TreeNode *node, int depth, char *prefix, bool is_last) {
    if (!node) {
        return;
    }
    
    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%d (h:%d, bf:%d)\n", node->data, node->height, node->balance_factor);
    
    // Update prefix for children
    char *new_prefix = malloc(strlen(prefix) + 10);
    strcpy(new_prefix, prefix);
    strcat(new_prefix, is_last ? "    " : "│   ");
    
    // Print children
    bool has_left = node->left != NULL;
    bool has_right = node->right != NULL;
    
    if (has_left) {
        print_tree_horizontal(node->left, depth + 1, new_prefix, !has_right);
    }
    if (has_right) {
        print_tree_horizontal(node->right, depth + 1, new_prefix, true);
    }
    
    free(new_prefix);
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Get maximum of two integers
 * 
 * Parameters:
 * - a: First integer
 * - b: Second integer
 * 
 * Returns:
 * - Maximum value
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Get minimum of two integers
 * 
 * Parameters:
 * - a: First integer
 * - b: Second integer
 * 
 * Returns:
 * - Minimum value
 */
int min(int a, int b) {
    return (a < b) ? a : b;
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate basic tree operations
 */
void demonstrate_basic_operations(void) {
    printf("\n=== BASIC TREE OPERATIONS DEMONSTRATION ===\n");
    
    BinaryTree *tree = create_binary_tree();
    if (!tree) {
        printf("Failed to create tree\n");
        return;
    }
    
    // Insert nodes
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int num_values = sizeof(values) / sizeof(values[0]);
    
    printf("Inserting values: ");
    for (int i = 0; i < num_values; i++) {
        printf("%d ", values[i]);
        insert_node(tree, values[i]);
    }
    printf("\n");
    
    // Print tree structure
    print_tree_structure(tree);
    
    // Demonstrate searching
    printf("\n--- Searching Demonstration ---\n");
    TreeNode *found = search_node(tree, 40);
    if (found) {
        printf("Found node with data: %d\n", found->data);
    }
    
    TreeNode *min_node = find_min_node(tree->root);
    TreeNode *max_node = find_max_node(tree->root);
    if (min_node && max_node) {
        printf("Minimum value: %d\n", min_node->data);
        printf("Maximum value: %d\n", max_node->data);
    }
    
    // Demonstrate traversals
    printf("\n--- Traversal Demonstrations ---\n");
    
    TraversalResult *inorder = inorder_traversal(tree);
    TraversalResult *preorder = preorder_traversal(tree);
    TraversalResult *postorder = postorder_traversal(tree);
    
    if (inorder) {
        print_traversal_result(inorder, "INORDER");
        free_traversal_result(inorder);
    }
    
    if (preorder) {
        print_traversal_result(preorder, "PREORDER");
        free_traversal_result(preorder);
    }
    
    if (postorder) {
        print_traversal_result(postorder, "POSTORDER");
        free_traversal_result(postorder);
    }
    
    // Demonstrate deletion
    printf("\n--- Deletion Demonstration ---\n");
    printf("Deleting node 30...\n");
    delete_node(tree, 30);
    print_tree_structure(tree);
    
    // Clean up
    destroy_tree(tree);
}

/**
 * Demonstrate AVL balancing
 */
void demonstrate_avl_balancing(void) {
    printf("\n=== AVL BALANCING DEMONSTRATION ===\n");
    
    BinaryTree *tree = create_binary_tree();
    if (!tree) {
        printf("Failed to create tree\n");
        return;
    }
    
    // Insert values that will cause rotations
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int num_values = sizeof(values) / sizeof(values[0]);
    
    printf("Inserting values in ascending order (will trigger rotations):\n");
    for (int i = 0; i < num_values; i++) {
        printf("Inserting %d...\n", values[i]);
        insert_node(tree, values[i]);
        printf("Tree height after insertion: %d\n", get_tree_height(tree));
        printf("Tree is balanced: %s\n", is_balanced(tree) ? "Yes" : "No");
    }
    
    print_tree_structure(tree);
    
    // Demonstrate deletion causing rotations
    printf("\n--- Deletion Causing Rotations ---\n");
    printf("Deleting root node...\n");
    delete_node(tree, tree->root->data);
    print_tree_structure(tree);
    
    destroy_tree(tree);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("BINARY TREE IMPLEMENTATION DEMONSTRATION\n");
    printf("========================================\n");
    
    // Run demonstrations
    demonstrate_basic_operations();
    demonstrate_avl_balancing();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Binary tree data structure implementation\n");
    printf("2. AVL tree balancing algorithms\n");
    printf("3. Tree traversal methods (inorder, preorder, postorder)\n");
    printf("4. Tree operations (insert, delete, search)\n");
    printf("5. Tree analysis and validation\n");
    printf("6. Tree visualization and debugging\n");
    printf("7. Memory management for tree structures\n");
    printf("8. Advanced tree algorithms and optimizations\n");
    
    return 0;
}




