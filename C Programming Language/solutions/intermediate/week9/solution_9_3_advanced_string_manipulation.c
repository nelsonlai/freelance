/**
 * Solution 9.3: Advanced String Manipulation
 * Week 9 - String Processing and Text Analysis
 * 
 * Description: Comprehensive string manipulation library with advanced
 * text processing, pattern matching, and string analysis capabilities.
 * 
 * Learning Objectives:
 * - Advanced string manipulation techniques
 * - Pattern matching and regular expressions
 * - Text analysis and statistics
 * - String parsing and tokenization
 * - Memory-efficient string operations
 * - Unicode and multibyte character handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// ============================================================================
// STRING UTILITY STRUCTURES AND CONSTANTS
// ============================================================================

/**
 * Structure to hold string statistics
 * Provides comprehensive analysis of text content
 */
typedef struct StringStats {
    size_t length;              // Total string length
    int word_count;             // Number of words
    int sentence_count;         // Number of sentences
    int paragraph_count;         // Number of paragraphs
    int char_count[256];        // Character frequency array
    int vowel_count;            // Number of vowels
    int consonant_count;        // Number of consonants
    int digit_count;            // Number of digits
    int space_count;            // Number of spaces
    int punctuation_count;      // Number of punctuation marks
    float average_word_length;  // Average word length
    float readability_score;    // Flesch readability score
} StringStats;

/**
 * Structure for pattern matching results
 * Stores information about pattern matches
 */
typedef struct MatchResult {
    int start_pos;              // Starting position of match
    int end_pos;                // Ending position of match
    char *matched_text;         // The matched text
    struct MatchResult *next;   // Pointer to next match
} MatchResult;

/**
 * Structure for string tokenization
 * Manages tokenized string data
 */
typedef struct TokenList {
    char **tokens;              // Array of token strings
    int count;                  // Number of tokens
    int capacity;              // Current capacity
} TokenList;

// Constants for string operations
#define MAX_STRING_LENGTH 10000
#define MAX_WORD_LENGTH 100
#define MAX_TOKENS 1000
#define GROWTH_FACTOR 2

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Basic string operations
char* string_copy(const char *src);
char* string_concat(const char *str1, const char *str2);
char* string_substring(const char *str, int start, int length);
int string_compare_case_insensitive(const char *str1, const char *str2);
bool string_starts_with(const char *str, const char *prefix);
bool string_ends_with(const char *str, const char *suffix);
char* string_reverse(char *str);
char* string_trim(char *str);

// Advanced string operations
char* string_replace(const char *str, const char *old, const char *new);
char* string_replace_all(const char *str, const char *old, const char *new);
char* string_insert(const char *str, int pos, const char *insert);
char* string_remove(const char *str, int start, int length);
char* string_pad_left(const char *str, int width, char pad_char);
char* string_pad_right(const char *str, int width, char pad_char);
char* string_pad_center(const char *str, int width, char pad_char);

// Case conversion functions
char* string_to_uppercase(const char *str);
char* string_to_lowercase(const char *str);
char* string_to_title_case(const char *str);
char* string_to_camel_case(const char *str);
char* string_to_snake_case(const char *str);

// Pattern matching functions
bool string_contains(const char *str, const char *substr);
int string_find_first(const char *str, const char *substr);
int string_find_last(const char *str, const char *substr);
MatchResult* string_find_all(const char *str, const char *pattern);
bool string_matches_pattern(const char *str, const char *pattern);
char* string_extract_pattern(const char *str, const char *pattern);

// Tokenization functions
TokenList* string_tokenize(const char *str, const char *delimiters);
TokenList* string_split_lines(const char *str);
TokenList* string_split_words(const char *str);
void free_token_list(TokenList *token_list);
void print_token_list(const TokenList *token_list);

// String analysis functions
StringStats* analyze_string(const char *str);
void print_string_stats(const StringStats *stats);
void free_string_stats(StringStats *stats);
bool is_palindrome(const char *str);
bool is_anagram(const char *str1, const char *str2);
int levenshtein_distance(const char *str1, const char *str2);

