// Exercise 1: Safe Division Function
// This exercise demonstrates basic error handling with try-catch

console.log("=== Exercise 1: Safe Division Function ===");

function safeDivide(a, b) {
    try {
        // Check if both arguments are numbers
        if (typeof a !== 'number' || typeof b !== 'number') {
            throw new Error("Both arguments must be numbers");
        }
        
        // Check for division by zero
        if (b === 0) {
            throw new Error("Cannot divide by zero");
        }
        
        // Check for invalid numbers (NaN, Infinity)
        if (!isFinite(a) || !isFinite(b)) {
            throw new Error("Arguments must be finite numbers");
        }
        
        const result = a / b;
        return {
            success: true,
            result: result,
            message: `${a} ÷ ${b} = ${result}`
        };
        
    } catch (error) {
        return {
            success: false,
            result: null,
            message: `Error: ${error.message}`
        };
    }
}

// Test the safe division function
console.log("Testing safe division function:");

const testCases = [
    { a: 10, b: 2, description: "Normal division" },
    { a: 10, b: 0, description: "Division by zero" },
    { a: 10, b: 'abc', description: "Non-numeric divisor" },
    { a: 'xyz', b: 5, description: "Non-numeric dividend" },
    { a: 10, b: Infinity, description: "Infinite divisor" },
    { a: NaN, b: 5, description: "NaN dividend" },
    { a: 0, b: 5, description: "Zero dividend" },
    { a: -10, b: 3, description: "Negative dividend" },
    { a: 10, b: -3, description: "Negative divisor" },
    { a: 0, b: 0, description: "Zero divided by zero" }
];

testCases.forEach((testCase, index) => {
    console.log(`\nTest ${index + 1}: ${testCase.description}`);
    console.log(`Input: ${testCase.a}, ${testCase.b}`);
    const result = safeDivide(testCase.a, testCase.b);
    console.log(`Result: ${result.message}`);
});

// Additional utility function for batch processing
function processDivisionBatch(operations) {
    const results = [];
    
    for (let i = 0; i < operations.length; i++) {
        const operation = operations[i];
        console.log(`\nProcessing operation ${i + 1}: ${operation.a} ÷ ${operation.b}`);
        
        try {
            const result = safeDivide(operation.a, operation.b);
            results.push(result);
            
            if (result.success) {
                console.log(`✓ Success: ${result.message}`);
            } else {
                console.log(`✗ Failed: ${result.message}`);
            }
        } catch (error) {
            console.log(`✗ Unexpected error: ${error.message}`);
            results.push({
                success: false,
                result: null,
                message: `Unexpected error: ${error.message}`
            });
        }
    }
    
    return results;
}

// Test batch processing
console.log("\n=== Batch Processing Test ===");
const batchOperations = [
    { a: 100, b: 4 },
    { a: 50, b: 0 },
    { a: 25, b: 5 },
    { a: 10, b: 'invalid' }
];

const batchResults = processDivisionBatch(batchOperations);

// Summary
const successCount = batchResults.filter(r => r.success).length;
const failureCount = batchResults.filter(r => !r.success).length;

console.log(`\n=== Batch Processing Summary ===`);
console.log(`Total operations: ${batchResults.length}`);
console.log(`Successful: ${successCount}`);
console.log(`Failed: ${failureCount}`);
console.log(`Success rate: ${((successCount / batchResults.length) * 100).toFixed(1)}%`);
