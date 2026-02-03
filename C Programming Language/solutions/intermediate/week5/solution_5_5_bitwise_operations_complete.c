/**
 * Solution 5.5: Complete Bitwise Operations and Bit Manipulation
 * Week 5 - Functions and Modular Programming
 * 
 * Description: Comprehensive bit manipulation techniques and bitwise operators
 */

#include <stdio.h>
#include <stdint.h>

// Function prototypes for bit manipulation
void print_binary(unsigned int n, int bits);
int count_set_bits(unsigned int n);
int is_power_of_two(unsigned int n);
unsigned int reverse_bits(unsigned int n, int bits);
unsigned int swap_bits(unsigned int n, int pos1, int pos2);
void demonstrate_bit_fields();

/*
 & - Bitwise AND    # mask operation
   0 & 0 = 0
   0 & 1 = 0
   1 & 0 = 0
   1 & 1 = 1
 | - Bitwise OR     # set operation
   0 | 0 = 0
   0 | 1 = 1
   1 | 0 = 1
   1 | 1 = 1
 ^ - Bitwise XOR    # toggle operation
   0 ^ 0 = 0
   0 ^ 1 = 1
   1 ^ 0 = 1
   1 ^ 1 = 0
 ~ - Bitwise NOT    # invert operation
 3 * 15 = 45 (15 = 8 + 4 + 2 + 1)
 3 << 3 (2^3 = 8)
 3 << 2 (2^2 = 4)
 3 << 1 (2^1 = 2)
 3 << 0 (2^0 = 1)
 << - Left shift    # multiply by 2
 >> - Right shift   # divide by 2
*/
void basic_bitwise_operators() {
    printf("=== Basic Bitwise Operators ===\n");
    
    unsigned int a = 0b11010110;  // 214 in decimal
    unsigned int b = 0b10110011;  // 179 in decimal
    
    printf("a = %u (", a);
    print_binary(a, 8);
    printf(")\n");
    
    printf("b = %u (", b);
    print_binary(b, 8);
    printf(")\n\n");
    
    // AND operation
    printf("a & b = %u (", a & b);
    print_binary(a & b, 8);
    printf(") - Bitwise AND\n");
    
    // OR operation
    printf("a | b = %u (", a | b);
    print_binary(a | b, 8);
    printf(") - Bitwise OR\n");
    
    // XOR operation
    printf("a ^ b = %u (", a ^ b);
    print_binary(a ^ b, 8);
    printf(") - Bitwise XOR\n");
    
    // NOT operation
    printf("~a = %u (", ~a & 0xFF);
    print_binary(~a & 0xFF, 8);
    printf(") - Bitwise NOT\n");
    
    // Left shift
    printf("a << 2 = %u (", a << 2);
    print_binary(a << 2, 10);
    printf(") - Left shift by 2\n");
    
    // Right shift
    printf("a >> 2 = %u (", a >> 2);
    print_binary(a >> 2, 6);
    printf(") - Right shift by 2\n");
}

void bit_manipulation_techniques() {
    printf("\n=== Bit Manipulation Techniques ===\n");
    
    unsigned int num = 0b10110100;  // 180 in decimal
    
    printf("Working with number: %u (", num);
    print_binary(num, 8);
    printf(")\n\n");
    
    // Set a bit
    int bit_to_set = 1;
    unsigned int set_result = num | (1 << bit_to_set);
    printf("Set bit %d: %u (", bit_to_set, set_result);
    print_binary(set_result, 8);
    printf(")\n");
    
    // Clear a bit
    int bit_to_clear = 5;
    unsigned int clear_result = num & ~(1 << bit_to_clear);
    printf("Clear bit %d: %u (", bit_to_clear, clear_result);
    print_binary(clear_result, 8);
    printf(")\n");
    
    // Toggle a bit
    int bit_to_toggle = 3;
    unsigned int toggle_result = num ^ (1 << bit_to_toggle);
    printf("Toggle bit %d: %u (", bit_to_toggle, toggle_result);
    print_binary(toggle_result, 8);
    printf(")\n");
    
    // Check if a bit is set
    int bit_to_check = 4;
    int is_set = (num & (1 << bit_to_check)) != 0;
    printf("Bit %d is %s\n", bit_to_check, is_set ? "SET" : "CLEAR");
    
    // Count set bits
    printf("Number of set bits: %d\n", count_set_bits(num));
    
    // Check if power of two
    printf("Is power of two: %s\n", is_power_of_two(num) ? "YES" : "NO");
}

void advanced_bit_operations() {
    printf("\n=== Advanced Bit Operations ===\n");
    
    unsigned int value = 0b11010110;
    
    printf("Original: %u (", value);
    print_binary(value, 8);
    printf(")\n");
    
    // Reverse bits
    unsigned int reversed = reverse_bits(value, 8);
    printf("Reversed: %u (", reversed);
    print_binary(reversed, 8);
    printf(")\n");
    
    // Swap specific bits
    unsigned int swapped = swap_bits(value, 1, 6);
    printf("Swap bits 1 and 6: %u (", swapped);
    print_binary(swapped, 8);
    printf(")\n");
    
    // Find rightmost set bit
    unsigned int rightmost = value & (-value);
    printf("Rightmost set bit: %u (", rightmost);
    print_binary(rightmost, 8);
    printf(")\n");
    
    // Clear rightmost set bit
    unsigned int cleared_rightmost = value & (value - 1);
    printf("Clear rightmost set bit: %u (", cleared_rightmost);
    print_binary(cleared_rightmost, 8);
    printf(")\n");
}