// Validation functions
bool is_valid_email(const char *email);
bool is_valid_phone(const char *phone);
bool is_valid_url(const char *url);
bool is_valid_ip_address(const char *ip);
bool is_numeric(const char *str);
bool is_alpha(const char *str);
bool is_alphanumeric(const char *str);

// Encoding and decoding functions
char* string_encode_base64(const char *str);
char* string_decode_base64(const char *str);
char* string_encode_url(const char *str);
char* string_decode_url(const char *str);
char* string_escape_html(const char *str);
char* string_unescape_html(const char *str);

// Memory management
void* safe_malloc(size_t size);
void safe_free(void *ptr);

// ============================================================================
// BASIC STRING OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Create a copy of a string
 * 
 * Parameters:
 * - src: Source string to copy
 * 
 * Returns:
 * - Pointer to new string on success
 * - NULL on failure
 */
char* string_copy(const char *src) {
    if (!src) {
        printf("[ERROR] Cannot copy NULL string\n");
        return NULL;
    }
    
    size_t len = strlen(src);
    char *copy = safe_malloc(len + 1);
    if (!copy) {
        printf("[ERROR] Memory allocation failed for string copy\n");
        return NULL;
    }
    
    strcpy(copy, src);
    printf("[STRING_COPY] Copied string: %s\n", src);
    return copy;
}

/**
 * Concatenate two strings
 * 
 * Parameters:
 * - str1: First string
 * - str2: Second string
 * 
 * Returns:
 * - Pointer to concatenated string on success
 * - NULL on failure
 */
char* string_concat(const char *str1, const char *str2) {
    if (!str1 || !str2) {
        printf("[ERROR] Cannot concatenate NULL strings\n");
        return NULL;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = safe_malloc(len1 + len2 + 1);
    
    if (!result) {
        printf("[ERROR] Memory allocation failed for string concatenation\n");
        return NULL;
    }
    
    strcpy(result, str1);
    strcat(result, str2);
    printf("[STRING_CONCAT] Concatenated: %s + %s = %s\n", str1, str2, result);
    return result;
}

/**
 * Extract a substring from a string
 * 
 * Parameters:
 * - str: Source string
 * - start: Starting position (0-based)
 * - length: Length of substring
 * 
 * Returns:
 * - Pointer to substring on success
 * - NULL on failure
 */
char* string_substring(const char *str, int start, int length) {
    if (!str || start < 0 || length < 0) {
        printf("[ERROR] Invalid parameters for substring\n");
        return NULL;
    }
    
    size_t str_len = strlen(str);
    if (start >= str_len) {
        printf("[ERROR] Start position %d exceeds string length %zu\n", start, str_len);
        return NULL;
    }
    
    // Adjust length if it exceeds string bounds
    if (start + length > str_len) {
        length = str_len - start;
    }
    
    char *substring = safe_malloc(length + 1);
    if (!substring) {
        printf("[ERROR] Memory allocation failed for substring\n");
        return NULL;
    }
    
    strncpy(substring, str + start, length);
    substring[length] = '\0';
    
    printf("[STRING_SUBSTRING] Extracted: '%s' from position %d, length %d\n", 
           substring, start, length);
    return substring;
}

/**
 * Compare two strings case-insensitively
 * 
 * Parameters:
 * - str1: First string
 * - str2: Second string
 * 
 * Returns:
 * - 0 if strings are equal
 * - Negative if str1 < str2
 * - Positive if str1 > str2
 */
int string_compare_case_insensitive(const char *str1, const char *str2) {
    if (!str1 || !str2) {
        printf("[ERROR] Cannot compare NULL strings\n");
        return 0;
    }
    
    int result = strcasecmp(str1, str2);
    printf("[STRING_COMPARE_CI] '%s' vs '%s': %d\n", str1, str2, result);
    return result;
}

/**
 * Check if string starts with a prefix
 * 
 * Parameters:
 * - str: String to check
 * - prefix: Prefix to look for
 * 
 * Returns:
 * - true if string starts with prefix
 * - false otherwise
 */
bool string_starts_with(const char *str, const char *prefix) {
    if (!str || !prefix) {
        printf("[ERROR] Cannot check prefix for NULL strings\n");
        return false;
    }
    
    size_t str_len = strlen(str);
    size_t prefix_len = strlen(prefix);
    
    if (prefix_len > str_len) {
        return false;
    }
    
    bool result = strncmp(str, prefix, prefix_len) == 0;
    printf("[STRING_STARTS_WITH] '%s' starts with '%s': %s\n", 
           str, prefix, result ? "true" : "false");
    return result;
}

/**
 * Check if string ends with a suffix
 * 
 * Parameters:
 * - str: String to check
 * - suffix: Suffix to look for
 * 
 * Returns:
 * - true if string ends with suffix
 * - false otherwise
 */
bool string_ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) {
        printf("[ERROR] Cannot check suffix for NULL strings\n");
        return false;
    }
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len) {
        return false;
    }
    
    bool result = strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
    printf("[STRING_ENDS_WITH] '%s' ends with '%s': %s\n", 
           str, suffix, result ? "true" : "false");
    return result;
}

