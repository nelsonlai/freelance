/**
 * Solution 9.10: Complete Project - Student Database System
 * Week 9 - Comprehensive C Programming Project
 * 
 * Description: A complete student database management system demonstrating
 * all intermediate C programming concepts including data structures,
 * file I/O, memory management, and user interface.
 * 
 * Learning Objectives:
 * - Complete project development
 * - Integration of multiple C concepts
 * - User interface design
 * - Data persistence and file management
 * - Error handling and validation
 * - System architecture and design
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// ============================================================================
// DATA STRUCTURES AND CONSTANTS
// ============================================================================

/**
 * Structure representing a student
 */
typedef struct Student {
    int id;                     // Unique student ID
    char name[50];              // Student name
    char email[100];            // Student email
    char phone[20];             // Student phone number
    char address[100];          // Student address
    char major[50];             // Student major
    int year;                   // Academic year (1-4)
    float gpa;                  // Grade Point Average
    struct Student *next;       // Pointer for linked list
} Student;

/**
 * Structure representing the database
 */
typedef struct Database {
    Student *students;          // Linked list of students
    int student_count;          // Number of students
    int next_id;                // Next available ID
    char filename[100];         // Database filename
    bool is_modified;           // Whether database has been modified
} Database;

/**
 * Structure for search criteria
 */
typedef struct SearchCriteria {
    int id;                     // Search by ID
    char name[50];              // Search by name
    char major[50];             // Search by major
    int year;                   // Search by year
    float min_gpa;              // Minimum GPA
    float max_gpa;              // Maximum GPA
    bool use_id;                // Whether to use ID search
    bool use_name;              // Whether to use name search
    bool use_major;             // Whether to use major search
    bool use_year;              // Whether to use year search
    bool use_gpa_range;         // Whether to use GPA range search
} SearchCriteria;

/**
 * Structure for statistics
 */
typedef struct Statistics {
    int total_students;         // Total number of students
    int students_by_year[5];    // Students by year (0-4)
    float average_gpa;          // Average GPA
    float highest_gpa;          // Highest GPA
    float lowest_gpa;           // Lowest GPA
    int students_above_3_0;     // Students with GPA > 3.0
    int students_below_2_0;     // Students with GPA < 2.0
} Statistics;

// Constants
#define MAX_STUDENTS 1000
#define MAX_NAME_LENGTH 49
#define MAX_EMAIL_LENGTH 99
#define MAX_PHONE_LENGTH 19
#define MAX_ADDRESS_LENGTH 99
#define MAX_MAJOR_LENGTH 49
#define DATABASE_FILENAME "students.db"
#define BACKUP_FILENAME "students_backup.db"

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Database management
Database* create_database(const char* filename);
void destroy_database(Database* db);
bool load_database(Database* db);
bool save_database(Database* db);
bool backup_database(Database* db);

// Student management
Student* create_student(int id, const char* name, const char* email, const char* phone,
                       const char* address, const char* major, int year, float gpa);
void destroy_student(Student* student);
bool add_student(Database* db, Student* student);
bool remove_student(Database* db, int id);
Student* find_student_by_id(Database* db, int id);
Student* find_student_by_name(Database* db, const char* name);
bool update_student(Database* db, int id, const Student* updated_student);

// Search and filter operations
Student** search_students(Database* db, const SearchCriteria* criteria, int* result_count);
Student** filter_by_major(Database* db, const char* major, int* count);
Student** filter_by_year(Database* db, int year, int* count);
Student** filter_by_gpa_range(Database* db, float min_gpa, float max_gpa, int* count);

// Statistics and analysis
Statistics* calculate_statistics(Database* db);
void print_statistics(const Statistics* stats);
void print_student_list(Student** students, int count);
void print_student_details(const Student* student);

// Input validation and utilities
bool validate_student_data(const Student* student);
bool validate_email(const char* email);
bool validate_phone(const char* phone);
bool validate_gpa(float gpa);
bool validate_year(int year);
void trim_string(char* str);
void clear_input_buffer(void);
int get_choice(int min, int max);

