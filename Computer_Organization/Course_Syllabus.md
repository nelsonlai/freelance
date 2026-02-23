# COURSE SYLLABUS
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## COURSE INFORMATION

**Course Code:** CCIT4026  
**Course Title:** Introduction to Computer Organization  
**Credit Hours:** 3 credits  
**Prerequisites:** Basic programming knowledge (C, Python, or Java)  
**Class Format:** 2 hours lecture + 2 hours lab per week  

---

## COURSE DESCRIPTION

This course provides a comprehensive introduction to computer organization and architecture with emphasis on the MIPS instruction set architecture. Students will learn how computers work at the hardware level, understand the relationship between hardware and software, and develop proficiency in assembly language programming using MIPS.

The course covers fundamental concepts including:
- Computer architecture and organization principles
- Number systems and data representation
- MIPS assembly language programming
- Instruction set design and formats
- Control flow implementation
- Function calls and stack management
- Input/output operations
- Memory organization and addressing modes

---

## LEARNING OUTCOMES

Upon successful completion of this course, students will be able to:

1. **Explain** the fundamental concepts of computer organization and the von Neumann architecture
2. **Describe** the MIPS instruction set architecture and register organization
3. **Write** MIPS assembly programs implementing various algorithms and data structures
4. **Translate** high-level language constructs (C/Java) into MIPS assembly code
5. **Implement** functions with proper calling conventions and stack management
6. **Debug** assembly programs using the MARS simulator
7. **Analyze** program performance and understand the relationship between hardware and software
8. **Apply** knowledge of computer organization to optimize code and understand system behavior

---

## COURSE MATERIALS

### Required Software
- **MARS (MIPS Assembler and Runtime Simulator)** - Free download
- Java Runtime Environment (JRE) 8 or higher

### Recommended Textbooks
1. Patterson & Hennessy, "Computer Organization and Design: The Hardware/Software Interface" (5th Edition)
2. Robert Britton, "MIPS Assembly Language Programming"

### Online Resources
- Course materials on SOUL (Student Online Universal Learning)
- MIPS reference cards (provided)
- MARS documentation and tutorials

---

## COURSE OUTLINE

