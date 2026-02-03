// Lesson 2: Destructuring & Spread/Rest Examples

console.log("=== Array Destructuring ===");

let colors = ["red", "green", "blue"];
let [first, second, third] = colors;
console.log("First:", first);   // "red"
console.log("Second:", second); // "green"
console.log("Third:", third);  // "blue"

console.log("\n=== Skipping Elements ===");
let numbers = [1, 2, 3, 4, 5];
let [firstNum, , thirdNum, , fifthNum] = numbers;
console.log("First:", firstNum);   // 1
console.log("Third:", thirdNum);    // 3
console.log("Fifth:", fifthNum);    // 5

console.log("\n=== Default Values ===");
let shortArray = ["red"];
let [color1, color2 = "green", color3 = "blue"] = shortArray;
console.log("Color 1:", color1);   // "red"
console.log("Color 2:", color2);   // "green" (default)
console.log("Color 3:", color3);   // "blue" (default)

console.log("\n=== Rest Operator in Arrays ===");
let allNumbers = [1, 2, 3, 4, 5];
let [firstItem, secondItem, ...rest] = allNumbers;
console.log("First:", firstItem);      // 1
console.log("Second:", secondItem);    // 2
console.log("Rest:", rest);        // [3, 4, 5]

console.log("\n=== Object Destructuring ===");
let person = {
    name: "Alice",
    age: 30,
    city: "New York"
};

let { name, age, city } = person;
console.log("Name:", name);        // "Alice"
console.log("Age:", age);          // 30
console.log("City:", city);        // "New York"

console.log("\n=== Renaming Variables ===");
let { name: fullName, age: years } = person;
console.log("Full Name:", fullName); // "Alice"
console.log("Years:", years);        // 30

console.log("\n=== Object Default Values ===");
let partialPerson = { name: "Alice" };
let { name: pName, age: pAge = 25, city: pCity = "Unknown" } = partialPerson;
console.log("Name:", pName);        // "Alice"
console.log("Age:", pAge);          // 25 (default)
console.log("City:", pCity);        // "Unknown" (default)

console.log("\n=== Nested Destructuring ===");
let user = {
    name: "Alice",
    address: {
        street: "123 Main St",
        city: "New York"
    }
};

let { name: userName, address: { street, city: userCity } } = user;
console.log("Name:", userName);     // "Alice"
console.log("Street:", street);      // "123 Main St"
console.log("City:", userCity);      // "New York"

console.log("\n=== Array Spread ===");
let arr1 = [1, 2, 3];
let arr2 = [4, 5, 6];
let combined = [...arr1, ...arr2];
console.log("Combined:", combined); // [1, 2, 3, 4, 5, 6]

let original = [1, 2, 3];
let copy = [...original];
console.log("Copy:", copy);         // [1, 2, 3]

console.log("\n=== Object Spread ===");
let obj1 = { a: 1, b: 2 };
let obj2 = { c: 3, d: 4 };
let combinedObj = { ...obj1, ...obj2 };
console.log("Combined Object:", combinedObj); // { a: 1, b: 2, c: 3, d: 4 }

let person2 = { name: "Alice", age: 30 };
let updated = { ...person2, age: 31 };
console.log("Updated:", updated);   // { name: "Alice", age: 31 }

console.log("\n=== Rest in Function Parameters ===");
function sum(...numbers) {
    return numbers.reduce((total, num) => total + num, 0);
}

console.log("Sum 1,2,3:", sum(1, 2, 3));        // 6
console.log("Sum 1,2,3,4,5:", sum(1, 2, 3, 4, 5)); // 15

console.log("\n=== Rest in Objects ===");
let fullPerson = {
    name: "Alice",
    age: 30,
    city: "New York",
    country: "USA"
};

let { name: personName, ...details } = fullPerson;
console.log("Name:", personName);   // "Alice"
console.log("Details:", details);   // { age: 30, city: "New York", country: "USA" }
