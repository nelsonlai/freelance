// Exercise 1: Array Destructuring
let fruits = ["apple", "banana", "orange", "grape", "kiwi"];
let [first, , third, ...rest] = fruits;
let last = rest[rest.length - 1];

console.log("First:", first);   // "apple"
console.log("Third:", third);  // "orange"
console.log("Last:", last);    // "kiwi"
