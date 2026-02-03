/*
 * C++ PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates C++ programming concepts and techniques:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental C++ PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

#include <stdio.h>

int main() {
    int a, b;  // 宣告兩個整數變數

    // 提示使用者輸入
    printf("請輸入兩個整數：");

    // 使用 scanf 接收輸入
    scanf("%d %d", &a, &b);

    // 計算並輸出結果
    printf("兩數的和是：%d\n", a + b);

    return 0;
}
