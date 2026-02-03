/**
 * Solution 10.1: File Copying Utility
 * Week 10 - File Input/Output
 * 
 * Description: File copying utility
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    
    FILE *source = fopen(argv[1], "rb");
    if (source == NULL) {
        printf("Error: Cannot open source file '%s'\n", argv[1]);
        return 1;
    }
    
    FILE *destination = fopen(argv[2], "wb");
    if (destination == NULL) {
        printf("Error: Cannot create destination file '%s'\n", argv[2]);
        fclose(source);
        return 1;
    }
    
    int ch;
    long bytescopied = 0;
    
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
        bytescopied++;
    }
    
    fclose(source);
    fclose(destination);
    
    printf("File copied successfully!\n");
    printf("Bytes copied: %ld\n", bytescopied);
    
    return 0;
}