// Lesson 1: Scope and Hoisting Examples

console.log("=== Global vs Local Scope ===");

// Global scope
let globalVariable = "I'm global!";

function myFunction() {
    // Local scope
    let localVariable = "I'm local!";
    console.log("Inside function - global:", globalVariable);
    console.log("Inside function - local:", localVariable);
}

myFunction();
console.log("Outside function - global:", globalVariable);
// console.log("Outside function - local:", localVariable); // Error!

console.log("\n=== Lexical Scope ===");

function outerFunction() {
    let outerVariable = "I'm in outer function";
    
    function innerFunction() {
        console.log("Inner can access outer:", outerVariable);
        let innerVariable = "I'm in inner function";
        console.log("Inner can access inner:", innerVariable);
    }
    
    innerFunction();
    console.log("Outer can access outer:", outerVariable);
    // console.log("Outer can access inner:", innerVariable); // Error!
}

outerFunction();

console.log("\n=== Hoisting with var ===");

console.log("Before declaration:", typeof hoistedVar); // undefined
var hoistedVar = "I'm hoisted!";
console.log("After declaration:", hoistedVar);

console.log("\n=== Hoisting with let/const ===");

// console.log("Before declaration:", typeof hoistedLet); // ReferenceError
let hoistedLet = "I'm not hoisted!";
console.log("After declaration:", hoistedLet);

console.log("\n=== Function Hoisting ===");

sayHello(); // Works!

function sayHello() {
    console.log("Hello from hoisted function!");
}

// sayGoodbye(); // Error!
const sayGoodbye = function() {
    console.log("Goodbye from function expression!");
};

console.log("\n=== Scope Chain Example ===");

let globalVar = "global";

function level1() {
    let level1Var = "level1";
    
    function level2() {
        let level2Var = "level2";
        console.log("Level 2 can see:", globalVar, level1Var, level2Var);
        
        function level3() {
            console.log("Level 3 can see:", globalVar, level1Var, level2Var);
        }
        
        level3();
    }
    
    level2();
    console.log("Level 1 can see:", globalVar, level1Var);
}

level1();

console.log("\n=== Loop Variable Issues ===");

console.log("Problem with var in loops:");
for (var i = 0; i < 3; i++) {
    setTimeout(() => console.log("var i:", i), 100); // Logs 3, 3, 3
}

console.log("Solution with let:");
for (let j = 0; j < 3; j++) {
    setTimeout(() => console.log("let j:", j), 100); // Logs 0, 1, 2
}
