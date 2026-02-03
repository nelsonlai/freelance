/**
 * Comprehensive strtok() Examples
 * Demonstrates various uses of the strtok function in C
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void basic_example() {
    printf("=== Basic strtok Example ===\n");
    
    char str[] = "apple,banana,cherry,date";
    char *token;
    
    printf("Original string: %s\n", str);
    printf("Tokens:\n");
    
    // First call with the string
    token = strtok(str, ",");
    while (token != NULL) {
        printf("  -> %s\n", token);
        // Subsequent calls with NULL
        token = strtok(NULL, ",");
    }
    
    printf("String after tokenization: ");
    for (int i = 0; i < 24; i++) {
        if (str[i] == '\0') {
            printf("\\0");
        } else {
            printf("%c", str[i]);
        }
    }
    printf("\n\n");
}

void multiple_delimiters() {
    printf("=== Multiple Delimiters Example ===\n");
    
    char str[] = "word1,word2;word3:word4 word5\tword6";
    char *token;
    
    printf("Original: %s\n", str);
    printf("Delimiters: comma, semicolon, colon, space, tab\n");
    printf("Tokens:\n");
    
    token = strtok(str, ",;: \t");
    while (token != NULL) {
        printf("  -> '%s'\n", token);
        token = strtok(NULL, ",;: \t");
    }
    printf("\n");
}

void csv_parser() {
    printf("=== CSV Parser Example ===\n");
    
    char csv[] = "John,25,Engineer,New York";
    char *fields[4];
    char *token;
    int field_count = 0;
    
    printf("CSV data: %s\n", csv);
    
    token = strtok(csv, ",");
    while (token != NULL && field_count < 4) {
        fields[field_count] = token;
        field_count++;
        token = strtok(NULL, ",");
    }
    
    printf("Parsed fields:\n");
    printf("  Name: %s\n", fields[0]);
    printf("  Age: %s\n", fields[1]);
    printf("  Job: %s\n", fields[2]);
    printf("  City: %s\n", fields[3]);
    printf("\n");
}

void path_tokenizer() {
    printf("=== File Path Tokenizer Example ===\n");
    
    char path[] = "/home/user/documents/file.txt";
    char *token;
    
    printf("File path: %s\n", path);
    printf("Path components:\n");
    
    token = strtok(path, "/");
    while (token != NULL) {
        printf("  -> %s\n", token);
        token = strtok(NULL, "/");
    }
    printf("\n");
}

void word_counter() {
    printf("=== Word Counter Example ===\n");
    
    char sentence[] = "The quick brown fox jumps over the lazy dog";
    char *token;
    int word_count = 0;
    
    printf("Sentence: %s\n", sentence);
    
    token = strtok(sentence, " ");
    while (token != NULL) {
        word_count++;
        printf("Word %d: %s\n", word_count, token);
        token = strtok(NULL, " ");
    }
    
    printf("Total words: %d\n\n", word_count);
}

void strtok_limitations() {
    printf("=== strtok Limitations & Important Notes ===\n");
    
    // Limitation 1: Modifies original string
    printf("1. MODIFIES ORIGINAL STRING:\n");
    char original[] = "a,b,c";
    char copy[10];
    strcpy(copy, original);
    
    printf("  Before: '%s'\n", copy);
    strtok(copy, ",");
    printf("  After strtok: string is modified internally\n");
    
    // Limitation 2: Not thread-safe
    printf("\n2. NOT THREAD-SAFE:\n");
    printf("  Uses internal static storage - problems in multi-threaded programs\n");
    
    // Limitation 3: Empty tokens are skipped
    printf("\n3. SKIPS EMPTY TOKENS:\n");
    char str_with_empty[] = "a,,b,c";
    char *token;
    printf("  String: '%s'\n", str_with_empty);
    printf("  Tokens found:\n");
    
    token = strtok(str_with_empty, ",");
    while (token != NULL) {
        printf("    '%s'\n", token);
        token = strtok(NULL, ",");
    }
    printf("  Note: Empty token between 'a' and 'b' is skipped!\n\n");
}

void safer_alternatives() {
    printf("=== Safer Alternatives to strtok ===\n");
    
    printf("1. strtok_r() - Reentrant version (POSIX):\n");
    printf("   char *strtok_r(char *str, const char *delim, char **saveptr);\n");
    
    printf("\n2. Manual parsing with strchr():\n");
    printf("   More control, doesn't modify original string\n");
    
    printf("\n3. Custom tokenizer functions:\n");
    printf("   Can handle empty tokens, preserve original string\n\n");
}

// Example of strtok_r (if available)
#ifdef _GNU_SOURCE
void strtok_r_example() {
    printf("=== strtok_r Example (Thread-Safe) ===\n");
    
    char str[] = "apple,banana,cherry";
    char *token;
    char *saveptr;  // Save pointer for strtok_r
    
    printf("Using strtok_r (thread-safe version):\n");
    
    token = strtok_r(str, ",", &saveptr);
    while (token != NULL) {
        printf("  -> %s\n", token);
        token = strtok_r(NULL, ",", &saveptr);
    }
    printf("\n");
}
#endif

int main() {
    printf("COMPREHENSIVE strtok() DEMONSTRATION\n");
    printf("====================================\n\n");
    
    basic_example();
    multiple_delimiters();
    csv_parser();
    path_tokenizer();
    word_counter();
    strtok_limitations();
    safer_alternatives();
    
#ifdef _GNU_SOURCE
    strtok_r_example();
#endif
    
    printf("Key Takeaways:\n");
    printf("- strtok modifies the original string\n");
    printf("- First call uses the string, subsequent calls use NULL\n");
    printf("- Not thread-safe due to internal static storage\n");
    printf("- Skips empty tokens\n");
    printf("- Consider strtok_r for thread-safe applications\n");
    
    return 0;
}
