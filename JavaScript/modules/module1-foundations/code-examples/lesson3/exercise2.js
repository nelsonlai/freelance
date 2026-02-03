// Exercise 2: Grade Calculator
let math = 85;
let science = 92;
let english = 78;

let average = (math + science + english) / 3;
let passed = average >= 70;

console.log("Math:", math);
console.log("Science:", science);
console.log("English:", english);
console.log("Average:", average.toFixed(2));  // 85.00
console.log("Passed:", passed);              // true
