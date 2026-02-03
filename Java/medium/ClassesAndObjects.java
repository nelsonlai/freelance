/**
 * MEDIUM LEVEL - Lesson 1: Classes and Objects
 * 
 * This lesson covers:
 * - Class definition
 * - Object creation
 * - Instance variables (fields)
 * - Instance methods
 * - Constructors
 * - this keyword
 * - Access modifiers (public, private, protected, package-private)
 */

// ========== CLASS DEFINITION ==========

class Student {
    // Instance variables (fields)
    private String name;
    private int age;
    private String studentId;
    
    // ========== CONSTRUCTORS ==========
    
    // Default constructor (no parameters)
    public Student() {
        this.name = "Unknown";
        this.age = 0;
        this.studentId = "N/A";
    }
    
    // Parameterized constructor
    public Student(String name, int age, String studentId) {
        this.name = name;
        this.age = age;
        this.studentId = studentId;
    }
    
    // Constructor with partial parameters
    public Student(String name, String studentId) {
        this.name = name;
        this.studentId = studentId;
        this.age = 18;  // Default age
    }
    
    // ========== GETTER METHODS (Accessors) ==========
    
    public String getName() {
        return name;
    }
    
    public int getAge() {
        return age;
    }
    
    public String getStudentId() {
        return studentId;
    }
    
    // ========== SETTER METHODS (Mutators) ==========
    
    public void setName(String name) {
        this.name = name;
    }
    
    public void setAge(int age) {
        if (age > 0) {  // Validation
            this.age = age;
        }
    }
    
    public void setStudentId(String studentId) {
        this.studentId = studentId;
    }
    
    // ========== INSTANCE METHODS ==========
    
    public void displayInfo() {
        System.out.println("Student ID: " + studentId);
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }
    
    public boolean isAdult() {
        return age >= 18;
    }
    
    public String getInfo() {
        return "Student[" + studentId + ": " + name + ", " + age + " years old]";
    }
}

// ========== MAIN CLASS TO DEMONSTRATE USAGE ==========

public class ClassesAndObjects {
    public static void main(String[] args) {
        System.out.println("=== Creating Objects ===");
        
        // Creating objects using different constructors
        Student student1 = new Student();
        Student student2 = new Student("Alice", 20, "S001");
        Student student3 = new Student("Bob", "S002");
        
        System.out.println("\n=== Student 1 (Default Constructor) ===");
        student1.displayInfo();
        
        System.out.println("\n=== Student 2 (Full Constructor) ===");
        student2.displayInfo();
        
        System.out.println("\n=== Student 3 (Partial Constructor) ===");
        student3.displayInfo();
        
        System.out.println("\n=== Using Getter Methods ===");
        System.out.println("Student 2 Name: " + student2.getName());
        System.out.println("Student 2 Age: " + student2.getAge());
        System.out.println("Is Student 2 an adult? " + student2.isAdult());
        
        System.out.println("\n=== Using Setter Methods ===");
        student1.setName("Charlie");
        student1.setAge(22);
        student1.setStudentId("S003");
        System.out.println("Updated Student 1:");
        student1.displayInfo();
        
        System.out.println("\n=== Using Instance Methods ===");
        System.out.println(student1.getInfo());
        System.out.println(student2.getInfo());
        System.out.println(student3.getInfo());
        
        // Creating multiple objects
        System.out.println("\n=== Multiple Objects ===");
        Student[] students = {  // Array of Student objects
            new Student("David", 19, "S004"),
            new Student("Eve", 21, "S005"),
            new Student("Frank", 18, "S006")
        };
        
        for (Student student : students) {
            System.out.println(student.getInfo());
        }
    }
}

