// Lesson 2: Variables and Data Types Examples

// 1. Variable Declaration Examples
console.log("=== Variable Declaration ===");

// Using let (can be changed)
let age = 25;
let name = "Alice";
let isStudent = true;

console.log("Age:", age);
console.log("Name:", name);
console.log("Is student:", isStudent);

// Change the age
age = 26;
console.log("New age:", age);

// Using const (cannot be changed)
const pi = 3.14159;
const company = "Google";
const maxUsers = 1000;

console.log("Pi:", pi);
console.log("Company:", company);
console.log("Max users:", maxUsers);

// This would cause an error:
// pi = 3.14;  // Error! Cannot change const

// 2. Data Types Examples
console.log("\n=== Data Types ===");

// Numbers
let integer = 42;
let decimal = 3.14;
let negative = -10;
let bigNumber = 1000000;

console.log("Integer:", integer);
console.log("Decimal:", decimal);
console.log("Negative:", negative);
console.log("Big number:", bigNumber);

// Strings
let singleQuote = 'Hello';
let doubleQuote = "World";
let templateLiteral = `Hello ${name}`;

console.log("Single quote:", singleQuote);
console.log("Double quote:", doubleQuote);
console.log("Template literal:", templateLiteral);

// Booleans
let isTrue = true;
let isFalse = false;

console.log("True:", isTrue);
console.log("False:", isFalse);

// Undefined and null
let undefinedVar;
let nullVar = null;

console.log("Undefined:", undefinedVar);
console.log("Null:", nullVar);

// 3. Type Checking
console.log("\n=== Type Checking ===");
console.log("Type of 42:", typeof 42);
console.log("Type of 'Hello':", typeof "Hello");
console.log("Type of true:", typeof true);
console.log("Type of undefined:", typeof undefined);
console.log("Type of null:", typeof null);

// 4. Type Conversion Examples
console.log("\n=== Type Conversion ===");

// String to Number
let ageString = "25";
let ageNumber = Number(ageString);
console.log("Age string:", ageString, typeof ageString);
console.log("Age number:", ageNumber, typeof ageNumber);

// Number to String
let score = 95;
let scoreString = String(score);
console.log("Score number:", score, typeof score);
console.log("Score string:", scoreString, typeof scoreString);

// Boolean conversion
let text = "Hello";
let emptyText = "";
let zero = 0;

console.log("Boolean of 'Hello':", Boolean(text));
console.log("Boolean of empty string:", Boolean(emptyText));
console.log("Boolean of 0:", Boolean(zero));
