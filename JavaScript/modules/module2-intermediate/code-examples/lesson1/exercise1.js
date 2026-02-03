// Exercise 1: Scope Understanding
let globalVar = "global";

function testScope() {
    let localVar = "local";
    console.log("Inside function - global:", globalVar);
    console.log("Inside function - local:", localVar);
}

testScope();
console.log("Outside function - global:", globalVar);
// console.log("Outside function - local:", localVar); // Error!