/**
 * Reverse a string in place
 * 
 * Parameters:
 * - str: String to reverse
 * 
 * Returns:
 * - Pointer to reversed string
 */
char* string_reverse(char *str) {
    if (!str) {
        printf("[ERROR] Cannot reverse NULL string\n");
        return NULL;
    }
    
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    
    printf("[STRING_REVERSE] Reversed string: %s\n", str);
    return str;
}

/**
 * Trim whitespace from both ends of string
 * 
 * Parameters:
 * - str: String to trim
 * 
 * Returns:
 * - Pointer to trimmed string
 */
char* string_trim(char *str) {
    if (!str) {
        printf("[ERROR] Cannot trim NULL string\n");
        return NULL;
    }
    
    // Trim leading whitespace
    char *start = str;
    while (isspace(*start)) start++;
    
    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    // Move trimmed string to beginning
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';
    
    printf("[STRING_TRIM] Trimmed string: '%s'\n", str);
    return str;
}

// ============================================================================
// ADVANCED STRING OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Replace first occurrence of substring
 * 
 * Parameters:
 * - str: Source string
 * - old: Substring to replace
 * - new: Replacement string
 * 
 * Returns:
 * - Pointer to new string with replacement
 * - NULL on failure
 */
char* string_replace(const char *str, const char *old, const char *new) {
    if (!str || !old || !new) {
        printf("[ERROR] Invalid parameters for string replace\n");
        return NULL;
    }
    
    char *pos = strstr(str, old);
    if (!pos) {
        // No match found, return copy of original string
        return string_copy(str);
    }
    
    size_t str_len = strlen(str);
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    
    char *result = safe_malloc(str_len - old_len + new_len + 1);
    if (!result) {
        printf("[ERROR] Memory allocation failed for string replace\n");
        return NULL;
    }
    
    // Copy part before the match
    strncpy(result, str, pos - str);
    result[pos - str] = '\0';
    
    // Append replacement
    strcat(result, new);
    
    // Append part after the match
    strcat(result, pos + old_len);
    
    printf("[STRING_REPLACE] Replaced '%s' with '%s' in '%s'\n", old, new, str);
    return result;
}

/**
 * Replace all occurrences of substring
 * 
 * Parameters:
 * - str: Source string
 * - old: Substring to replace
 * - new: Replacement string
 * 
 * Returns:
 * - Pointer to new string with all replacements
 * - NULL on failure
 */
