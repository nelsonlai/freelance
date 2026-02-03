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

#include <iostream>
#include <string>
using namespace std;

int add(int a, int b){
    int x = 0;
    static int c = 0 ;
    cout << "add x: " << x << " add c: " << c << endl;
    x ++;
    c ++;
    return a + b + c;
}

int sub(int a, int b){
    int x = 0;
    static int c = 0 ;
    cout << "sub x: " << x << " sub c: " << c << endl;
    x ++;
    c ++;
    return a - b - c;
}
int main(){
    cout<<"First Time: "<<add(2,3)<<endl;
    cout<<"Second Time: "<<add(2,3)<<endl;
    cout<<"Third Time: "<<add(2,3)<<endl;
    return 0;
};