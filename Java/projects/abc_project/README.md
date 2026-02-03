# ABC Project - Multi-File Java Project Example

This project demonstrates a simple multi-file Java application where:
- **A.java** is the main class that uses classes from B.java and C.java
- **B.java** provides utility functions (mathematical operations)
- **C.java** provides data processing functions (string and array operations)

## Project Structure

```
abc_project/
├── A.java          # Main class - uses B and C
├── B.java          # Utility class with mathematical operations
├── C.java          # Processor class with data processing operations
└── README.md       # This file
```

## How to Compile and Run

### Method 1: Compile All Files Together (Recommended)

1. **Navigate to the project directory:**
   ```bash
   cd projects/abc_project
   ```

2. **Compile all Java files:**
   ```bash
   javac *.java
   ```
   This will compile A.java, B.java, and C.java and create corresponding `.class` files (A.class, B.class, C.class).

3. **Run the program:**
   ```bash
   java A
   ```

### Method 2: Compile Individual Files (In Order)

If you prefer to compile files individually, you need to compile in the correct order:

1. **Navigate to the project directory:**
   ```bash
   cd projects/abc_project
   ```

2. **Compile B.java first** (since A depends on B):
   ```bash
   javac B.java
   ```

3. **Compile C.java** (since A depends on C):
   ```bash
   javac C.java
   ```

4. **Compile A.java** (the main class):
   ```bash
   javac A.java
   ```

5. **Run the program:**
   ```bash
   java A
   ```

### Method 3: Compile with Output Directory

For better organization, you can compile to a separate directory:

1. **Create a bin directory:**
   ```bash
   mkdir bin
   ```

2. **Compile all files to the bin directory:**
   ```bash
   javac -d bin *.java
   ```

3. **Run from the bin directory:**
   ```bash
   java -cp bin A
   ```

   Or run from the project root:
   ```bash
   java -cp bin A
   ```

## Expected Output

When you run the program, you should see output like:

```
=== Multi-File Java Project Demo ===

--- Using B class methods ---
Sum of 10 and 20: 30
Product of 5 and 6: 30
Is 15 even? false
Is 16 even? true

--- Using C class methods ---
Hello, Alice! Welcome to the program.
Array: [1, 2, 3, 4, 5]
Maximum value: 5
Minimum value: 1
Reversed 'Hello World': dlroW olleH

--- Combining B and C functionality ---
Array: [12, 45, 7, 23, 56]
Maximum value: 56
Is maximum value even? true

=== Project Structure ===
abc_project/
  ├── A.java  (Main class - uses B and C)
  ├── B.java  (Utility class)
  └── C.java  (Processor class)
```

## Key Concepts Demonstrated

1. **Multiple Java Files**: Working with multiple `.java` files in the same project
2. **Class Dependencies**: A.java depends on B.java and C.java
3. **Compilation Order**: Understanding that dependent classes need to be compiled
4. **Class Usage**: Creating instances and calling methods from other classes
5. **No Packages**: Simple example without package declarations (all classes in default package)

## Troubleshooting

### Error: "cannot find symbol"
- **Solution**: Make sure all files (A.java, B.java, C.java) are in the same directory
- **Solution**: Compile all files together using `javac *.java`

### Error: "class file not found"
- **Solution**: Make sure you've compiled all files before running
- **Solution**: Check that `.class` files exist in the same directory

### Error: "main method not found"
- **Solution**: Make sure you're running `java A` (not `java A.java` or `java a`)

## Notes

- All classes are in the default package (no package declaration)
- All files must be in the same directory for this simple example
- The `javac *.java` command compiles all `.java` files in the current directory
- The `java A` command runs the main method in class A