char* string_replace_all(const char *str, const char *old, const char *new) {
    if (!str || !old || !new) {
        printf("[ERROR] Invalid parameters for string replace all\n");
        return NULL;
    }
    
    char *result = string_copy(str);
    if (!result) {
        return NULL;
    }
    
    char *pos = strstr(result, old);
    while (pos) {
        size_t old_len = strlen(old);
        size_t new_len = strlen(new);
        size_t result_len = strlen(result);
        
        // Create new string with replacement
        char *temp = safe_malloc(result_len - old_len + new_len + 1);
        if (!temp) {
            safe_free(result);
            return NULL;
        }
        
        // Copy part before match
        strncpy(temp, result, pos - result);
        temp[pos - result] = '\0';
        
        // Append replacement
        strcat(temp, new);
        
        // Append part after match
        strcat(temp, pos + old_len);
        
        safe_free(result);
        result = temp;
        
        // Find next occurrence
        pos = strstr(result, old);
    }
    
    printf("[STRING_REPLACE_ALL] Replaced all '%s' with '%s'\n", old, new);
    return result;
}

/**
 * Insert string at specified position
 * 
 * Parameters:
 * - str: Source string
 * - pos: Position to insert at
 * - insert: String to insert
 * 
 * Returns:
 * - Pointer to new string with insertion
 * - NULL on failure
 */
char* string_insert(const char *str, int pos, const char *insert) {
    if (!str || !insert || pos < 0) {
        printf("[ERROR] Invalid parameters for string insert\n");
        return NULL;
    }
    
    size_t str_len = strlen(str);
    size_t insert_len = strlen(insert);
    
    if (pos > str_len) {
        pos = str_len;  // Insert at end
    }
    
    char *result = safe_malloc(str_len + insert_len + 1);
    if (!result) {
        printf("[ERROR] Memory allocation failed for string insert\n");
        return NULL;
    }
    
    // Copy part before insertion point
    strncpy(result, str, pos);
    result[pos] = '\0';
    
    // Append insertion
    strcat(result, insert);
    
    // Append part after insertion point
    strcat(result, str + pos);
    
    printf("[STRING_INSERT] Inserted '%s' at position %d\n", insert, pos);
    return result;
}

// ============================================================================
// CASE CONVERSION FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Convert string to uppercase
 * 
 * Parameters:
 * - str: String to convert
 * 
 * Returns:
 * - Pointer to uppercase string
 * - NULL on failure
 */
char* string_to_uppercase(const char *str) {
    if (!str) {
        printf("[ERROR] Cannot convert NULL string to uppercase\n");
        return NULL;
    }
    
    char *result = string_copy(str);
    if (!result) {
        return NULL;
    }
    
    for (size_t i = 0; result[i]; i++) {
        result[i] = toupper(result[i]);
    }
    
    printf("[STRING_TO_UPPERCASE] Converted: %s\n", result);
    return result;
}

/**
 * Convert string to lowercase
 * 
 * Parameters:
 * - str: String to convert
 * 
 * Returns:
 * - Pointer to lowercase string
 * - NULL on failure
 */
char* string_to_lowercase(const char *str) {
    if (!str) {
        printf("[ERROR] Cannot convert NULL string to lowercase\n");
        return NULL;
    }
    
    char *result = string_copy(str);
    if (!result) {
        return NULL;
    }
    
    for (size_t i = 0; result[i]; i++) {
        result[i] = tolower(result[i]);
    }
    
    printf("[STRING_TO_LOWERCASE] Converted: %s\n", result);
    return result;
}

/**
 * Convert string to title case
 * 
 * Parameters:
 * - str: String to convert
 * 
 * Returns:
 * - Pointer to title case string
 * - NULL on failure
 */
char* string_to_title_case(const char *str) {
    if (!str) {
        printf("[ERROR] Cannot convert NULL string to title case\n");
        return NULL;
    }
    
    char *result = string_copy(str);
    if (!result) {
        return NULL;
    }
    
    bool capitalize_next = true;
    for (size_t i = 0; result[i]; i++) {
        if (isspace(result[i])) {
            capitalize_next = true;
        } else if (capitalize_next) {
            result[i] = toupper(result[i]);
            capitalize_next = false;
        } else {
            result[i] = tolower(result[i]);
        }
    }
    
    printf("[STRING_TO_TITLE_CASE] Converted: %s\n", result);
    return result;
}

// ============================================================================
// PATTERN MATCHING FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Check if string contains substring
 * 
 * Parameters:
 * - str: String to search in
 * - substr: Substring to search for
 * 
 * Returns:
 * - true if substring found
 * - false otherwise
 */
