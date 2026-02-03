// Exercise 3: Age Verification
let age = 20;
let hasLicense = true;

let canVote = age >= 18;
let canDrive = age >= 16 && hasLicense;
let canDrink = age >= 21;

console.log("Age:", age);
console.log("Has license:", hasLicense);
console.log("Can vote:", canVote);    // true
console.log("Can drive:", canDrive);  // true
console.log("Can drink:", canDrink);  // false