// User interface functions
void print_main_menu(void);
void print_student_menu(void);
void print_search_menu(void);
void print_statistics_menu(void);
void handle_add_student(Database* db);
void handle_remove_student(Database* db);
void handle_update_student(Database* db);
void handle_search_students(Database* db);
void handle_view_all_students(Database* db);
void handle_view_statistics(Database* db);

// File operations
bool export_to_csv(Database* db, const char* filename);
bool import_from_csv(Database* db, const char* filename);
void print_export_menu(void);
void print_import_menu(void);

// Demonstration functions
void demonstrate_database_operations(void);
void run_interactive_demo(void);

// ============================================================================
// DATABASE MANAGEMENT IMPLEMENTATION
// ============================================================================

/**
 * Create a new database
 */
Database* create_database(const char* filename) {
    Database* db = malloc(sizeof(Database));
    if (!db) {
        printf("[ERROR] Memory allocation failed for database\n");
        return NULL;
    }
    
    db->students = NULL;
    db->student_count = 0;
    db->next_id = 1;
    db->is_modified = false;
    
    if (filename) {
        strncpy(db->filename, filename, sizeof(db->filename) - 1);
        db->filename[sizeof(db->filename) - 1] = '\0';
    } else {
        strcpy(db->filename, DATABASE_FILENAME);
    }
    
    printf("[CREATE_DATABASE] Created database '%s'\n", db->filename);
    return db;
}

/**
 * Destroy database and free all memory
 */
void destroy_database(Database* db) {
    if (!db) {
        printf("[ERROR] Cannot destroy NULL database\n");
        return;
    }
    
    Student* current = db->students;
    while (current) {
        Student* next = current->next;
        destroy_student(current);
        current = next;
    }
    
    free(db);
    printf("[DESTROY_DATABASE] Destroyed database\n");
}

/**
 * Load database from file
 */
bool load_database(Database* db) {
    if (!db) {
        printf("[ERROR] Cannot load NULL database\n");
        return false;
    }
    
    FILE* file = fopen(db->filename, "r");
    if (!file) {
        printf("[INFO] Database file '%s' not found, creating new database\n", db->filename);
        return true; // Not an error, just no existing data
    }
    
    char line[500];
    int loaded_count = 0;
    
    while (fgets(line, sizeof(line), file)) {
        // Parse line: ID,Name,Email,Phone,Address,Major,Year,GPA
        int id, year;
        char name[50], email[100], phone[20], address[100], major[50];
        float gpa;
        
        int parsed = sscanf(line, "%d,%49[^,],%99[^,],%19[^,],%99[^,],%49[^,],%d,%f",
                           &id, name, email, phone, address, major, &year, &gpa);
        
        if (parsed == 8) {
            Student* student = create_student(id, name, email, phone, address, major, year, gpa);
            if (student) {
                add_student(db, student);
                loaded_count++;
            }
        }
    }
    
    fclose(file);
    db->is_modified = false;
    
    printf("[LOAD_DATABASE] Loaded %d students from '%s'\n", loaded_count, db->filename);
    return true;
}

/**
 * Save database to file
 */
bool save_database(Database* db) {
    if (!db) {
        printf("[ERROR] Cannot save NULL database\n");
        return false;
    }
    
    FILE* file = fopen(db->filename, "w");
    if (!file) {
        printf("[ERROR] Cannot open file '%s' for writing\n", db->filename);
        return false;
    }
    
    Student* current = db->students;
    int saved_count = 0;
    
    while (current) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%.2f\n",
                current->id, current->name, current->email, current->phone,
                current->address, current->major, current->year, current->gpa);
        current = current->next;
        saved_count++;
    }
    
    fclose(file);
    db->is_modified = false;
    
    printf("[SAVE_DATABASE] Saved %d students to '%s'\n", saved_count, db->filename);
    return true;
}

/**
 * Create backup of database
 */
bool backup_database(Database* db) {
    if (!db) {
        printf("[ERROR] Cannot backup NULL database\n");
        return false;
    }
    
    char backup_filename[150];
    snprintf(backup_filename, sizeof(backup_filename), "%s_%lu.db", 
             db->filename, (unsigned long)time(NULL));
    
    FILE* source = fopen(db->filename, "r");
    if (!source) {
        printf("[ERROR] Cannot open source file for backup\n");
        return false;
    }
    
    FILE* backup = fopen(backup_filename, "w");
    if (!backup) {
        fclose(source);
        printf("[ERROR] Cannot create backup file\n");
        return false;
    }
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), source)) {
        fputs(buffer, backup);
    }
    
    fclose(source);
    fclose(backup);
    
    printf("[BACKUP_DATABASE] Created backup: '%s'\n", backup_filename);
    return true;
}