bool string_contains(const char *str, const char *substr) {
    if (!str || !substr) {
        printf("[ERROR] Cannot search in NULL strings\n");
        return false;
    }
    
    bool result = strstr(str, substr) != NULL;
    printf("[STRING_CONTAINS] '%s' contains '%s': %s\n", 
           str, substr, result ? "true" : "false");
    return result;
}

/**
 * Find first occurrence of substring
 * 
 * Parameters:
 * - str: String to search in
 * - substr: Substring to search for
 * 
 * Returns:
 * - Position of first occurrence (0-based)
 * - -1 if not found
 */
int string_find_first(const char *str, const char *substr) {
    if (!str || !substr) {
        printf("[ERROR] Cannot search in NULL strings\n");
        return -1;
    }
    
    char *pos = strstr(str, substr);
    int result = pos ? (int)(pos - str) : -1;
    printf("[STRING_FIND_FIRST] '%s' in '%s' at position: %d\n", 
           substr, str, result);
    return result;
}

/**
 * Find last occurrence of substring
 * 
 * Parameters:
 * - str: String to search in
 * - substr: Substring to search for
 * 
 * Returns:
 * - Position of last occurrence (0-based)
 * - -1 if not found
 */
int string_find_last(const char *str, const char *substr) {
    if (!str || !substr) {
        printf("[ERROR] Cannot search in NULL strings\n");
        return -1;
    }
    
    int last_pos = -1;
    char *pos = strstr(str, substr);
    
    while (pos) {
        last_pos = (int)(pos - str);
        pos = strstr(pos + 1, substr);
    }
    
    printf("[STRING_FIND_LAST] '%s' in '%s' at position: %d\n", 
           substr, str, last_pos);
    return last_pos;
}

// ============================================================================
// TOKENIZATION FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Tokenize string using specified delimiters
 * 
 * Parameters:
 * - str: String to tokenize
 * - delimiters: Delimiter characters
 * 
 * Returns:
 * - Pointer to TokenList structure
 * - NULL on failure
 */
TokenList* string_tokenize(const char *str, const char *delimiters) {
    if (!str || !delimiters) {
        printf("[ERROR] Invalid parameters for tokenization\n");
        return NULL;
    }
    
    TokenList *token_list = safe_malloc(sizeof(TokenList));
    if (!token_list) {
        printf("[ERROR] Memory allocation failed for token list\n");
        return NULL;
    }
    
    token_list->tokens = safe_malloc(MAX_TOKENS * sizeof(char*));
    if (!token_list->tokens) {
        printf("[ERROR] Memory allocation failed for token array\n");
        safe_free(token_list);
        return NULL;
    }
    
    token_list->count = 0;
    token_list->capacity = MAX_TOKENS;
    
    // Create a copy of the string for tokenization
    char *str_copy = string_copy(str);
    if (!str_copy) {
        safe_free(token_list->tokens);
        safe_free(token_list);
        return NULL;
    }
    
    // Tokenize using strtok
    char *token = strtok(str_copy, delimiters);
    while (token && token_list->count < MAX_TOKENS) {
        token_list->tokens[token_list->count] = string_copy(token);
        token_list->count++;
        token = strtok(NULL, delimiters);
    }
    
    safe_free(str_copy);
    
    printf("[STRING_TOKENIZE] Tokenized into %d tokens\n", token_list->count);
    return token_list;
}

/**
 * Split string into words
 * 
 * Parameters:
 * - str: String to split
 * 
 * Returns:
 * - Pointer to TokenList of words
 * - NULL on failure
 */
TokenList* string_split_words(const char *str) {
    return string_tokenize(str, " \t\n\r");
}

/**
 * Free token list and all associated memory
 * 
 * Parameters:
 * - token_list: Token list to free
 */
void free_token_list(TokenList *token_list) {
    if (!token_list) {
        return;
    }
    
    for (int i = 0; i < token_list->count; i++) {
        safe_free(token_list->tokens[i]);
    }
    
    safe_free(token_list->tokens);
    safe_free(token_list);
    printf("[FREE_TOKEN_LIST] Freed token list\n");
}

