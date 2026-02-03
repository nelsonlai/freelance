// Lesson 5: Classes and OOP Examples

console.log("=== Classes and Object-Oriented Programming ===");

// Example 1: Basic Class Definition
console.log("\n=== Basic Class Example ===");
class Person {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }
    
    greet() {
        return `Hello, I'm ${this.name}`;
    }
    
    getAge() {
        return this.age;
    }
    
    haveBirthday() {
        this.age++;
        return `Happy birthday! ${this.name} is now ${this.age}`;
    }
    
    introduce() {
        return `My name is ${this.name} and I'm ${this.age} years old`;
    }
}

// Creating instances
let person1 = new Person("Alice", 30);
let person2 = new Person("Bob", 25);

console.log("Person 1:", person1.greet());
console.log("Person 2 age:", person2.getAge());
console.log("Person 1 birthday:", person1.haveBirthday());
console.log("Person 2 introduction:", person2.introduce());

// Example 2: Class with More Complex Methods
console.log("\n=== Complex Class Example ===");
class BankAccount {
    constructor(accountNumber, ownerName, initialBalance = 0) {
        this.accountNumber = accountNumber;
        this.ownerName = ownerName;
        this.balance = initialBalance;
        this.transactions = [];
    }
    
    deposit(amount) {
        if (amount > 0) {
            this.balance += amount;
            this.transactions.push({
                type: 'deposit',
                amount: amount,
                date: new Date()
            });
            return `Deposited $${amount}. New balance: $${this.balance}`;
        }
        return "Invalid deposit amount";
    }
    
    withdraw(amount) {
        if (amount > 0 && amount <= this.balance) {
            this.balance -= amount;
            this.transactions.push({
                type: 'withdrawal',
                amount: amount,
                date: new Date()
            });
            return `Withdrew $${amount}. New balance: $${this.balance}`;
        }
        return "Insufficient funds or invalid amount";
    }
    
    getBalance() {
        return this.balance;
    }
    
    getAccountInfo() {
        return `Account: ${this.accountNumber}, Owner: ${this.ownerName}, Balance: $${this.balance}`;
    }
    
    getTransactionHistory() {
        return this.transactions;
    }
}

// Using the BankAccount class
let account = new BankAccount("12345", "Alice Johnson", 1000);
console.log("Initial account:", account.getAccountInfo());
console.log("Deposit:", account.deposit(500));
console.log("Withdraw:", account.withdraw(200));
console.log("Final balance:", account.getBalance());
console.log("Transactions:", account.getTransactionHistory().length);

// Example 3: Inheritance
console.log("\n=== Inheritance Example ===");
class Student extends Person {
    constructor(name, age, grade, studentId) {
        super(name, age); // Call parent constructor
        this.grade = grade;
        this.studentId = studentId;
        this.subjects = [];
    }
    
    study(subject) {
        this.subjects.push(subject);
        return `${this.name} is studying ${subject}`;
    }
    
    greet() {
        return `Hi, I'm ${this.name}, a student in grade ${this.grade}`;
    }
    
    getStudentInfo() {
        return `Student ID: ${this.studentId}, Grade: ${this.grade}, Subjects: ${this.subjects.join(', ')}`;
    }
}

class Teacher extends Person {
    constructor(name, age, subject, employeeId) {
        super(name, age);
        this.subject = subject;
        this.employeeId = employeeId;
        this.students = [];
    }
    
    teach(student) {
        return `${this.name} is teaching ${this.subject} to ${student.name}`;
    }
    
    addStudent(student) {
        this.students.push(student);
        return `Added ${student.name} to ${this.name}'s class`;
    }
    
    greet() {
        return `Hello, I'm ${this.name}, a ${this.subject} teacher`;
    }
    
    getTeacherInfo() {
        return `Employee ID: ${this.employeeId}, Subject: ${this.subject}, Students: ${this.students.length}`;
    }
}

// Using inheritance
let student = new Student("Charlie", 16, 10, "S001");
let teacher = new Teacher("Ms. Smith", 35, "Mathematics", "T001");

console.log("Student:", student.greet());
console.log("Teacher:", teacher.greet());
console.log("Student studying:", student.study("Math"));
console.log("Teacher teaching:", teacher.teach(student));
console.log("Teacher adding student:", teacher.addStudent(student));
console.log("Student info:", student.getStudentInfo());
console.log("Teacher info:", teacher.getTeacherInfo());

// Example 4: Method Overriding and Super
console.log("\n=== Method Overriding Example ===");
class Animal {
    constructor(name, species) {
        this.name = name;
        this.species = species;
    }
    
    speak() {
        return `${this.name} makes a sound`;
    }
    
    move() {
        return `${this.name} moves`;
    }
    
    getInfo() {
        return `${this.name} is a ${this.species}`;
    }
}

class Dog extends Animal {
    constructor(name, breed) {
        super(name, "dog");
        this.breed = breed;
    }
    
    speak() {
        return `${this.name} barks: Woof! Woof!`;
    }
    
    fetch() {
        return `${this.name} fetches the ball`;
    }
    
    getInfo() {
        return super.getInfo() + ` (${this.breed})`;
    }
}

class Cat extends Animal {
    constructor(name, breed) {
        super(name, "cat");
        this.breed = breed;
    }
    
    speak() {
        return `${this.name} meows: Meow! Meow!`;
    }
    
    climb() {
        return `${this.name} climbs the tree`;
    }
    
    getInfo() {
        return super.getInfo() + ` (${this.breed})`;
    }
}

// Using method overriding
let dog = new Dog("Buddy", "Golden Retriever");
let cat = new Cat("Whiskers", "Persian");

console.log("Dog info:", dog.getInfo());
console.log("Cat info:", cat.getInfo());
console.log("Dog speaks:", dog.speak());
console.log("Cat speaks:", cat.speak());
console.log("Dog action:", dog.fetch());
console.log("Cat action:", cat.climb());

// Example 5: Static Methods and Properties
console.log("\n=== Static Methods Example ===");
class MathUtils {
    static PI = 3.14159;
    static E = 2.71828;
    
    static add(a, b) {
        return a + b;
    }
    
    static multiply(a, b) {
        return a * b;
    }
    
    static circleArea(radius) {
        return MathUtils.PI * radius * radius;
    }
    
    static getConstants() {
        return {
            pi: MathUtils.PI,
            e: MathUtils.E
        };
    }
}

console.log("Static PI:", MathUtils.PI);
console.log("Static add:", MathUtils.add(5, 3));
console.log("Static multiply:", MathUtils.multiply(4, 6));
console.log("Circle area:", MathUtils.circleArea(5));
console.log("Constants:", MathUtils.getConstants());

console.log("\n=== Class Concepts Summary ===");
console.log("✓ Classes are blueprints for objects");
console.log("✓ Constructor initializes new instances");
console.log("✓ Methods define object behavior");
console.log("✓ Inheritance allows classes to extend others");
console.log("✓ Super() calls parent constructor");
console.log("✓ Static methods belong to the class, not instances");
console.log("✓ Method overriding allows custom behavior in child classes");
