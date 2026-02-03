// Exercise 3: Scope Chain
let globalVar = "global";

function outerFunction() {
    let outerVar = "outer";
    
    function innerFunction() {
        let innerVar = "inner";
        console.log("Inner can see:", globalVar, outerVar, innerVar);
        
        function deepestFunction() {
            console.log("Deepest can see:", globalVar, outerVar, innerVar);
        }
        
        deepestFunction();
    }
    
    innerFunction();
    console.log("Outer can see:", globalVar, outerVar);
}

outerFunction();
