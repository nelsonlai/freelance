/*
 * Problem: Substring with Concatenation of All Words
 * Difficulty: Hard
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} HashEntry;

typedef struct {
    HashEntry* entries;
    int size;
    int capacity;
} HashMap;

HashMap* createMap(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->entries = (HashEntry*)calloc(capacity, sizeof(HashEntry));
    map->size = 0;
    map->capacity = capacity;
    return map;
}

void put(HashMap* map, char* key, int value) {
    for (int i = 0; i < map->capacity; i++) {
        int idx = (i + (int)key) % map->capacity;
        if (map->entries[idx].key == NULL || strcmp(map->entries[idx].key, key) == 0) {
            map->entries[idx].key = key;
            map->entries[idx].value = value;
            map->size++;
            return;
        }
    }
}

int get(HashMap* map, char* key) {
    for (int i = 0; i < map->capacity; i++) {
        int idx = (i + (int)key) % map->capacity;
        if (map->entries[idx].key != NULL && strcmp(map->entries[idx].key, key) == 0) {
            return map->entries[idx].value;
        }
    }
    return 0;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    *returnSize = 0;
    if (!s || !words || wordsSize == 0) {
        return NULL;
    }
    
    int wordLen = strlen(words[0]);
    int totalLen = wordsSize * wordLen;
    int sLen = strlen(s);
    
    HashMap* wordCount = createMap(wordsSize * 2);
    for (int i = 0; i < wordsSize; i++) {
        int count = get(wordCount, words[i]);
        put(wordCount, words[i], count + 1);
    }
    
    int* result = (int*)malloc(sLen * sizeof(int));
    int resultIdx = 0;
    
    for (int i = 0; i < wordLen; i++) {
        int left = i;
        HashMap* seen = createMap(wordsSize * 2);
        int count = 0;
        
        for (int j = i; j <= sLen - wordLen; j += wordLen) {
            char* word = (char*)malloc((wordLen + 1) * sizeof(char));
            strncpy(word, s + j, wordLen);
            word[wordLen] = '\0';
            
            if (get(wordCount, word) > 0) {
                int seenCount = get(seen, word);
                put(seen, word, seenCount + 1);
                count++;
                
                while (get(seen, word) > get(wordCount, word)) {
                    char* leftWord = (char*)malloc((wordLen + 1) * sizeof(char));
                    strncpy(leftWord, s + left, wordLen);
                    leftWord[wordLen] = '\0';
                    put(seen, leftWord, get(seen, leftWord) - 1);
                    count--;
                    left += wordLen;
                    free(leftWord);
                }
                
                if (count == wordsSize) {
                    result[resultIdx++] = left;
                    char* leftWord = (char*)malloc((wordLen + 1) * sizeof(char));
                    strncpy(leftWord, s + left, wordLen);
                    leftWord[wordLen] = '\0';
                    put(seen, leftWord, get(seen, leftWord) - 1);
                    count--;
                    left += wordLen;
                    free(leftWord);
                }
            } else {
                for (int k = 0; k < seen->capacity; k++) {
                    seen->entries[k].key = NULL;
                }
                seen->size = 0;
                count = 0;
                left = j + wordLen;
            }
            free(word);
        }
        free(seen->entries);
        free(seen);
    }
    
    free(wordCount->entries);
    free(wordCount);
    
    *returnSize = resultIdx;
    return result;
}