// Exercise 2: Object Destructuring
let student = {
    firstName: "Alice",
    lastName: "Smith",
    grade: 95,
    subject: "Math"
};

let { firstName: fName, lastName: lName, grade: score } = student;
console.log("Name:", fName, lName); // "Alice Smith"
console.log("Score:", score);       // 95