// ============================================================================
// STUDENT MANAGEMENT IMPLEMENTATION
// ============================================================================

/**
 * Create a new student
 */
Student* create_student(int id, const char* name, const char* email, const char* phone,
                       const char* address, const char* major, int year, float gpa) {
    if (!name || !email || !phone || !address || !major) {
        printf("[ERROR] Invalid parameters for student creation\n");
        return NULL;
    }
    
    Student* student = malloc(sizeof(Student));
    if (!student) {
        printf("[ERROR] Memory allocation failed for student\n");
        return NULL;
    }
    
    student->id = id;
    strncpy(student->name, name, sizeof(student->name) - 1);
    student->name[sizeof(student->name) - 1] = '\0';
    
    strncpy(student->email, email, sizeof(student->email) - 1);
    student->email[sizeof(student->email) - 1] = '\0';
    
    strncpy(student->phone, phone, sizeof(student->phone) - 1);
    student->phone[sizeof(student->phone) - 1] = '\0';
    
    strncpy(student->address, address, sizeof(student->address) - 1);
    student->address[sizeof(student->address) - 1] = '\0';
    
    strncpy(student->major, major, sizeof(student->major) - 1);
    student->major[sizeof(student->major) - 1] = '\0';
    
    student->year = year;
    student->gpa = gpa;
    student->next = NULL;
    
    printf("[CREATE_STUDENT] Created student: ID=%d, Name=%s\n", id, name);
    return student;
}

/**
 * Destroy student and free memory
 */
void destroy_student(Student* student) {
    if (student) {
        free(student);
    }
}

/**
 * Add student to database
 */
bool add_student(Database* db, Student* student) {
    if (!db || !student) {
        printf("[ERROR] Invalid parameters for adding student\n");
        return false;
    }
    
    if (db->student_count >= MAX_STUDENTS) {
        printf("[ERROR] Database is full (max %d students)\n", MAX_STUDENTS);
        return false;
    }
    
    // Check for duplicate ID
    if (find_student_by_id(db, student->id)) {
        printf("[ERROR] Student with ID %d already exists\n", student->id);
        return false;
    }
    
    // Add to beginning of list
    student->next = db->students;
    db->students = student;
    db->student_count++;
    
    if (student->id >= db->next_id) {
        db->next_id = student->id + 1;
    }
    
    db->is_modified = true;
    
    printf("[ADD_STUDENT] Added student %d to database (total: %d)\n", 
           student->id, db->student_count);
    return true;
}

/**
 * Remove student from database
 */
bool remove_student(Database* db, int id) {
    if (!db) {
        printf("[ERROR] Cannot remove from NULL database\n");
        return false;
    }
    
    Student* current = db->students;
    Student* prev = NULL;
    
    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                db->students = current->next;
            }
            
            destroy_student(current);
            db->student_count--;
            db->is_modified = true;
            
            printf("[REMOVE_STUDENT] Removed student %d from database (total: %d)\n", 
                   id, db->student_count);
            return true;
        }
        
        prev = current;
        current = current->next;
    }
    
    printf("[REMOVE_STUDENT] Student with ID %d not found\n", id);
    return false;
}

/**
 * Find student by ID
 */
