#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Demonstrates C++ source file organization, linkage, and storage duration
int main() {
    std::cout << "C++ Source Files and Programs Demonstration" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // 1. Linkage demonstration
    std::cout << "\n1. LINKAGE DEMONSTRATION:" << std::endl;
    
    // External linkage - accessible from other translation units
    extern int external_var;  // Declaration
    std::cout << "External variable (declared): " << external_var << std::endl;
    
    // Internal linkage - accessible only within this translation unit
    static int internal_var = 42;
    std::cout << "Internal variable: " << internal_var << std::endl;
    
    // No linkage - local to this block
    {
        int no_linkage_var = 100;
        std::cout << "No linkage variable: " << no_linkage_var << std::endl;
    }
    // no_linkage_var is not accessible here
    
    // 2. Storage duration demonstration
    std::cout << "\n2. STORAGE DURATION DEMONSTRATION:" << std::endl;
    
    // Static storage duration
    static int static_counter = 0;
    static_counter++;
    std::cout << "Static counter: " << static_counter << std::endl;
    
    // Automatic storage duration
    int automatic_var = 50;
    std::cout << "Automatic variable: " << automatic_var << std::endl;
    
    // Dynamic storage duration
    std::unique_ptr<int> dynamic_var = std::make_unique<int>(75);
    std::cout << "Dynamic variable: " << *dynamic_var << std::endl;
    
    // 3. Function with external linkage
    std::cout << "\n3. FUNCTION WITH EXTERNAL LINKAGE:" << std::endl;
    
    auto external_function = [](int x) -> int {
        return x * 2;
    };
    
    std::cout << "external_function(5) = " << external_function(5) << std::endl;
    
    // 4. Function with internal linkage
    std::cout << "\n4. FUNCTION WITH INTERNAL LINKAGE:" << std::endl;
    
    static auto internal_function = [](int x) -> int {
        return x * 3;
    };
    
    std::cout << "internal_function(5) = " << internal_function(5) << std::endl;
    
    // 5. Class with different linkage
    std::cout << "\n5. CLASS WITH DIFFERENT LINKAGE:" << std::endl;
    
    // Class with external linkage (default)
    class ExternalClass {
    public:
        static int get_value() { return 200; }
    };
    
    // Class with internal linkage
    static class InternalClass {
    public:
        static int get_value() { return 300; }
    } internal_class;
    
    std::cout << "ExternalClass::get_value() = " << ExternalClass::get_value() << std::endl;
    std::cout << "InternalClass::get_value() = " << internal_class.get_value() << std::endl;
    
    // 6. Namespace with linkage
    std::cout << "\n6. NAMESPACE WITH LINKAGE:" << std::endl;
    
    namespace linkage_demo {
        // External linkage
        int external_var = 400;
        
        // Internal linkage
        static int internal_var = 500;
        
        // External linkage function
        int external_func() { return 600; }
        
        // Internal linkage function
        static int internal_func() { return 700; }
        
        // Class with external linkage
        class ExternalClass {
        public:
            static int get_value() { return 800; }
        };
        
        // Class with internal linkage
        static class InternalClass {
        public:
            static int get_value() { return 900; }
        } internal_class;
    }
    
    std::cout << "linkage_demo::external_var = " << linkage_demo::external_var << std::endl;
    std::cout << "linkage_demo::internal_var = " << linkage_demo::internal_var << std::endl;
    std::cout << "linkage_demo::external_func() = " << linkage_demo::external_func() << std::endl;
    std::cout << "linkage_demo::internal_func() = " << linkage_demo::internal_func() << std::endl;
    std::cout << "linkage_demo::ExternalClass::get_value() = " << linkage_demo::ExternalClass::get_value() << std::endl;
    std::cout << "linkage_demo::InternalClass::get_value() = " << linkage_demo::internal_class.get_value() << std::endl;
    
    // 7. Template with linkage
    std::cout << "\n7. TEMPLATE WITH LINKAGE:" << std::endl;
    
    template<typename T>
    T template_function(T value) {
        return value * 2;
    }
    
    // Template specialization with internal linkage
    template<>
    static int template_function<int>(int value) {
        return value * 3;
    }
    
    std::cout << "template_function(5) = " << template_function(5) << std::endl;
    std::cout << "template_function(3.14) = " << template_function(3.14) << std::endl;
    std::cout << "template_function('A') = " << template_function('A') << std::endl;
    
    // 8. Const variables and linkage
    std::cout << "\n8. CONST VARIABLES AND LINKAGE:" << std::endl;
    
    // External linkage const
    const int external_const = 1000;
    
    // Internal linkage const
    static const int internal_const = 2000;
    
    // No linkage const
    const int no_linkage_const = 3000;
    
    std::cout << "external_const = " << external_const << std::endl;
    std::cout << "internal_const = " << internal_const << std::endl;
    std::cout << "no_linkage_const = " << no_linkage_const << std::endl;
    
    // 9. Function pointers and linkage
    std::cout << "\n9. FUNCTION POINTERS AND LINKAGE:" << std::endl;
    
    // Function pointer with external linkage
    int (*external_func_ptr)(int) = [](int x) { return x * 4; };
    
    // Function pointer with internal linkage
    static int (*internal_func_ptr)(int) = [](int x) { return x * 5; };
    
    std::cout << "external_func_ptr(5) = " << external_func_ptr(5) << std::endl;
    std::cout << "internal_func_ptr(5) = " << internal_func_ptr(5) << std::endl;
    
    // 10. Static member variables and linkage
    std::cout << "\n10. STATIC MEMBER VARIABLES AND LINKAGE:" << std::endl;
    
    class StaticMemberClass {
    public:
        static int static_member;
        static const int static_const_member = 42;
        
        static int get_static_member() {
            return static_member;
        }
        
        static void set_static_member(int value) {
            static_member = value;
        }
    };
    
    // Define static member (external linkage)
    int StaticMemberClass::static_member = 100;
    
    std::cout << "StaticMemberClass::static_member = " << StaticMemberClass::static_member << std::endl;
    std::cout << "StaticMemberClass::static_const_member = " << StaticMemberClass::static_const_member << std::endl;
    
    StaticMemberClass::set_static_member(200);
    std::cout << "After setting, static_member = " << StaticMemberClass::get_static_member() << std::endl;
    
    // 11. Anonymous namespace (internal linkage)
    std::cout << "\n11. ANONYMOUS NAMESPACE (INTERNAL LINKAGE):" << std::endl;
    
    namespace {
        int anonymous_var = 400;
        
        int anonymous_function() {
            return 500;
        }
        
        class AnonymousClass {
        public:
            static int get_value() { return 600; }
        };
    }
    
    std::cout << "anonymous_var = " << anonymous_var << std::endl;
    std::cout << "anonymous_function() = " << anonymous_function() << std::endl;
    std::cout << "AnonymousClass::get_value() = " << AnonymousClass::get_value() << std::endl;
    
    // 12. Linkage with arrays
    std::cout << "\n12. LINKAGE WITH ARRAYS:" << std::endl;
    
    // External linkage array
    int external_array[] = {1, 2, 3, 4, 5};
    
    // Internal linkage array
    static int internal_array[] = {6, 7, 8, 9, 10};
    
    // No linkage array
    int no_linkage_array[] = {11, 12, 13, 14, 15};
    
    std::cout << "external_array[2] = " << external_array[2] << std::endl;
    std::cout << "internal_array[2] = " << internal_array[2] << std::endl;
    std::cout << "no_linkage_array[2] = " << no_linkage_array[2] << std::endl;
    
    // 13. Linkage with strings
    std::cout << "\n13. LINKAGE WITH STRINGS:" << std::endl;
    
    // External linkage string
    const char* external_string = "External string";
    
    // Internal linkage string
    static const char* internal_string = "Internal string";
    
    // No linkage string
    const char* no_linkage_string = "No linkage string";
    
    std::cout << "external_string = " << external_string << std::endl;
    std::cout << "internal_string = " << internal_string << std::endl;
    std::cout << "no_linkage_string = " << no_linkage_string << std::endl;
    
    // 14. Linkage with complex types
    std::cout << "\n14. LINKAGE WITH COMPLEX TYPES:" << std::endl;
    
    // External linkage vector
    std::vector<int> external_vector = {1, 2, 3, 4, 5};
    
    // Internal linkage vector
    static std::vector<int> internal_vector = {6, 7, 8, 9, 10};
    
    std::cout << "external_vector size: " << external_vector.size() << std::endl;
    std::cout << "internal_vector size: " << internal_vector.size() << std::endl;
    
    // 15. Linkage with function objects
    std::cout << "\n15. LINKAGE WITH FUNCTION OBJECTS:" << std::endl;
    
    // External linkage function object
    auto external_func_obj = [](int x) { return x * 6; };
    
    // Internal linkage function object
    static auto internal_func_obj = [](int x) { return x * 7; };
    
    std::cout << "external_func_obj(5) = " << external_func_obj(5) << std::endl;
    std::cout << "internal_func_obj(5) = " << internal_func_obj(5) << std::endl;
    
    // 16. Linkage with enums
    std::cout << "\n16. LINKAGE WITH ENUMS:" << std::endl;
    
    // External linkage enum
    enum ExternalEnum { EXTERNAL_A, EXTERNAL_B, EXTERNAL_C };
    
    // Internal linkage enum
    static enum InternalEnum { INTERNAL_A, INTERNAL_B, INTERNAL_C } internal_enum;
    
    // External linkage enum class
    enum class ExternalEnumClass { A, B, C };
    
    // Internal linkage enum class
    static enum class InternalEnumClass { A, B, C } internal_enum_class;
    
    std::cout << "EXTERNAL_A = " << EXTERNAL_A << std::endl;
    std::cout << "INTERNAL_A = " << INTERNAL_A << std::endl;
    std::cout << "ExternalEnumClass::A = " << static_cast<int>(ExternalEnumClass::A) << std::endl;
    std::cout << "InternalEnumClass::A = " << static_cast<int>(internal_enum_class.A) << std::endl;
    
    // 17. Linkage with unions
    std::cout << "\n17. LINKAGE WITH UNIONS:" << std::endl;
    
    // External linkage union
    union ExternalUnion {
        int int_val;
        double double_val;
        char char_val;
    };
    
    // Internal linkage union
    static union InternalUnion {
        int int_val;
        double double_val;
        char char_val;
    } internal_union;
    
    ExternalUnion external_union;
    external_union.int_val = 42;
    std::cout << "external_union.int_val = " << external_union.int_val << std::endl;
    
    internal_union.int_val = 84;
    std::cout << "internal_union.int_val = " << internal_union.int_val << std::endl;
    
    // 18. Linkage with structures
    std::cout << "\n18. LINKAGE WITH STRUCTURES:" << std::endl;
    
    // External linkage struct
    struct ExternalStruct {
        int value;
        std::string name;
        
        ExternalStruct(int v = 0, const std::string& n = "") : value(v), name(n) {}
        
        void display() const {
            std::cout << "ExternalStruct: value = " << value << ", name = " << name << std::endl;
        }
    };
    
    // Internal linkage struct
    static struct InternalStruct {
        int value;
        std::string name;
        
        InternalStruct(int v = 0, const std::string& n = "") : value(v), name(n) {}
        
        void display() const {
            std::cout << "InternalStruct: value = " << value << ", name = " << name << std::endl;
        }
    } internal_struct;
    
    ExternalStruct external_struct(100, "External");
    external_struct.display();
    
    internal_struct = InternalStruct(200, "Internal");
    internal_struct.display();
    
    // 19. Linkage with global variables
    std::cout << "\n19. LINKAGE WITH GLOBAL VARIABLES:" << std::endl;
    
    // Global variable with external linkage
    int global_external = 300;
    
    // Global variable with internal linkage
    static int global_internal = 400;
    
    // Global variable with no linkage (const)
    const int global_const = 500;
    
    std::cout << "global_external = " << global_external << std::endl;
    std::cout << "global_internal = " << global_internal << std::endl;
    std::cout << "global_const = " << global_const << std::endl;
    
    // 20. Linkage with function templates
    std::cout << "\n20. LINKAGE WITH FUNCTION TEMPLATES:" << std::endl;
    
    // Function template with external linkage
    template<typename T>
    T external_template_function(T value) {
        return value * 8;
    }
    
    // Function template with internal linkage
    template<typename T>
    static T internal_template_function(T value) {
        return value * 9;
    }
    
    std::cout << "external_template_function(5) = " << external_template_function(5) << std::endl;
    std::cout << "internal_template_function(5) = " << internal_template_function(5) << std::endl;
    
    std::cout << "\nSource files demonstration completed!" << std::endl;
    return 0;
}

// External variable definition (external linkage)
int external_var = 100;