### **Chapter 1: Introduction** (Weeks 1-2)
- What is Computer Organization?
- Von Neumann Architecture
- Number Systems (Binary, Hexadecimal, Two's Complement)
- Data Representation
- Performance Metrics
- Programming Language Levels

### **Chapter 2: Instruction Set Design (Part 1)** (Weeks 3-4)
- Introduction to MIPS Architecture
- MIPS Register Organization
- Memory Organization and Addressing
- Basic Arithmetic Instructions
- Logical Operations
- Shift Instructions
- Data Transfer Instructions (Load/Store)
- Instruction Formats (R-type, I-type, J-type)

### **Chapter 3: Instruction Set Design (Part 2)** (Weeks 5-7)
- Control Flow Instructions
- Conditional Branches (beq, bne)
- Comparison Operations (slt, slti)
- Unconditional Jumps (j, jal, jr)
- Implementing High-Level Constructs
  - If-then-else statements
  - While loops
  - For loops
- Multiplication and Division
- Addressing Modes
- Pseudo-instructions

### **Chapter 4: Instruction Set Design (Part 3)** (Weeks 8-10)
- Function Calls and Calling Conventions
- Stack Operations
- Parameter Passing
- Return Values
- Saving and Restoring Registers
- Recursive Functions
- Nested Function Calls
- Arrays and Array Processing
- Pointers and Dynamic Data Structures
- Structure Access

### **Chapter 5: Instruction Set Design (Part 4)** (Weeks 11-13)
- System Calls in MARS
- Input/Output Operations
  - Integer and string I/O
  - Character I/O
- String Processing and Manipulation
- Floating-Point Operations
- Memory-Mapped I/O
- Dynamic Memory Allocation
- File Operations (if time permits)
- Advanced Topics and Optimization

---

## ASSESSMENT AND GRADING

### Grade Distribution

| Component | Weight | Description |
|-----------|--------|-------------|
| Laboratory Assignments | 40% | Weekly lab exercises and projects |
| Quizzes | 20% | Regular short quizzes on recent material |
| Midterm Examination | 20% | Covers Chapters 1-3 |
| Final Examination | 20% | Comprehensive, emphasis on Chapters 4-5 |

### Grading Scale

| Grade | Percentage | Description |
|-------|------------|-------------|
| A | 85-100% | Excellent |
| B | 70-84% | Good |
| C | 55-69% | Satisfactory |
| D | 40-54% | Pass |
| F | 0-39% | Fail |

---

## LABORATORY ASSIGNMENTS

### Lab Schedule

1. **Lab 1:** MARS Setup and Hello World (Week 2)
2. **Lab 2:** User Input and Output (Week 4) - **Graded**
3. **Lab 3:** Arithmetic and Logical Operations (Week 5)
4. **Lab 4:** Control Flow and Loops (Week 6)
5. **Lab 5:** Arrays and Array Processing (Week 8)
6. **Lab 6:** Functions and Procedures (Week 9) - **Graded**
7. **Lab 7:** Recursive Algorithms (Week 10)
8. **Lab 8:** String Manipulation (Week 11)
9. **Lab 9:** Comprehensive Project (Week 12-13) - **Graded**

### Lab Submission Requirements

**For Each Lab:**
1. Assembly source code (.asm file)
2. Lab report (PDF) containing:
   - Student information with ID photo
   - Colored source code screenshots from MARS
   - Assembled machine code screenshots
   - Program execution output with termination message
   - Brief explanation of approach (for graded labs)

**Submission Guidelines:**
- Files must be named: `ICO_Lab#_CL##_YourName_StudentID.{asm/pdf}`
- Both .asm and .pdf files required (missing either = 0 marks)
- Submit via SOUL before deadline
- **NO late submissions accepted**
- Code must include proper comments and formatting

---

## COURSE POLICIES

### Attendance
- Attendance is mandatory for both lecture and lab sessions
- Students with more than 30% absences may not be permitted to take the final exam

### Academic Honesty
- The College maintains a **zero-tolerance policy** on cheating and plagiarism
- All work must be your own
- Discussing concepts is encouraged, but code must be written individually
- Copying code from classmates or online sources is strictly prohibited
- Violations will be reported to the Guidance Committee
- Penalties may include assignment failure, course failure, or termination of study

### Student Conduct
- Be respectful to instructor and classmates
- Arrive on time for classes
- Keep mobile phones on silent during class
- No food in computer labs
- Save your work frequently to avoid data loss

### Special Accommodations
- Students requiring accommodations should contact the instructor within the first two weeks
- Documentation may be required

---

## WEEKLY SCHEDULE

| Week | Lecture Topic | Lab Activity | Assessments |
|------|---------------|--------------|-------------|
| 1 | Course Introduction, Ch 1: Computer Organization Basics | MARS Installation and Setup | - |
| 2 | Ch 1: Number Systems and Data Representation | Lab 1: Hello World Program | - |
| 3 | Ch 2: MIPS Architecture, Registers, Arithmetic | Lab 2 Work: User I/O | - |
| 4 | Ch 2: Logical Operations, Data Transfer, Instruction Formats | Lab 2: Complete and Submit | **Lab 2 Due** |
| 5 | Ch 3: Control Flow, Branches | Lab 3: Arithmetic Programs | **Quiz 1** |
| 6 | Ch 3: Loops and High-Level Constructs | Lab 4: Loops and Conditions | - |
| 7 | Ch 3: Multiplication, Division, Addressing Modes | Lab 5 Work: Array Processing | - |
| 8 | **Midterm Review** | Lab 5: Complete Arrays Lab | **Midterm Exam** |
| 9 | Ch 4: Functions and Stack | Lab 6: Function Implementation | **Lab 5 Due** |
| 10 | Ch 4: Recursion and Nested Calls | Lab 7: Recursive Programs | **Quiz 2** |
| 11 | Ch 5: System Calls and I/O | Lab 8: String Processing | **Lab 6 Due** |
| 12 | Ch 5: String Processing, Floating-Point | Lab 9: Start Final Project | - |
| 13 | Ch 5: Advanced Topics, Optimization | Lab 9: Project Work | **Quiz 3** |
| 14 | **Final Exam Review** | Lab 9: Project Completion | **Lab 9 Due** |
| 15 | **Final Examination** | - | **Final Exam** |

---

## TIPS FOR SUCCESS

### General Study Strategies
1. **Attend all classes** - Material builds cumulatively
2. **Practice regularly** - Programming skills improve with repetition
3. **Start assignments early** - Don't wait until the deadline
4. **Ask questions** - Use office hours and online forums
5. **Study in groups** - Discuss concepts (but write code individually)
6. **Read before class** - Come prepared with questions
7. **Review after class** - Reinforce learning within 24 hours

### MIPS Programming Tips
1. **Plan before coding** - Write pseudocode or flowcharts first
2. **Use comments generously** - Explain your logic
3. **Test incrementally** - Don't write everything then test
4. **Use the debugger** - Step through code to understand behavior
5. **Save frequently** - Prevent data loss
6. **Organize your code** - Use consistent formatting and naming
7. **Learn from errors** - Understand why mistakes happened

### Exam Preparation
1. Work through all practice problems
2. Review lab code you've written
3. Create your own MIPS reference card
4. Practice translating C to MIPS
5. Time yourself on practice problems
6. Understand concepts, don't just memorize

---

## CONTACT INFORMATION

**Instructor:** [Your Name]  
**Email:** [instructor.email@hkuspace.hku.hk]  
**Office:** [Office Location]  
**Office Hours:** [Days and Times] or by appointment  

**Teaching Assistant:** [TA Name]  
**Email:** [ta.email@hkuspace.hku.hk]  
**Lab Hours:** [Days and Times]  

**Course Website:** SOUL (Student Online Universal Learning)  
**Discussion Forum:** [Forum URL/Platform]  

---

## IMPORTANT DATES

- **First Class:** [Date]
- **Lab 2 Due:** Week 4
- **Quiz 1:** Week 5
- **Midterm Exam:** Week 8
- **Lab 6 Due:** Week 11
- **Quiz 3:** Week 13
- **Lab 9 (Final Project) Due:** Week 14
- **Final Examination:** Week 15
- **Last Day to Withdraw:** [Date]

---

## STUDENT RESOURCES

### Technical Support
- **IT Helpdesk:** [Contact Information]
- **Computer Lab Access:** [Hours and Location]
- **Software Installation Help:** [Support Resources]

### Academic Support
- **Tutoring Services:** [Information]
- **Writing Center:** [For lab report help]
- **Study Groups:** [Information]
- **Peer Mentoring:** [Information]

### Wellness Resources
- **Counseling Services:** [Contact Information]
- **Health Services:** [Contact Information]
- **Student Affairs:** [Contact Information]

---

## ACKNOWLEDGMENT

By enrolling in this course, you acknowledge that you have:
- Read and understood this syllabus
- Reviewed the course requirements and assessment criteria
- Understood the academic honesty policy
- Agreed to comply with all course policies and procedures
- Understood that failure to comply may result in grade penalties or disciplinary action

---

**This syllabus is subject to change at the instructor's discretion. Students will be notified of any changes via SOUL and email.**

---

*Last Updated: February 2026*
*Course Code: CCIT4026*
*HKU SPACE Community College*