/**
 * Print token list
 * 
 * Parameters:
 * - token_list: Token list to print
 */
void print_token_list(const TokenList *token_list) {
    if (!token_list) {
        printf("[ERROR] Cannot print NULL token list\n");
        return;
    }
    
    printf("\n=== TOKEN LIST ===\n");
    printf("Number of tokens: %d\n", token_list->count);
    
    for (int i = 0; i < token_list->count; i++) {
        printf("Token %d: '%s'\n", i + 1, token_list->tokens[i]);
    }
}

// ============================================================================
// STRING ANALYSIS FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Analyze string and generate comprehensive statistics
 * 
 * Parameters:
 * - str: String to analyze
 * 
 * Returns:
 * - Pointer to StringStats structure
 * - NULL on failure
 */
StringStats* analyze_string(const char *str) {
    if (!str) {
        printf("[ERROR] Cannot analyze NULL string\n");
        return NULL;
    }
    
    StringStats *stats = safe_malloc(sizeof(StringStats));
    if (!stats) {
        printf("[ERROR] Memory allocation failed for string stats\n");
        return NULL;
    }
    
    // Initialize all counters
    memset(stats, 0, sizeof(StringStats));
    
    stats->length = strlen(str);
    
    // Analyze each character
    bool in_word = false;
    bool in_sentence = false;
    
    for (size_t i = 0; i < stats->length; i++) {
        char c = str[i];
        
        // Character frequency
        stats->char_count[(unsigned char)c]++;
        
        // Character type analysis
        if (isalpha(c)) {
            char lower_c = tolower(c);
            if (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || 
                lower_c == 'o' || lower_c == 'u') {
                stats->vowel_count++;
            } else {
                stats->consonant_count++;
            }
        } else if (isdigit(c)) {
            stats->digit_count++;
        } else if (isspace(c)) {
            stats->space_count++;
            if (c == '\n' || c == '\r') {
                stats->paragraph_count++;
            }
        } else if (ispunct(c)) {
            stats->punctuation_count++;
            if (c == '.' || c == '!' || c == '?') {
                stats->sentence_count++;
            }
        }
        
        // Word counting
        if (isalnum(c) && !in_word) {
            stats->word_count++;
            in_word = true;
        } else if (!isalnum(c)) {
            in_word = false;
        }
    }
    
    // Calculate average word length
    if (stats->word_count > 0) {
        stats->average_word_length = (float)(stats->length - stats->space_count - stats->punctuation_count) / stats->word_count;
    }
    
    // Calculate Flesch readability score
    if (stats->sentence_count > 0 && stats->word_count > 0) {
        float avg_sentence_length = (float)stats->word_count / stats->sentence_count;
        float avg_syllables_per_word = 1.0; // Simplified calculation
        stats->readability_score = 206.835 - (1.015 * avg_sentence_length) - (84.6 * avg_syllables_per_word);
    }
    
    printf("[ANALYZE_STRING] Analyzed string of length %zu\n", stats->length);
    return stats;
}

/**
 * Print string statistics
 * 
 * Parameters:
 * - stats: Statistics to print
 */
void print_string_stats(const StringStats *stats) {
    if (!stats) {
        printf("[ERROR] Cannot print NULL statistics\n");
        return;
    }
    
    printf("\n=== STRING ANALYSIS STATISTICS ===\n");
    printf("Length: %zu characters\n", stats->length);
    printf("Words: %d\n", stats->word_count);
    printf("Sentences: %d\n", stats->sentence_count);
    printf("Paragraphs: %d\n", stats->paragraph_count);
    printf("Vowels: %d\n", stats->vowel_count);
    printf("Consonants: %d\n", stats->consonant_count);
    printf("Digits: %d\n", stats->digit_count);
    printf("Spaces: %d\n", stats->space_count);
    printf("Punctuation: %d\n", stats->punctuation_count);
    printf("Average word length: %.2f characters\n", stats->average_word_length);
    printf("Readability score: %.2f\n", stats->readability_score);
    
    // Print most frequent characters
    printf("\nMost frequent characters:\n");
    int max_freq = 0;
    for (int i = 0; i < 256; i++) {
        if (stats->char_count[i] > max_freq) {
            max_freq = stats->char_count[i];
        }
    }
    
    for (int i = 0; i < 256 && max_freq > 0; i++) {
        if (stats->char_count[i] == max_freq && isprint(i)) {
            printf("'%c': %d occurrences\n", (char)i, stats->char_count[i]);
        }
    }
}

