/**
 * Advanced Bitwise Operations
 * Comprehensive demonstration of bit manipulation techniques and applications
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// Bit manipulation macros
#define SET_BIT(n, pos)     ((n) |= (1ULL << (pos)))
#define CLEAR_BIT(n, pos)   ((n) &= ~(1ULL << (pos)))
#define TOGGLE_BIT(n, pos)  ((n) ^= (1ULL << (pos)))
#define CHECK_BIT(n, pos)   (((n) >> (pos)) & 1ULL)
#define MASK(bits)          ((1ULL << (bits)) - 1)

// Bit field structures for various applications
struct CPUFlags {
    unsigned int carry : 1;
    unsigned int zero : 1;
    unsigned int interrupt : 1;
    unsigned int decimal : 1;
    unsigned int break_flag : 1;
    unsigned int unused : 1;
    unsigned int overflow : 1;
    unsigned int negative : 1;
};

struct RGBColor {
    unsigned int blue : 8;
    unsigned int green : 8;
    unsigned int red : 8;
    unsigned int alpha : 8;
};

struct FilePermissions {
    unsigned int others_execute : 1;
    unsigned int others_write : 1;
    unsigned int others_read : 1;
    unsigned int group_execute : 1;
    unsigned int group_write : 1;
    unsigned int group_read : 1;
    unsigned int owner_execute : 1;
    unsigned int owner_write : 1;
    unsigned int owner_read : 1;
};

// Function prototypes
void print_binary(uint64_t n, int bits);
void print_binary_formatted(uint64_t n, int bits);
int count_set_bits(uint64_t n);
int count_trailing_zeros(uint64_t n);
int count_leading_zeros(uint64_t n);
uint64_t reverse_bits(uint64_t n, int bits);
bool is_power_of_two(uint64_t n);
uint64_t next_power_of_two(uint64_t n);
uint64_t isolate_rightmost_set_bit(uint64_t n);
uint64_t clear_rightmost_set_bit(uint64_t n);
uint64_t set_rightmost_unset_bit(uint64_t n);
void demonstrate_bit_hacks();
void demonstrate_bit_fields();
void demonstrate_practical_applications();

void demonstrate_basic_bitwise_operations() {
    printf("=== Basic Bitwise Operations ===\n");
    
    uint32_t a = 0b11010110;  // 214
    uint32_t b = 0b10110011;  // 179
    
    printf("a = %u (", a);
    print_binary(a, 8);
    printf(")\n");
    
    printf("b = %u (", b);
    print_binary(b, 8);
    printf(")\n\n");
    
    // Basic operations
    printf("Bitwise AND (a & b):\n");
    uint32_t result = a & b;
    printf("Result = %u (", result);
    print_binary(result, 8);
    printf(")\n");
    
    printf("\nBitwise OR (a | b):\n");
    result = a | b;
    printf("Result = %u (", result);
    print_binary(result, 8);
    printf(")\n");
    
    printf("\nBitwise XOR (a ^ b):\n");
    result = a ^ b;
    printf("Result = %u (", result);
    print_binary(result, 8);
    printf(")\n");
    
    printf("\nBitwise NOT (~a):\n");
    result = ~a & 0xFF;  // Mask to 8 bits
    printf("Result = %u (", result);
    print_binary(result, 8);
    printf(")\n");
    
    printf("\nLeft Shift (a << 2):\n");
    result = a << 2;
    printf("Result = %u (", result);
    print_binary(result, 10);
    printf(")\n");
    
    printf("\nRight Shift (a >> 2):\n");
    result = a >> 2;
    printf("Result = %u (", result);
    print_binary(result, 6);
    printf(")\n");
}

void demonstrate_bit_manipulation_techniques() {
    printf("\n=== Bit Manipulation Techniques ===\n");
    
    uint32_t num = 0b10110100;  // 180
    
    printf("Working with number: %u (", num);
    print_binary(num, 8);
    printf(")\n\n");
    
    // Set specific bits
    printf("Setting bits 0 and 3:\n");
    uint32_t modified = num;
    SET_BIT(modified, 0);
    SET_BIT(modified, 3);
    printf("Result: %u (", modified);
    print_binary(modified, 8);
    printf(")\n");
    
    // Clear specific bits
    printf("\nClearing bits 2 and 5:\n");
    modified = num;
    CLEAR_BIT(modified, 2);
    CLEAR_BIT(modified, 5);
    printf("Result: %u (", modified);
    print_binary(modified, 8);
    printf(")\n");
    
    // Toggle specific bits
    printf("\nToggling bits 1 and 6:\n");
    modified = num;
    TOGGLE_BIT(modified, 1);
    TOGGLE_BIT(modified, 6);
    printf("Result: %u (", modified);
    print_binary(modified, 8);
    printf(")\n");
    
    // Check specific bits
    printf("\nChecking individual bits:\n");
    for (int i = 0; i < 8; i++) {
        printf("Bit %d: %s\n", i, CHECK_BIT(num, i) ? "SET" : "CLEAR");
    }
}

void demonstrate_advanced_bit_operations() {
    printf("\n=== Advanced Bit Operations ===\n");
    
    uint64_t numbers[] = {0b11010110, 0b10000000, 0b11111111, 0b10101010};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < count; i++) {
        uint64_t n = numbers[i];
        
        printf("\nNumber: %llu (", n);
        print_binary(n, 8);
        printf(")\n");
        
        printf("Set bits: %d\n", count_set_bits(n));
        printf("Trailing zeros: %d\n", count_trailing_zeros(n));
        printf("Leading zeros: %d\n", count_leading_zeros(n));
        printf("Is power of 2: %s\n", is_power_of_two(n) ? "Yes" : "No");
        
        if (!is_power_of_two(n)) {
            printf("Next power of 2: %llu\n", next_power_of_two(n));
        }
        
        printf("Reversed bits: %llu (", reverse_bits(n, 8));
        print_binary(reverse_bits(n, 8), 8);
        printf(")\n");
        
        printf("Rightmost set bit: %llu (", isolate_rightmost_set_bit(n));
        print_binary(isolate_rightmost_set_bit(n), 8);
        printf(")\n");
    }
}

void demonstrate_bit_hacks() {
    printf("\n=== Bit Manipulation Hacks ===\n");
    
    // Swap two numbers using XOR
    int x = 25, y = 30;
    printf("XOR Swap: x=%d, y=%d\n", x, y);
    x ^= y;
    y ^= x;
    x ^= y;
    printf("After swap: x=%d, y=%d\n", x, y);
    
    // Check if number is odd/even
    int test_nums[] = {15, 16, 23, 100};
    printf("\nOdd/Even check using bit operations:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d is %s\n", test_nums[i], (test_nums[i] & 1) ? "odd" : "even");
    }
    
    // Multiply/divide by powers of 2
    int base = 17;
    printf("\nMultiplication/Division by powers of 2:\n");
    printf("%d * 4 = %d (using << 2)\n", base, base << 2);
    printf("%d * 8 = %d (using << 3)\n", base, base << 3);
    printf("%d / 2 = %d (using >> 1)\n", base, base >> 1);
    printf("%d / 4 = %d (using >> 2)\n", base, base >> 2);
    
    // Absolute value using bit manipulation
    int negative = -42;
    int mask = negative >> 31;
    int absolute = (negative ^ mask) - mask;
    printf("\nAbsolute value of %d: %d (using bit manipulation)\n", negative, absolute);
    
    // Min/Max without branching
    int a = 10, b = 15;
    int min_val = b ^ ((a ^ b) & -(a < b));
    int max_val = a ^ ((a ^ b) & -(a < b));
    printf("Min(%d, %d) = %d, Max(%d, %d) = %d (branchless)\n", a, b, min_val, a, b, max_val);
    
    // Count set bits (Brian Kernighan's algorithm)
    uint32_t n = 0b11010110;
    int count = 0;
    uint32_t temp = n;
    printf("\nCounting set bits in %u:\n", n);
    while (temp) {
        temp &= temp - 1;  // Clear rightmost set bit
        count++;
        printf("Step %d: ", count);
        print_binary(temp, 8);
        printf("\n");
    }
    printf("Total set bits: %d\n", count);
}

void demonstrate_bit_fields() {
    printf("\n=== Bit Fields Applications ===\n");
    
    // CPU Status Register
    struct CPUFlags cpu = {0};
    cpu.carry = 1;
    cpu.zero = 0;
    cpu.interrupt = 1;
    cpu.overflow = 0;
    
    printf("CPU Flags:\n");
    printf("Carry: %u, Zero: %u, Interrupt: %u, Overflow: %u\n",
           cpu.carry, cpu.zero, cpu.interrupt, cpu.overflow);
    
    uint8_t *cpu_byte = (uint8_t*)&cpu;
    printf("As byte: 0x%02X (", *cpu_byte);
    print_binary(*cpu_byte, 8);
    printf(")\n");
    
    // RGB Color representation
    struct RGBColor color = {0};
    color.red = 255;
    color.green = 128;
    color.blue = 64;
    color.alpha = 255;
    
    printf("\nRGB Color (R=%u, G=%u, B=%u, A=%u):\n", 
           color.red, color.green, color.blue, color.alpha);
    
    uint32_t *color_int = (uint32_t*)&color;
    printf("As 32-bit integer: 0x%08X\n", *color_int);
    
    // File Permissions (Unix-style)
    struct FilePermissions perms = {0};
    perms.owner_read = 1;
    perms.owner_write = 1;
    perms.owner_execute = 1;
    perms.group_read = 1;
    perms.group_execute = 1;
    perms.others_read = 1;
    
    printf("\nFile Permissions:\n");
    printf("Owner: %c%c%c\n", 
           perms.owner_read ? 'r' : '-',
           perms.owner_write ? 'w' : '-',
           perms.owner_execute ? 'x' : '-');
    printf("Group: %c%c%c\n", 
           perms.group_read ? 'r' : '-',
           perms.group_write ? 'w' : '-',
           perms.group_execute ? 'x' : '-');
    printf("Others: %c%c%c\n", 
           perms.others_read ? 'r' : '-',
           perms.others_write ? 'w' : '-',
           perms.others_execute ? 'x' : '-');
    
    uint16_t *perm_bits = (uint16_t*)&perms;
    printf("As octal: %03o\n", *perm_bits);
}

void demonstrate_practical_applications() {
    printf("\n=== Practical Bit Manipulation Applications ===\n");
    
    // Bit set implementation
    printf("Bit Set Implementation:\n");
    uint64_t bit_set = 0;
    
    // Add elements to set
    int elements[] = {3, 7, 15, 31, 63};
    printf("Adding elements: ");
    for (int i = 0; i < 5; i++) {
        SET_BIT(bit_set, elements[i]);
        printf("%d ", elements[i]);
    }
    printf("\n");
    
    printf("Bit set: ");
    print_binary_formatted(bit_set, 64);
    printf("\n");
    
    // Check membership
    int test_elements[] = {3, 5, 7, 10, 15};
    printf("Membership test:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d: %s\n", test_elements[i], 
               CHECK_BIT(bit_set, test_elements[i]) ? "Present" : "Absent");
    }
    
    // Remove elements
    printf("Removing element 7\n");
    CLEAR_BIT(bit_set, 7);
    printf("7 present: %s\n", CHECK_BIT(bit_set, 7) ? "Yes" : "No");
    
    // Bit manipulation for encryption (simple XOR cipher)
    printf("\nSimple XOR Encryption:\n");
    char message[] = "Hello World";
    uint8_t key = 0xAB;
    
    printf("Original: %s\n", message);
    
    // Encrypt
    for (int i = 0; message[i]; i++) {
        message[i] ^= key;
    }
    printf("Encrypted: ");
    for (int i = 0; message[i]; i++) {
        printf("%02X ", (unsigned char)message[i]);
    }
    printf("\n");
    
    // Decrypt
    for (int i = 0; message[i]; i++) {
        message[i] ^= key;
    }
    printf("Decrypted: %s\n", message);
    
    // Gray code generation
    printf("\nGray Code Generation (4 bits):\n");
    for (int i = 0; i < 16; i++) {
        int gray = i ^ (i >> 1);
        printf("%2d: ", i);
        print_binary(i, 4);
        printf(" -> ");
        print_binary(gray, 4);
        printf(" (Gray: %d)\n", gray);
    }
}

void demonstrate_bit_manipulation_algorithms() {
    printf("\n=== Bit Manipulation Algorithms ===\n");
    
    // Find the only non-duplicate number
    printf("Find single number in array of duplicates:\n");
    int arr[] = {2, 3, 5, 4, 5, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int single = 0;
    for (int i = 0; i < n; i++) {
        single ^= arr[i];
    }
    printf("Single number: %d\n", single);
    
    // Find two non-duplicate numbers
    printf("\nFind two single numbers:\n");
    int arr2[] = {2, 4, 3, 6, 3, 2, 5, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Array: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    int xor_result = 0;
    for (int i = 0; i < n2; i++) {
        xor_result ^= arr2[i];
    }
    
    // Find rightmost set bit
    int rightmost_bit = xor_result & (-xor_result);
    int num1 = 0, num2 = 0;
    
    for (int i = 0; i < n2; i++) {
        if (arr2[i] & rightmost_bit) {
            num1 ^= arr2[i];
        } else {
            num2 ^= arr2[i];
        }
    }
    
    printf("Two single numbers: %d and %d\n", num1, num2);
    
    // Count number of 1s in binary representation
    printf("\nCount set bits for numbers 1-16:\n");
    for (int i = 1; i <= 16; i++) {
        printf("%2d (", i);
        print_binary(i, 4);
        printf("): %d set bits\n", count_set_bits(i));
    }
}

void demonstrate_bit_tricks() {
    printf("\n=== Bit Manipulation Tricks ===\n");
    
    // Check if two integers have opposite signs
    int pairs[][2] = {{-1, 5}, {3, 7}, {-10, -20}, {15, -8}};
    printf("Opposite signs check:\n");
    for (int i = 0; i < 4; i++) {
        int a = pairs[i][0], b = pairs[i][1];
        bool opposite = (a ^ b) < 0;
        printf("%d and %d: %s\n", a, b, opposite ? "Opposite signs" : "Same sign");
    }
    
    // Turn off rightmost set bit
    printf("\nTurn off rightmost set bit:\n");
    uint32_t test_nums[] = {12, 16, 40, 64};
    for (int i = 0; i < 4; i++) {
        uint32_t n = test_nums[i];
        uint32_t result = n & (n - 1);
        
        printf("%u (", n);
        print_binary(n, 8);
        printf(") -> %u (", result);
        print_binary(result, 8);
        printf(")\n");
    }
    
    // Isolate rightmost set bit
    printf("\nIsolate rightmost set bit:\n");
    for (int i = 0; i < 4; i++) {
        uint32_t n = test_nums[i];
        uint32_t result = n & (-n);
        
        printf("%u (", n);
        print_binary(n, 8);
        printf(") -> %u (", result);
        print_binary(result, 8);
        printf(")\n");
    }
    
    // Check if number is a power of 4
    printf("\nCheck if power of 4:\n");
    uint32_t pow4_test[] = {1, 4, 8, 16, 64, 100};
    for (int i = 0; i < 6; i++) {
        uint32_t n = pow4_test[i];
        bool is_pow4 = (n > 0) && ((n & (n - 1)) == 0) && ((n & 0x55555555) != 0);
        printf("%u: %s\n", n, is_pow4 ? "Power of 4" : "Not power of 4");
    }
}

void demonstrate_bitwise_sorting() {
    printf("\n=== Bitwise Sorting (Radix Sort) ===\n");
    
    uint32_t arr[] = {170, 45, 75, 90, 2, 802, 24, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%u ", arr[i]);
    }
    printf("\n");
    
    // Radix sort using bit manipulation
    uint32_t max_val = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }
    
    // Sort for each bit position
    for (int bit = 0; (1U << bit) <= max_val; bit++) {
        uint32_t *temp = malloc(n * sizeof(uint32_t));
        int zero_count = 0, one_count = 0;
        
        // Count zeros and ones
        for (int i = 0; i < n; i++) {
            if (CHECK_BIT(arr[i], bit)) {
                one_count++;
            } else {
                zero_count++;
            }
        }
        
        // Place elements with 0 bit first, then 1 bit
        int zero_idx = 0, one_idx = zero_count;
        for (int i = 0; i < n; i++) {
            if (CHECK_BIT(arr[i], bit)) {
                temp[one_idx++] = arr[i];
            } else {
                temp[zero_idx++] = arr[i];
            }
        }
        
        // Copy back
        for (int i = 0; i < n; i++) {
            arr[i] = temp[i];
        }
        
        printf("After sorting bit %d: ", bit);
        for (int i = 0; i < n; i++) {
            printf("%u ", arr[i]);
        }
        printf("\n");
        
        free(temp);
    }
}

// Helper function implementations
void print_binary(uint64_t n, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (int)((n >> i) & 1));
    }
}

void print_binary_formatted(uint64_t n, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (int)((n >> i) & 1));
        if (i % 8 == 0 && i > 0) printf(" ");
    }
}

int count_set_bits(uint64_t n) {
    int count = 0;
    while (n) {
        count++;
        n &= n - 1;  // Brian Kernighan's algorithm
    }
    return count;
}

int count_trailing_zeros(uint64_t n) {
    if (n == 0) return 64;
    
    int count = 0;
    while ((n & 1) == 0) {
        count++;
        n >>= 1;
    }
    return count;
}

int count_leading_zeros(uint64_t n) {
    if (n == 0) return 64;
    
    int count = 0;
    uint64_t mask = 1ULL << 63;
    
    while ((n & mask) == 0) {
        count++;
        mask >>= 1;
    }
    
    return count;
}

uint64_t reverse_bits(uint64_t n, int bits) {
    uint64_t result = 0;
    for (int i = 0; i < bits; i++) {
        result <<= 1;
        result |= (n & 1);
        n >>= 1;
    }
    return result;
}

bool is_power_of_two(uint64_t n) {
    return n > 0 && (n & (n - 1)) == 0;
}

uint64_t next_power_of_two(uint64_t n) {
    if (n == 0) return 1;
    
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    n++;
    
    return n;
}

uint64_t isolate_rightmost_set_bit(uint64_t n) {
    return n & (-n);
}

uint64_t clear_rightmost_set_bit(uint64_t n) {
    return n & (n - 1);
}

uint64_t set_rightmost_unset_bit(uint64_t n) {
    return n | (n + 1);
}

int main() {
    printf("ADVANCED BITWISE OPERATIONS AND APPLICATIONS\n");
    printf("============================================\n\n");
    
    demonstrate_basic_bitwise_operations();
    demonstrate_bit_manipulation_techniques();
    demonstrate_advanced_bit_operations();
    demonstrate_bit_hacks();
    demonstrate_bit_fields();
    demonstrate_practical_applications();
    demonstrate_bit_manipulation_algorithms();
    demonstrate_bit_tricks();
    demonstrate_bitwise_sorting();
    
    printf("\nKey Concepts Covered:\n");
    printf("- All bitwise operators and their applications\n");
    printf("- Bit manipulation techniques (set, clear, toggle, check)\n");
    printf("- Advanced bit operations (count, reverse, isolate)\n");
    printf("- Bit manipulation hacks and optimizations\n");
    printf("- Bit fields for efficient data storage\n");
    printf("- Practical applications (encryption, permissions, colors)\n");
    printf("- Bit manipulation algorithms (find unique elements)\n");
    printf("- Bitwise tricks for mathematical operations\n");
    printf("- Bitwise sorting algorithms\n");
    printf("- Performance optimizations using bit operations\n");
    
    return 0;
}

