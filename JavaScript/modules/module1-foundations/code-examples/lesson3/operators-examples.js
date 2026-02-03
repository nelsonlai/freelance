// Lesson 3: Operators Examples

console.log("=== Arithmetic Operators ===");
let a = 10;
let b = 3;

console.log("a =", a, "b =", b);
console.log("a + b =", a + b);  // 13
console.log("a - b =", a - b);  // 7
console.log("a * b =", a * b);  // 30
console.log("a / b =", a / b);  // 3.333...
console.log("a % b =", a % b);  // 1
console.log("a ** b =", a ** b); // 1000

console.log("\n=== Assignment Operators ===");
let x = 10;
console.log("Initial x:", x);

x += 5;   // x = x + 5
console.log("After x += 5:", x);  // 15

x -= 3;   // x = x - 3
console.log("After x -= 3:", x);  // 12

x *= 2;   // x = x * 2
console.log("After x *= 2:", x);  // 24

x /= 4;   // x = x / 4
console.log("After x /= 4:", x);  // 6

x %= 5;   // x = x % 5
console.log("After x %= 5:", x);  // 1

console.log("\n=== Comparison Operators ===");
let num1 = 10;
let num2 = 5;

console.log("num1 =", num1, "num2 =", num2);
console.log("num1 > num2:", num1 > num2);   // true
console.log("num1 < num2:", num1 < num2);   // false
console.log("num1 >= num2:", num1 >= num2);  // true
console.log("num1 <= num2:", num1 <= num2);  // false
console.log("num1 == num2:", num1 == num2);  // false
console.log("num1 != num2:", num1 != num2);  // true
console.log("num1 === num2:", num1 === num2); // false
console.log("num1 !== num2:", num1 !== num2); // true

console.log("\n=== Strict vs Loose Equality ===");
let num = 5;
let str = "5";

console.log("num =", num, "str =", str);
console.log("num == str:", num == str);   // true (loose)
console.log("num === str:", num === str); // false (strict)

console.log("\n=== Logical Operators ===");
let age = 25;
let hasLicense = true;
let isStudent = false;

console.log("age =", age, "hasLicense =", hasLicense, "isStudent =", isStudent);
console.log("age >= 18 && hasLicense:", age >= 18 && hasLicense); // true
console.log("isStudent || age >= 65:", isStudent || age >= 65);   // false
console.log("!isStudent:", !isStudent); // true

console.log("\n=== Ternary Operator ===");
let userAge = 20;
let status = userAge >= 18 ? "adult" : "minor";
console.log("Age:", userAge, "Status:", status);

let score = 85;
let grade = score >= 90 ? "A" : score >= 80 ? "B" : "C";
console.log("Score:", score, "Grade:", grade);

console.log("\n=== Operator Precedence ===");
let result1 = 2 + 3 * 4;
let result2 = (2 + 3) * 4;
console.log("2 + 3 * 4 =", result1);     // 14
console.log("(2 + 3) * 4 =", result2);    // 20

console.log("\n=== Short-Circuit Evaluation ===");
let bool1 = false;
let bool2 = true;
let result3 = bool1 && bool2;
console.log("false && true =", result3);  // false

let bool3 = true;
let bool4 = false;
let result4 = bool3 || bool4;
console.log("true || false =", result4); // true