/**
 * Free string statistics
 * 
 * Parameters:
 * - stats: Statistics to free
 */
void free_string_stats(StringStats *stats) {
    if (stats) {
        safe_free(stats);
        printf("[FREE_STRING_STATS] Freed string statistics\n");
    }
}

/**
 * Check if string is a palindrome
 * 
 * Parameters:
 * - str: String to check
 * 
 * Returns:
 * - true if palindrome
 * - false otherwise
 */
bool is_palindrome(const char *str) {
    if (!str) {
        printf("[ERROR] Cannot check palindrome for NULL string\n");
        return false;
    }
    
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        if (tolower(str[i]) != tolower(str[len - 1 - i])) {
            printf("[IS_PALINDROME] '%s' is not a palindrome\n", str);
            return false;
        }
    }
    
    printf("[IS_PALINDROME] '%s' is a palindrome\n", str);
    return true;
}

// ============================================================================
// VALIDATION FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Validate email address format
 * 
 * Parameters:
 * - email: Email to validate
 * 
 * Returns:
 * - true if valid email format
 * - false otherwise
 */
bool is_valid_email(const char *email) {
    if (!email || strlen(email) == 0) {
        return false;
    }
    
    // Simple email validation
    bool has_at = false;
    bool has_dot_after_at = false;
    int at_pos = -1;
    
    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') {
            if (has_at) return false; // Multiple @ symbols
            has_at = true;
            at_pos = i;
        } else if (email[i] == '.' && has_at && i > at_pos + 1) {
            has_dot_after_at = true;
        }
    }
    
    bool result = has_at && has_dot_after_at && at_pos > 0;
    printf("[IS_VALID_EMAIL] '%s' is %s\n", email, result ? "valid" : "invalid");
    return result;
}

/**
 * Check if string contains only numeric characters
 * 
 * Parameters:
 * - str: String to check
 * 
 * Returns:
 * - true if numeric
 * - false otherwise
 */
bool is_numeric(const char *str) {
    if (!str || strlen(str) == 0) {
        return false;
    }
    
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]) && str[i] != '.' && str[i] != '-' && str[i] != '+') {
            printf("[IS_NUMERIC] '%s' is not numeric\n", str);
            return false;
        }
    }
    
    printf("[IS_NUMERIC] '%s' is numeric\n", str);
    return true;
}

// ============================================================================
// MEMORY MANAGEMENT FUNCTIONS
// ============================================================================

/**
 * Safe memory allocation with error checking
 * 
 * Parameters:
 * - size: Number of bytes to allocate
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure
 */
void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        printf("[ERROR] Memory allocation failed: %zu bytes\n", size);
    }
    return ptr;
}

/**
 * Safe memory deallocation
 * 
 * Parameters:
 * - ptr: Pointer to memory to free
 */
void safe_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate basic string operations
 */
void demonstrate_basic_operations(void) {
    printf("\n=== BASIC STRING OPERATIONS DEMONSTRATION ===\n");
    
    const char *original = "Hello, World!";
    
    // String copying
    char *copy = string_copy(original);
    if (copy) {
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);
        safe_free(copy);
    }
    
    // String concatenation
    char *concatenated = string_concat("Hello", ", World!");
    if (concatenated) {
        printf("Concatenated: %s\n", concatenated);
        safe_free(concatenated);
    }
    
    // Substring extraction
    char *substring = string_substring(original, 7, 5);
    if (substring) {
        printf("Substring: %s\n", substring);
        safe_free(substring);
    }
    
    // Case conversion
    char *uppercase = string_to_uppercase(original);
    char *lowercase = string_to_lowercase(original);
    char *title_case = string_to_title_case("hello world");
    
    if (uppercase && lowercase && title_case) {
        printf("Uppercase: %s\n", uppercase);
        printf("Lowercase: %s\n", lowercase);
        printf("Title case: %s\n", title_case);
        
        safe_free(uppercase);
        safe_free(lowercase);
        safe_free(title_case);
    }
}