void bit_manipulation_tricks() {
    printf("\n=== Bit Manipulation Tricks ===\n");
    
    // Multiply by power of 2
    int x = 15;
    printf("%d * 8 = %d (using << 3)\n", x, x << 3);
    
    // Divide by power of 2
    printf("%d / 4 = %d (using >> 2)\n", x, x >> 2);
    
    // Check if odd/even
    printf("%d is %s (using & 1)\n", x, (x & 1) ? "ODD" : "EVEN");
    
    // Swap two numbers using XOR
    int a = 25, b = 30;
    printf("Before XOR swap: a=%d, b=%d\n", a, b);
    a ^= b;
    b ^= a;
    a ^= b;
    printf("After XOR swap: a=%d, b=%d\n", a, b);
    
    // Absolute value using bit manipulation
    int n = -42;
    int mask = n >> 31;  // All 1s if negative, all 0s if positive
    int abs_n = (n ^ mask) - mask;
    printf("Absolute value of %d: %d\n", n, abs_n);
    
    // Min and Max using bit manipulation
    a = 10; b = 15;
    int min_val = b ^ ((a ^ b) & -(a < b));
    int max_val = a ^ ((a ^ b) & -(a < b));
    printf("Min(%d, %d) = %d, Max(%d, %d) = %d\n", a, b, min_val, a, b, max_val);
}

void bit_field_structures() {
    printf("\n=== Bit Field Structures ===\n");
    
    // Define a structure with bit fields
    struct StatusRegister {
        unsigned int ready : 1;        // 1 bit
        unsigned int error : 1;        // 1 bit
        unsigned int mode : 3;         // 3 bits (0-7)
        unsigned int priority : 4;     // 4 bits (0-15)
        unsigned int reserved : 23;    // 23 bits
    };
    
    struct StatusRegister status = {0};
    
    // Set bit fields
    status.ready = 1;
    status.error = 0;
    status.mode = 5;
    status.priority = 12;
    
    printf("Status register values:\n");
    printf("Ready: %u\n", status.ready);
    printf("Error: %u\n", status.error);
    printf("Mode: %u\n", status.mode);
    printf("Priority: %u\n", status.priority);
    
    // View as integer (platform dependent)
    unsigned int *status_int = (unsigned int*)&status;
    printf("As integer: 0x%08X (", *status_int);
    print_binary(*status_int, 32);
    printf(")\n");
    
    // Demonstrate packing
    printf("Size of structure: %zu bytes\n", sizeof(status));
}

void practical_bit_applications() {
    printf("\n=== Practical Bit Applications ===\n");
    
    // Permission system (like Unix file permissions)
    #define READ_PERM    0x4  // 100 in binary
    #define WRITE_PERM   0x2  // 010 in binary
    #define EXEC_PERM    0x1  // 001 in binary
    
    unsigned int permissions = 0;
    
    // Grant permissions
    permissions |= READ_PERM;
    permissions |= WRITE_PERM;
    
    printf("Current permissions: ");
    printf("Read: %s, ", (permissions & READ_PERM) ? "YES" : "NO");
    printf("Write: %s, ", (permissions & WRITE_PERM) ? "YES" : "NO");
    printf("Execute: %s\n", (permissions & EXEC_PERM) ? "YES" : "NO");
    
    // Revoke write permission
    permissions &= ~WRITE_PERM;
    printf("After revoking write: ");
    printf("Read: %s, ", (permissions & READ_PERM) ? "YES" : "NO");
    printf("Write: %s, ", (permissions & WRITE_PERM) ? "YES" : "NO");
    printf("Execute: %s\n", (permissions & EXEC_PERM) ? "YES" : "NO");
    
    // Color representation (RGB)
    unsigned int color = 0xFF4500;  // Orange color
    unsigned int red = (color >> 16) & 0xFF;
    unsigned int green = (color >> 8) & 0xFF;
    unsigned int blue = color & 0xFF;
    
    printf("\nColor 0x%06X breakdown:\n", color);
    printf("Red: %u, Green: %u, Blue: %u\n", red, green, blue);
}

// Helper function implementations
void print_binary(unsigned int n, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int is_power_of_two(unsigned int n) {
    return n && !(n & (n - 1));
}

unsigned int reverse_bits(unsigned int n, int bits) {
    unsigned int result = 0;
    for (int i = 0; i < bits; i++) {
        result <<= 1;
        result |= (n & 1);
        n >>= 1;
    }
    return result;
}

unsigned int swap_bits(unsigned int n, int pos1, int pos2) {
    // Get the bits at positions pos1 and pos2
    unsigned int bit1 = (n >> pos1) & 1;
    unsigned int bit2 = (n >> pos2) & 1;
    
    // If bits are different, swap them
    if (bit1 != bit2) {
        n ^= (1 << pos1);  // Toggle bit at pos1
        n ^= (1 << pos2);  // Toggle bit at pos2
    }
    
    return n;
}

int main() {
    printf("COMPREHENSIVE BITWISE OPERATIONS AND BIT MANIPULATION\n");
    printf("====================================================\n\n");
    
    basic_bitwise_operators();
    bit_manipulation_techniques();
    advanced_bit_operations();
    bit_manipulation_tricks();
    bit_field_structures();
    practical_bit_applications();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Basic bitwise operators (&, |, ^, ~, <<, >>)\n");
    printf("- Bit manipulation techniques (set, clear, toggle, check)\n");
    printf("- Advanced operations (reverse, swap, count bits)\n");
    printf("- Bit manipulation tricks and optimizations\n");
    printf("- Bit field structures\n");
    printf("- Practical applications (permissions, colors, etc.)\n");
    
    return 0;
}
