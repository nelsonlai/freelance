/**
 * Complete Huffman Coding Implementation
 * Comprehensive Huffman encoding and decoding with binary tree implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHARS 256
#define MAX_CODE_LENGTH 256

// Huffman Tree Node
struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
};

// Priority Queue for Huffman Tree construction
struct PriorityQueue {
    struct HuffmanNode **nodes;
    int size;
    int capacity;
};

// Huffman Code structure
struct HuffmanCode {
    char character;
    char code[MAX_CODE_LENGTH];
};

// Function prototypes
struct HuffmanNode* create_huffman_node(char character, int frequency);
struct PriorityQueue* create_priority_queue(int capacity);
void pq_insert(struct PriorityQueue *pq, struct HuffmanNode *node);
struct HuffmanNode* pq_extract_min(struct PriorityQueue *pq);
bool pq_is_empty(struct PriorityQueue *pq);
void pq_heapify_up(struct PriorityQueue *pq, int index);
void pq_heapify_down(struct PriorityQueue *pq, int index);

struct HuffmanNode* build_huffman_tree(char text[]);
void generate_codes(struct HuffmanNode *root, char code[], int depth, struct HuffmanCode codes[], int *code_count);
char* huffman_encode(char text[], struct HuffmanCode codes[], int code_count);
char* huffman_decode(char encoded[], struct HuffmanNode *root);
void print_huffman_tree(struct HuffmanNode *root, int space);
void print_codes(struct HuffmanCode codes[], int count);
int calculate_frequency(char text[], int freq[]);
void free_huffman_tree(struct HuffmanNode *root);

void demonstrate_frequency_analysis() {
    printf("=== Frequency Analysis ===\n");
    
    char text[] = "this is an example of a huffman tree";
    int freq[MAX_CHARS] = {0};
    
    printf("Input text: \"%s\"\n", text);
    
    int unique_chars = calculate_frequency(text, freq);
    
    printf("\nCharacter frequencies:\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
    
    printf("Total unique characters: %d\n", unique_chars);
    printf("Total characters: %zu\n", strlen(text));
}

void demonstrate_huffman_tree_construction() {
    printf("\n=== Huffman Tree Construction ===\n");
    
    char text[] = "abracadabra";
    printf("Text: \"%s\"\n", text);
    
    // Build Huffman tree
    struct HuffmanNode *root = build_huffman_tree(text);
    
    if (!root) {
        printf("Failed to build Huffman tree!\n");
        return;
    }
    
    printf("\nHuffman Tree Structure:\n");
    print_huffman_tree(root, 0);
    
    // Generate codes
    struct HuffmanCode codes[MAX_CHARS];
    int code_count = 0;
    char code[MAX_CODE_LENGTH];
    
    if (root->left == NULL && root->right == NULL) {
        // Special case: only one unique character
        codes[0].character = root->character;
        strcpy(codes[0].code, "0");
        code_count = 1;
    } else {
        generate_codes(root, code, 0, codes, &code_count);
    }
    
    printf("\nGenerated Huffman Codes:\n");
    print_codes(codes, code_count);
    
    free_huffman_tree(root);
}

void demonstrate_huffman_encoding() {
    printf("\n=== Huffman Encoding ===\n");
    
    char text[] = "hello world";
    printf("Original text: \"%s\"\n", text);
    printf("Original size: %zu characters = %zu bits (8 bits per char)\n", 
           strlen(text), strlen(text) * 8);
    
    // Build Huffman tree
    struct HuffmanNode *root = build_huffman_tree(text);
    if (!root) return;
    
    // Generate codes
    struct HuffmanCode codes[MAX_CHARS];
    int code_count = 0;
    char code[MAX_CODE_LENGTH];
    
    if (root->left == NULL && root->right == NULL) {
        codes[0].character = root->character;
        strcpy(codes[0].code, "0");
        code_count = 1;
    } else {
        generate_codes(root, code, 0, codes, &code_count);
    }
    
    printf("\nHuffman Codes:\n");
    print_codes(codes, code_count);
    
    // Encode the text
    char *encoded = huffman_encode(text, codes, code_count);
    if (encoded) {
        printf("\nEncoded text: %s\n", encoded);
        printf("Encoded size: %zu bits\n", strlen(encoded));
        printf("Compression ratio: %.2f%%\n", 
               (1.0 - (double)strlen(encoded) / (strlen(text) * 8)) * 100);
        
        // Decode the text
        char *decoded = huffman_decode(encoded, root);
        if (decoded) {
            printf("Decoded text: \"%s\"\n", decoded);
            printf("Decoding successful: %s\n", 
                   strcmp(text, decoded) == 0 ? "Yes" : "No");
            free(decoded);
        }
        
        free(encoded);
    }
    
    free_huffman_tree(root);
}

void demonstrate_compression_analysis() {
    printf("\n=== Compression Analysis ===\n");
    
    char *test_texts[] = {
        "aaaaaaaaaa",
        "abcdefghij",
        "aabbbccccdddddeeeeeeffffff",
        "the quick brown fox jumps over the lazy dog",
        "mississippi"
    };
    
    int num_texts = sizeof(test_texts) / sizeof(test_texts[0]);
    
    printf("Compression analysis for different text patterns:\n");
    printf("Text\t\t\t\tOriginal\tCompressed\tRatio\n");
    printf("----\t\t\t\t--------\t----------\t-----\n");
    
    for (int i = 0; i < num_texts; i++) {
        char *text = test_texts[i];
        int original_bits = strlen(text) * 8;
        
        struct HuffmanNode *root = build_huffman_tree(text);
        if (!root) continue;
        
        struct HuffmanCode codes[MAX_CHARS];
        int code_count = 0;
        char code[MAX_CODE_LENGTH];
        
        if (root->left == NULL && root->right == NULL) {
            codes[0].character = root->character;
            strcpy(codes[0].code, "0");
            code_count = 1;
        } else {
            generate_codes(root, code, 0, codes, &code_count);
        }
        
        char *encoded = huffman_encode(text, codes, code_count);
        if (encoded) {
            int compressed_bits = strlen(encoded);
            double ratio = (1.0 - (double)compressed_bits / original_bits) * 100;
            
            printf("%-30s\t%d\t\t%d\t\t%.1f%%\n", 
                   text, original_bits, compressed_bits, ratio);
            
            free(encoded);
        }
        
        free_huffman_tree(root);
    }
}

void demonstrate_file_compression() {
    printf("\n=== File Compression Simulation ===\n");
    
    // Simulate reading from a file
    char file_content[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                         "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
                         "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris.";
    
    printf("File content length: %zu characters\n", strlen(file_content));
    
    // Build Huffman tree
    struct HuffmanNode *root = build_huffman_tree(file_content);
    if (!root) return;
    
    // Generate codes
    struct HuffmanCode codes[MAX_CHARS];
    int code_count = 0;
    char code[MAX_CODE_LENGTH];
    generate_codes(root, code, 0, codes, &code_count);
    
    // Encode
    char *encoded = huffman_encode(file_content, codes, code_count);
    if (!encoded) return;
    
    printf("Original size: %zu bytes (%zu bits)\n", 
           strlen(file_content), strlen(file_content) * 8);
    printf("Compressed size: %zu bits\n", strlen(encoded));
    printf("Compression ratio: %.2f%%\n", 
           (1.0 - (double)strlen(encoded) / (strlen(file_content) * 8)) * 100);
    
    // Calculate theoretical minimum (entropy)
    int freq[MAX_CHARS] = {0};
    calculate_frequency(file_content, freq);
    
    double entropy = 0.0;
    int total_chars = strlen(file_content);
    
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            double probability = (double)freq[i] / total_chars;
            entropy -= probability * log2(probability);
        }
    }
    
    double theoretical_min = entropy * total_chars;
    printf("Theoretical minimum (entropy): %.2f bits\n", theoretical_min);
    printf("Huffman efficiency: %.2f%% of theoretical minimum\n", 
           (theoretical_min / strlen(encoded)) * 100);
    
    free(encoded);
    free_huffman_tree(root);
}

// Core Implementation Functions

struct HuffmanNode* create_huffman_node(char character, int frequency) {
    struct HuffmanNode *node = malloc(sizeof(struct HuffmanNode));
    if (node) {
        node->character = character;
        node->frequency = frequency;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct PriorityQueue* create_priority_queue(int capacity) {
    struct PriorityQueue *pq = malloc(sizeof(struct PriorityQueue));
    if (pq) {
        pq->nodes = malloc(capacity * sizeof(struct HuffmanNode*));
        pq->size = 0;
        pq->capacity = capacity;
    }
    return pq;
}

void pq_insert(struct PriorityQueue *pq, struct HuffmanNode *node) {
    if (!pq || pq->size >= pq->capacity) return;
    
    pq->nodes[pq->size] = node;
    pq->size++;
    pq_heapify_up(pq, pq->size - 1);
}

struct HuffmanNode* pq_extract_min(struct PriorityQueue *pq) {
    if (!pq || pq->size == 0) return NULL;
    
    struct HuffmanNode *min_node = pq->nodes[0];
    pq->nodes[0] = pq->nodes[pq->size - 1];
    pq->size--;
    pq_heapify_down(pq, 0);
    
    return min_node;
}

bool pq_is_empty(struct PriorityQueue *pq) {
    return !pq || pq->size == 0;
}

void pq_heapify_up(struct PriorityQueue *pq, int index) {
    if (index == 0) return;
    
    int parent = (index - 1) / 2;
    if (pq->nodes[index]->frequency < pq->nodes[parent]->frequency) {
        struct HuffmanNode *temp = pq->nodes[index];
        pq->nodes[index] = pq->nodes[parent];
        pq->nodes[parent] = temp;
        pq_heapify_up(pq, parent);
    }
}

void pq_heapify_down(struct PriorityQueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < pq->size && 
        pq->nodes[left]->frequency < pq->nodes[smallest]->frequency) {
        smallest = left;
    }
    
    if (right < pq->size && 
        pq->nodes[right]->frequency < pq->nodes[smallest]->frequency) {
        smallest = right;
    }
    
    if (smallest != index) {
        struct HuffmanNode *temp = pq->nodes[index];
        pq->nodes[index] = pq->nodes[smallest];
        pq->nodes[smallest] = temp;
        pq_heapify_down(pq, smallest);
    }
}

struct HuffmanNode* build_huffman_tree(char text[]) {
    int freq[MAX_CHARS] = {0};
    int unique_chars = calculate_frequency(text, freq);
    
    if (unique_chars == 0) return NULL;
    
    struct PriorityQueue *pq = create_priority_queue(unique_chars);
    
    // Create leaf nodes and add to priority queue
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            struct HuffmanNode *node = create_huffman_node(i, freq[i]);
            pq_insert(pq, node);
        }
    }
    
    // Build Huffman tree
    while (pq->size > 1) {
        struct HuffmanNode *left = pq_extract_min(pq);
        struct HuffmanNode *right = pq_extract_min(pq);
        
        struct HuffmanNode *merged = create_huffman_node('\0', 
                                                        left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        
        pq_insert(pq, merged);
    }
    
    struct HuffmanNode *root = pq_extract_min(pq);
    free(pq->nodes);
    free(pq);
    
    return root;
}

void generate_codes(struct HuffmanNode *root, char code[], int depth, 
                   struct HuffmanCode codes[], int *code_count) {
    if (!root) return;
    
    // Leaf node
    if (!root->left && !root->right) {
        code[depth] = '\0';
        codes[*code_count].character = root->character;
        strcpy(codes[*code_count].code, code);
        (*code_count)++;
        return;
    }
    
    // Traverse left
    if (root->left) {
        code[depth] = '0';
        generate_codes(root->left, code, depth + 1, codes, code_count);
    }
    
    // Traverse right
    if (root->right) {
        code[depth] = '1';
        generate_codes(root->right, code, depth + 1, codes, code_count);
    }
}

char* huffman_encode(char text[], struct HuffmanCode codes[], int code_count) {
    int text_len = strlen(text);
    char *encoded = malloc(text_len * MAX_CODE_LENGTH);
    if (!encoded) return NULL;
    
    encoded[0] = '\0';
    
    for (int i = 0; i < text_len; i++) {
        char ch = text[i];
        
        // Find code for character
        for (int j = 0; j < code_count; j++) {
            if (codes[j].character == ch) {
                strcat(encoded, codes[j].code);
                break;
            }
        }
    }
    
    return encoded;
}

char* huffman_decode(char encoded[], struct HuffmanNode *root) {
    if (!root || !encoded) return NULL;
    
    int encoded_len = strlen(encoded);
    char *decoded = malloc(encoded_len + 1);  // Worst case: all single bits
    if (!decoded) return NULL;
    
    int decoded_index = 0;
    struct HuffmanNode *current = root;
    
    // Special case: only one unique character
    if (!root->left && !root->right) {
        for (int i = 0; i < encoded_len; i++) {
            decoded[decoded_index++] = root->character;
        }
        decoded[decoded_index] = '\0';
        return decoded;
    }
    
    for (int i = 0; i < encoded_len; i++) {
        if (encoded[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        // Reached leaf node
        if (!current->left && !current->right) {
            decoded[decoded_index++] = current->character;
            current = root;  // Reset to root
        }
    }
    
    decoded[decoded_index] = '\0';
    return decoded;
}

void print_huffman_tree(struct HuffmanNode *root, int space) {
    const int COUNT = 10;
    
    if (!root) return;
    
    space += COUNT;
    
    print_huffman_tree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    
    if (root->character != '\0') {
        printf("'%c':%d\n", root->character, root->frequency);
    } else {
        printf("*:%d\n", root->frequency);
    }
    
    print_huffman_tree(root->left, space);
}

void print_codes(struct HuffmanCode codes[], int count) {
    for (int i = 0; i < count; i++) {
        printf("'%c': %s\n", codes[i].character, codes[i].code);
    }
}

int calculate_frequency(char text[], int freq[]) {
    int unique_chars = 0;
    
    for (int i = 0; text[i]; i++) {
        if (freq[(unsigned char)text[i]] == 0) {
            unique_chars++;
        }
        freq[(unsigned char)text[i]]++;
    }
    
    return unique_chars;
}

void free_huffman_tree(struct HuffmanNode *root) {
    if (!root) return;
    
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}

// Additional utility functions
void demonstrate_step_by_step_encoding() {
    printf("\n=== Step-by-Step Encoding Process ===\n");
    
    char text[] = "aab";
    printf("Text to encode: \"%s\"\n", text);
    
    // Step 1: Calculate frequencies
    int freq[MAX_CHARS] = {0};
    calculate_frequency(text, freq);
    
    printf("\nStep 1 - Character frequencies:\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
    
    // Step 2: Build tree
    printf("\nStep 2 - Building Huffman tree...\n");
    struct HuffmanNode *root = build_huffman_tree(text);
    
    // Step 3: Generate codes
    printf("\nStep 3 - Generating codes...\n");
    struct HuffmanCode codes[MAX_CHARS];
    int code_count = 0;
    char code[MAX_CODE_LENGTH];
    
    if (root->left == NULL && root->right == NULL) {
        codes[0].character = root->character;
        strcpy(codes[0].code, "0");
        code_count = 1;
    } else {
        generate_codes(root, code, 0, codes, &code_count);
    }
    
    print_codes(codes, code_count);
    
    // Step 4: Encode
    printf("\nStep 4 - Encoding process:\n");
    for (int i = 0; text[i]; i++) {
        char ch = text[i];
        for (int j = 0; j < code_count; j++) {
            if (codes[j].character == ch) {
                printf("'%c' -> %s\n", ch, codes[j].code);
                break;
            }
        }
    }
    
    char *encoded = huffman_encode(text, codes, code_count);
    printf("Final encoded string: %s\n", encoded);
    
    free(encoded);
    free_huffman_tree(root);
}

void demonstrate_decoding_process() {
    printf("\n=== Step-by-Step Decoding Process ===\n");
    
    char text[] = "programming";
    printf("Original text: \"%s\"\n", text);
    
    // Build tree and encode
    struct HuffmanNode *root = build_huffman_tree(text);
    struct HuffmanCode codes[MAX_CHARS];
    int code_count = 0;
    char code[MAX_CODE_LENGTH];
    generate_codes(root, code, 0, codes, &code_count);
    
    char *encoded = huffman_encode(text, codes, code_count);
    printf("Encoded: %s\n", encoded);
    
    // Step-by-step decoding
    printf("\nDecoding process:\n");
    struct HuffmanNode *current = root;
    int decoded_index = 0;
    
    for (int i = 0; encoded[i]; i++) {
        printf("Bit %c: ", encoded[i]);
        
        if (encoded[i] == '0') {
            current = current->left;
            printf("go left");
        } else {
            current = current->right;
            printf("go right");
        }
        
        if (!current->left && !current->right) {
            printf(" -> found '%c'\n", current->character);
            current = root;
        } else {
            printf("\n");
        }
    }
    
    free(encoded);
    free_huffman_tree(root);
}

int main() {
    printf("COMPLETE HUFFMAN CODING IMPLEMENTATION\n");
    printf("======================================\n\n");
    
    demonstrate_frequency_analysis();
    demonstrate_huffman_tree_construction();
    demonstrate_huffman_encoding();
    demonstrate_compression_analysis();
    demonstrate_step_by_step_encoding();
    demonstrate_decoding_process();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Character frequency analysis\n");
    printf("- Priority queue implementation for tree construction\n");
    printf("- Huffman tree building algorithm\n");
    printf("- Code generation from tree structure\n");
    printf("- Text encoding using generated codes\n");
    printf("- Text decoding using tree traversal\n");
    printf("- Compression ratio analysis\n");
    printf("- Entropy calculation and theoretical limits\n");
    printf("- Step-by-step encoding/decoding process\n");
    printf("- Memory management for tree structures\n");
    
    return 0;
}