Student* find_student_by_id(Database* db, int id) {
    if (!db) {
        return NULL;
    }
    
    Student* current = db->students;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Find student by name
 */
Student* find_student_by_name(Database* db, const char* name) {
    if (!db || !name) {
        return NULL;
    }
    
    Student* current = db->students;
    while (current) {
        if (strcasecmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

// ============================================================================
// SEARCH AND FILTER OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Search students based on criteria
 */
Student** search_students(Database* db, const SearchCriteria* criteria, int* result_count) {
    if (!db || !criteria || !result_count) {
        printf("[ERROR] Invalid parameters for student search\n");
        return NULL;
    }
    
    Student** results = malloc(db->student_count * sizeof(Student*));
    if (!results) {
        printf("[ERROR] Memory allocation failed for search results\n");
        return NULL;
    }
    
    *result_count = 0;
    Student* current = db->students;
    
    while (current) {
        bool matches = true;
        
        if (criteria->use_id && current->id != criteria->id) {
            matches = false;
        }
        
        if (criteria->use_name && strcasecmp(current->name, criteria->name) != 0) {
            matches = false;
        }
        
        if (criteria->use_major && strcasecmp(current->major, criteria->major) != 0) {
            matches = false;
        }
        
        if (criteria->use_year && current->year != criteria->year) {
            matches = false;
        }
        
        if (criteria->use_gpa_range && 
            (current->gpa < criteria->min_gpa || current->gpa > criteria->max_gpa)) {
            matches = false;
        }
        
        if (matches) {
            results[*result_count] = current;
            (*result_count)++;
        }
        
        current = current->next;
    }
    
    printf("[SEARCH_STUDENTS] Found %d students matching criteria\n", *result_count);
    return results;
}

// ============================================================================
// STATISTICS AND ANALYSIS IMPLEMENTATION
// ============================================================================

/**
 * Calculate database statistics
 */
Statistics* calculate_statistics(Database* db) {
    if (!db) {
        printf("[ERROR] Cannot calculate statistics for NULL database\n");
        return NULL;
    }
    
    Statistics* stats = malloc(sizeof(Statistics));
    if (!stats) {
        printf("[ERROR] Memory allocation failed for statistics\n");
        return NULL;
    }
    
    stats->total_students = db->student_count;
    stats->average_gpa = 0.0;
    stats->highest_gpa = 0.0;
    stats->lowest_gpa = 4.0;
    stats->students_above_3_0 = 0;
    stats->students_below_2_0 = 0;
    
    // Initialize year counts
    for (int i = 0; i < 5; i++) {
        stats->students_by_year[i] = 0;
    }
    
    if (db->student_count == 0) {
        stats->lowest_gpa = 0.0;
        return stats;
    }
    
    Student* current = db->students;
    float total_gpa = 0.0;
    
    while (current) {
        total_gpa += current->gpa;
        
        if (current->gpa > stats->highest_gpa) {
            stats->highest_gpa = current->gpa;
        }
        
        if (current->gpa < stats->lowest_gpa) {
            stats->lowest_gpa = current->gpa;
        }
        
        if (current->gpa > 3.0) {
            stats->students_above_3_0++;
        }
        
        if (current->gpa < 2.0) {
            stats->students_below_2_0++;
        }
        
        if (current->year >= 1 && current->year <= 4) {
            stats->students_by_year[current->year]++;
        }
        
        current = current->next;
    }
    
    stats->average_gpa = total_gpa / db->student_count;
    
    printf("[CALCULATE_STATISTICS] Calculated statistics for %d students\n", db->student_count);
    return stats;
}

/**
 * Print statistics
 */
void print_statistics(const Statistics* stats) {
    if (!stats) {
        printf("[ERROR] Cannot print NULL statistics\n");
        return;
    }
    
    printf("\n=== DATABASE STATISTICS ===\n");
    printf("Total Students: %d\n", stats->total_students);
    printf("Average GPA: %.2f\n", stats->average_gpa);
    printf("Highest GPA: %.2f\n", stats->highest_gpa);
    printf("Lowest GPA: %.2f\n", stats->lowest_gpa);
    printf("Students with GPA > 3.0: %d\n", stats->students_above_3_0);
    printf("Students with GPA < 2.0: %d\n", stats->students_below_2_0);
    
    printf("\nStudents by Year:\n");
    for (int i = 1; i <= 4; i++) {
        printf("  Year %d: %d students\n", i, stats->students_by_year[i]);
    }
}

/**
 * Print student list
 */
void print_student_list(Student** students, int count) {
    if (!students || count <= 0) {
        printf("No students to display\n");
        return;
    }
    
    printf("\n=== STUDENT LIST (%d students) ===\n", count);
    printf("%-5s %-20s %-30s %-15s %-10s %-8s\n", 
           "ID", "Name", "Email", "Phone", "Major", "GPA");
    printf("%-5s %-20s %-30s %-15s %-10s %-8s\n", 
           "---", "----", "-----", "-----", "-----", "---");
    
    for (int i = 0; i < count; i++) {
        Student* student = students[i];
        printf("%-5d %-20s %-30s %-15s %-10s %-8.2f\n",
               student->id, student->name, student->email, 
               student->phone, student->major, student->gpa);
    }
}

/**
 * Print detailed student information
 */
void print_student_details(const Student* student) {
    if (!student) {
        printf("[ERROR] Cannot print NULL student\n");
        return;
    }
    
    printf("\n=== STUDENT DETAILS ===\n");
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Email: %s\n", student->email);
    printf("Phone: %s\n", student->phone);
    printf("Address: %s\n", student->address);
    printf("Major: %s\n", student->major);
    printf("Year: %d\n", student->year);
    printf("GPA: %.2f\n", student->gpa);
}

// ============================================================================
// INPUT VALIDATION AND UTILITIES IMPLEMENTATION
// ============================================================================

/**
 * Validate student data
 */
bool validate_student_data(const Student* student) {
    if (!student) {
        printf("[ERROR] Cannot validate NULL student\n");
        return false;
    }
    
    if (student->id <= 0) {
        printf("[VALIDATION] Invalid student ID: %d\n", student->id);
        return false;
    }
    
    if (strlen(student->name) == 0) {
        printf("[VALIDATION] Student name cannot be empty\n");
        return false;
    }
    
    if (!validate_email(student->email)) {
        printf("[VALIDATION] Invalid email: %s\n", student->email);
        return false;
    }
    
    if (!validate_phone(student->phone)) {
        printf("[VALIDATION] Invalid phone: %s\n", student->phone);
        return false;
    }
    
    if (!validate_gpa(student->gpa)) {
        printf("[VALIDATION] Invalid GPA: %.2f\n", student->gpa);
        return false;
    }
    
    if (!validate_year(student->year)) {
        printf("[VALIDATION] Invalid year: %d\n", student->year);
        return false;
    }
    
    return true;
}

/**
 * Validate email format
 */
bool validate_email(const char* email) {
    if (!email || strlen(email) == 0) {
        return false;
    }
    
    bool has_at = false;
    bool has_dot_after_at = false;
    
    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') {
            has_at = true;
        } else if (email[i] == '.' && has_at) {
            has_dot_after_at = true;
        }
    }
    
    return has_at && has_dot_after_at;
}

/**
 * Validate phone number
 */
bool validate_phone(const char* phone) {
    if (!phone || strlen(phone) == 0) {
        return false;
    }
    
    // Simple validation: should contain only digits, spaces, hyphens, and parentheses
    for (int i = 0; phone[i]; i++) {
        if (!isdigit(phone[i]) && phone[i] != ' ' && phone[i] != '-' && phone[i] != '(' && phone[i] != ')') {
            return false;
        }
    }
    
    return true;
}

/**
 * Validate GPA
 */
bool validate_gpa(float gpa) {
    return gpa >= 0.0 && gpa <= 4.0;
}

/**
 * Validate academic year
 */
bool validate_year(int year) {
    return year >= 1 && year <= 4;
}

/**
 * Trim whitespace from string
 */
void trim_string(char* str) {
    if (!str) return;
    
    // Trim leading whitespace
    char* start = str;
    while (isspace(*start)) start++;
    
    // Trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    // Move trimmed string to beginning
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';
}

/**
 * Clear input buffer
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Get user choice within range
 */
int get_choice(int min, int max) {
    int choice;
    while (1) {
        printf("Enter your choice (%d-%d): ", min, max);
        if (scanf("%d", &choice) == 1) {
            if (choice >= min && choice <= max) {
                clear_input_buffer();
                return choice;
            }
        }
        printf("Invalid choice. Please try again.\n");
        clear_input_buffer();
    }
}

// ============================================================================
// USER INTERFACE IMPLEMENTATION
// ============================================================================

/**
 * Print main menu
 */
void print_main_menu(void) {
    printf("\n=== STUDENT DATABASE MANAGEMENT SYSTEM ===\n");
    printf("1. Add Student\n");
    printf("2. Remove Student\n");
    printf("3. Update Student\n");
    printf("4. Search Students\n");
    printf("5. View All Students\n");
    printf("6. View Statistics\n");
    printf("7. Export Data\n");
    printf("8. Import Data\n");
    printf("9. Backup Database\n");
    printf("0. Exit\n");
}

/**
 * Handle adding a student
 */
void handle_add_student(Database* db) {
    printf("\n=== ADD NEW STUDENT ===\n");
    
    char name[50], email[100], phone[20], address[100], major[50];
    int year;
    float gpa;
    
    printf("Enter student name: ");
    if (fgets(name, sizeof(name), stdin)) {
        trim_string(name);
    }
    
    printf("Enter email: ");
    if (fgets(email, sizeof(email), stdin)) {
        trim_string(email);
    }
    
    printf("Enter phone: ");
    if (fgets(phone, sizeof(phone), stdin)) {
        trim_string(phone);
    }
    
    printf("Enter address: ");
    if (fgets(address, sizeof(address), stdin)) {
        trim_string(address);
    }
    
    printf("Enter major: ");
    if (fgets(major, sizeof(major), stdin)) {
        trim_string(major);
    }
    
    printf("Enter academic year (1-4): ");
    scanf("%d", &year);
    clear_input_buffer();
    
    printf("Enter GPA (0.0-4.0): ");
    scanf("%f", &gpa);
    clear_input_buffer();
    
    Student* student = create_student(db->next_id, name, email, phone, address, major, year, gpa);
    if (student && validate_student_data(student)) {
        if (add_student(db, student)) {
            printf("Student added successfully with ID: %d\n", student->id);
        } else {
            destroy_student(student);
        }
    } else {
        printf("Failed to add student. Please check your input.\n");
        if (student) destroy_student(student);
    }
}

/**
 * Handle removing a student
 */
void handle_remove_student(Database* db) {
    printf("\n=== REMOVE STUDENT ===\n");
    
    int id;
    printf("Enter student ID to remove: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    Student* student = find_student_by_id(db, id);
    if (student) {
        print_student_details(student);
        printf("\nAre you sure you want to remove this student? (y/n): ");
        char confirm;
        scanf("%c", &confirm);
        clear_input_buffer();
        
        if (confirm == 'y' || confirm == 'Y') {
            if (remove_student(db, id)) {
                printf("Student removed successfully.\n");
            }
        } else {
            printf("Operation cancelled.\n");
        }
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

/**
 * Handle searching students
 */
void handle_search_students(Database* db) {
    printf("\n=== SEARCH STUDENTS ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Major\n");
    printf("4. Search by Year\n");
    printf("5. Search by GPA Range\n");
    printf("0. Back to Main Menu\n");
    
    int choice = get_choice(0, 5);
    
    SearchCriteria criteria = {0};
    int result_count = 0;
    Student** results = NULL;
    
    switch (choice) {
        case 1:
            printf("Enter student ID: ");
            scanf("%d", &criteria.id);
            clear_input_buffer();
            criteria.use_id = true;
            break;
            
        case 2:
            printf("Enter student name: ");
            char name[50];
            if (fgets(name, sizeof(name), stdin)) {
                trim_string(name);
                strcpy(criteria.name, name);
            }
            criteria.use_name = true;
            break;
            
        case 3:
            printf("Enter major: ");
            char major[50];
            if (fgets(major, sizeof(major), stdin)) {
                trim_string(major);
                strcpy(criteria.major, major);
            }
            criteria.use_major = true;
            break;
            
        case 4:
            printf("Enter academic year (1-4): ");
            scanf("%d", &criteria.year);
            clear_input_buffer();
            criteria.use_year = true;
            break;
            
        case 5:
            printf("Enter minimum GPA: ");
            scanf("%f", &criteria.min_gpa);
            printf("Enter maximum GPA: ");
            scanf("%f", &criteria.max_gpa);
            clear_input_buffer();
            criteria.use_gpa_range = true;
            break;
            
        case 0:
            return;
    }
    
    results = search_students(db, &criteria, &result_count);
    if (results) {
        print_student_list(results, result_count);
        free(results);
    }
}

/**
 * Handle viewing all students
 */
void handle_view_all_students(Database* db) {
    printf("\n=== ALL STUDENTS ===\n");
    
    if (db->student_count == 0) {
        printf("No students in database.\n");
        return;
    }
    
    Student** all_students = malloc(db->student_count * sizeof(Student*));
    if (!all_students) {
        printf("[ERROR] Memory allocation failed\n");
        return;
    }
    
    Student* current = db->students;
    int index = 0;
    while (current) {
        all_students[index++] = current;
        current = current->next;
    }
    
    print_student_list(all_students, db->student_count);
    free(all_students);
}

/**
 * Handle viewing statistics
 */
void handle_view_statistics(Database* db) {
    printf("\n=== DATABASE STATISTICS ===\n");
    
    Statistics* stats = calculate_statistics(db);
    if (stats) {
        print_statistics(stats);
        free(stats);
    }
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate database operations
 */
void demonstrate_database_operations(void) {
    printf("\n=== DATABASE OPERATIONS DEMONSTRATION ===\n");
    
    Database* db = create_database("demo.db");
    if (!db) {
        printf("Failed to create database\n");
        return;
    }
    
    // Add some sample students
    Student* student1 = create_student(1, "John Doe", "john@email.com", "123-456-7890", 
                                      "123 Main St", "Computer Science", 3, 3.5);
    Student* student2 = create_student(2, "Jane Smith", "jane@email.com", "098-765-4321", 
                                      "456 Oak Ave", "Mathematics", 2, 3.8);
    Student* student3 = create_student(3, "Bob Johnson", "bob@email.com", "555-123-4567", 
                                      "789 Pine Rd", "Physics", 4, 2.9);
    
    if (student1) add_student(db, student1);
    if (student2) add_student(db, student2);
    if (student3) add_student(db, student3);
    
    // Display all students
    handle_view_all_students(db);
    
    // Show statistics
    handle_view_statistics(db);
    
    // Save database
    save_database(db);
    
    destroy_database(db);
}

/**
 * Run interactive demo
 */
void run_interactive_demo(void) {
    printf("=== INTERACTIVE STUDENT DATABASE DEMO ===\n");
    
    Database* db = create_database(DATABASE_FILENAME);
    if (!db) {
        printf("Failed to create database\n");
        return;
    }
    
    // Load existing data
    load_database(db);
    
    int choice;
    do {
        print_main_menu();
        choice = get_choice(0, 9);
        
        switch (choice) {
            case 1:
                handle_add_student(db);
                break;
            case 2:
                handle_remove_student(db);
                break;
            case 3:
                printf("Update student functionality not implemented in this demo\n");
                break;
            case 4:
                handle_search_students(db);
                break;
            case 5:
                handle_view_all_students(db);
                break;
            case 6:
                handle_view_statistics(db);
                break;
            case 7:
                printf("Export functionality not implemented in this demo\n");
                break;
            case 8:
                printf("Import functionality not implemented in this demo\n");
                break;
            case 9:
                backup_database(db);
                break;
            case 0:
                printf("Exiting...\n");
                break;
        }
        
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar();
        }
        
    } while (choice != 0);
    
    // Save database before exiting
    if (db->is_modified) {
        printf("Saving database...\n");
        save_database(db);
    }
    
    destroy_database(db);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("STUDENT DATABASE MANAGEMENT SYSTEM\n");
    printf("==================================\n");
    
    printf("Choose demo mode:\n");
    printf("1. Automated demonstration\n");
    printf("2. Interactive demonstration\n");
    printf("Enter choice (1-2): ");
    
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch (choice) {
        case 1:
            demonstrate_database_operations();
            break;
        case 2:
            run_interactive_demo();
            break;
        default:
            printf("Invalid choice. Running automated demo.\n");
            demonstrate_database_operations();
            break;
    }
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Complete project development and architecture\n");
    printf("2. Integration of multiple C programming concepts\n");
    printf("3. User interface design and interaction\n");
    printf("4. Data persistence and file management\n");
    printf("5. Error handling and input validation\n");
    printf("6. Linked list data structure implementation\n");
    printf("7. Search and filter operations\n");
    printf("8. Statistics calculation and analysis\n");
    printf("9. Memory management and cleanup\n");
    printf("10. System design and modular programming\n");
    
    return 0;
}