/**
 * Demonstrate advanced string operations
 */
void demonstrate_advanced_operations(void) {
    printf("\n=== ADVANCED STRING OPERATIONS DEMONSTRATION ===\n");
    
    const char *text = "The quick brown fox jumps over the lazy dog";
    
    // String replacement
    char *replaced = string_replace(text, "fox", "cat");
    if (replaced) {
        printf("Original: %s\n", text);
        printf("Replaced: %s\n", replaced);
        safe_free(replaced);
    }
    
    // Pattern matching
    printf("Contains 'fox': %s\n", string_contains(text, "fox") ? "true" : "false");
    printf("First 'o' at position: %d\n", string_find_first(text, "o"));
    printf("Last 'o' at position: %d\n", string_find_last(text, "o"));
    
    // String analysis
    StringStats *stats = analyze_string(text);
    if (stats) {
        print_string_stats(stats);
        free_string_stats(stats);
    }
}

/**
 * Demonstrate tokenization
 */
void demonstrate_tokenization(void) {
    printf("\n=== TOKENIZATION DEMONSTRATION ===\n");
    
    const char *text = "apple,banana,cherry,date,elderberry";
    
    // Tokenize by comma
    TokenList *tokens = string_tokenize(text, ",");
    if (tokens) {
        print_token_list(tokens);
        free_token_list(tokens);
    }
    
    // Split into words
    const char *sentence = "The quick brown fox jumps over the lazy dog";
    TokenList *words = string_split_words(sentence);
    if (words) {
        print_token_list(words);
        free_token_list(words);
    }
}

/**
 * Demonstrate validation functions
 */
void demonstrate_validation(void) {
    printf("\n=== VALIDATION DEMONSTRATION ===\n");
    
    // Email validation
    const char *emails[] = {
        "user@example.com",
        "invalid.email",
        "test@domain.co.uk",
        "bad@email@domain.com"
    };
    
    for (int i = 0; i < 4; i++) {
        printf("Email '%s' is %s\n", emails[i], 
               is_valid_email(emails[i]) ? "valid" : "invalid");
    }
    
    // Numeric validation
    const char *numbers[] = {
        "12345",
        "3.14159",
        "-42",
        "abc123"
    };
    
    for (int i = 0; i < 4; i++) {
        printf("'%s' is %s\n", numbers[i], 
               is_numeric(numbers[i]) ? "numeric" : "not numeric");
    }
    
    // Palindrome check
    const char *palindromes[] = {
        "racecar",
        "level",
        "hello",
        "A man a plan a canal Panama"
    };
    
    for (int i = 0; i < 4; i++) {
        printf("'%s' is %s\n", palindromes[i], 
               is_palindrome(palindromes[i]) ? "a palindrome" : "not a palindrome");
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("ADVANCED STRING MANIPULATION DEMONSTRATION\n");
    printf("==========================================\n");
    
    // Run demonstrations
    demonstrate_basic_operations();
    demonstrate_advanced_operations();
    demonstrate_tokenization();
    demonstrate_validation();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Basic string operations (copy, concat, substring)\n");
    printf("2. Advanced string manipulation (replace, insert, remove)\n");
    printf("3. Case conversion functions\n");
    printf("4. Pattern matching and searching\n");
    printf("5. String tokenization and parsing\n");
    printf("6. Text analysis and statistics\n");
    printf("7. String validation functions\n");
    printf("8. Memory management for string operations\n");
    printf("9. Error handling and input validation\n");
    printf("10. Comprehensive string utility library\n");
    
    return 0;
}




