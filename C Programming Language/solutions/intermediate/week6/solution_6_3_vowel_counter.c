/**
 * Solution 6.3: Vowel Counter
 * Week 6 - Arrays and String Basics
 * 
 * Description: Count vowels in a string
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countVowels(char str[]) {
    int count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    
    return count;
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\n")] = '\0';
    
    int vowels = countVowels(str);
    
    printf("Number of vowels: %d\n", vowels);
    
    char *newstr;
    /* str = "Xyz abc Mnd abc QPR abc" */
    newstr = str;
    do {
        printf("New string: %s\n", newstr); /* print the new string */
        newstr = strstr(str, "abc");
        newstr = strstr(newstr + 3, "abc");
        newstr = strstr(newstr + 3, "abc");
    } while (newstr != NULL);
    

    
    
    return 0;
}