# Lesson 5: Classes and OOP

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Create classes using the `class` keyword
- Define constructors and methods
- Create instances of classes
- Understand inheritance with `extends`
- Use `super()` to call parent constructors
- Apply object-oriented programming principles

## 📚 What are Classes?

**Classes** are blueprints for creating objects. They define what properties and methods objects of that type will have.

### Basic Class Syntax
```javascript
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
}
```

### Creating Instances
```javascript
let person1 = new Person("Alice", 30);
let person2 = new Person("Bob", 25);

console.log(person1.greet()); // "Hello, I'm Alice"
console.log(person2.getAge()); // 25
```

## 🔄 Inheritance

Classes can inherit from other classes using `extends`:

```javascript
class Student extends Person {
    constructor(name, age, grade) {
        super(name, age); // Call parent constructor
        this.grade = grade;
    }
    
    study() {
        return `${this.name} is studying`;
    }
    
    greet() {
        return `Hi, I'm ${this.name}, a student`;
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: Create a Car Class
Create a class for cars with properties and methods:

**Solution:**
```javascript
class Car {
    constructor(brand, model, year) {
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.speed = 0;
    }
    
    accelerate() {
        this.speed += 10;
        return `Speed is now ${this.speed} mph`;
    }
    
    brake() {
        this.speed -= 10;
        if (this.speed < 0) this.speed = 0;
        return `Speed is now ${this.speed} mph`;
    }
    
    getInfo() {
        return `${this.year} ${this.brand} ${this.model}`;
    }
}
```

### Exercise 2: Create a SportsCar Class
Extend the Car class to create a SportsCar:

**Solution:**
```javascript
class SportsCar extends Car {
    constructor(brand, model, year, topSpeed) {
        super(brand, model, year);
        this.topSpeed = topSpeed;
    }
    
    accelerate() {
        this.speed += 20; // Faster acceleration
        return `Sports car speed is now ${this.speed} mph`;
    }
    
    getTopSpeed() {
        return `Top speed: ${this.topSpeed} mph`;
    }
}
```

## 🎯 Key Takeaways

1. **Classes** are blueprints for objects
2. **Constructor** initializes new instances
3. **Methods** define object behavior
4. **Inheritance** allows classes to extend others
5. **Super()** calls parent constructor

---

**Next Lesson**: [Lesson 6: Error Handling](./lesson6-error-handling.md)
