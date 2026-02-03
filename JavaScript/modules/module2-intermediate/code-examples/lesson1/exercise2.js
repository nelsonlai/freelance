// Exercise 2: Hoisting Behavior
console.log("1. var before:", typeof hoistedVar); // undefined
// console.log("2. let before:", typeof hoistedLet); // ReferenceError

var hoistedVar = "I'm hoisted!";
let hoistedLet = "I'm not hoisted!";

console.log("3. var after:", hoistedVar); // "I'm hoisted!"
console.log("4. let after:", hoistedLet); // "I'm not hoisted!"
