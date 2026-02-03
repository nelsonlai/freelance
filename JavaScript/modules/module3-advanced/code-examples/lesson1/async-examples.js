// Lesson 1: Asynchronous JavaScript Examples

console.log("=== Synchronous vs Asynchronous ===");

// Synchronous (blocking)
console.log("1. Synchronous start");
console.log("2. Synchronous middle");
console.log("3. Synchronous end");

// Asynchronous (non-blocking)
console.log("4. Asynchronous start");
setTimeout(() => console.log("5. Asynchronous delayed"), 1000);
console.log("6. Asynchronous end");

console.log("\n=== Callback Examples ===");

function fetchData(callback) {
    setTimeout(() => {
        const data = "Hello from server!";
        callback(data);
    }, 1000);
}

fetchData((result) => {
    console.log("Callback result:", result);
});

console.log("\n=== Promise Examples ===");

const myPromise = new Promise((resolve, reject) => {
    const success = Math.random() > 0.5;
    
    setTimeout(() => {
        if (success) {
            resolve("Operation successful!");
        } else {
            reject("Operation failed!");
        }
    }, 1000);
});

myPromise
    .then((result) => {
        console.log("Promise success:", result);
    })
    .catch((error) => {
        console.log("Promise error:", error);
    });

console.log("\n=== Multiple Promises ===");

const promise1 = new Promise(resolve => setTimeout(() => resolve("First"), 1000));
const promise2 = new Promise(resolve => setTimeout(() => resolve("Second"), 1500));
const promise3 = new Promise(resolve => setTimeout(() => resolve("Third"), 500));

Promise.all([promise1, promise2, promise3])
    .then((results) => {
        console.log("All promises completed:", results);
    });

Promise.race([promise1, promise2, promise3])
    .then((result) => {
        console.log("First promise completed:", result);
    });

console.log("\n=== Async/Await Examples ===");

async function fetchDataAsync() {
    try {
        // Simulate API call
        const response = await new Promise(resolve => 
            setTimeout(() => resolve({ data: "API response" }), 1000)
        );
        console.log("Async result:", response.data);
        return response.data;
    } catch (error) {
        console.log("Async error:", error);
    }
}

fetchDataAsync();

console.log("\n=== Error Handling ===");

async function riskyOperation() {
    try {
        const result = await new Promise((resolve, reject) => {
            setTimeout(() => {
                if (Math.random() > 0.5) {
                    resolve("Success!");
                } else {
                    reject(new Error("Something went wrong!"));
                }
            }, 1000);
        });
        console.log("Risky operation result:", result);
    } catch (error) {
        console.log("Risky operation error:", error.message);
    }
}

riskyOperation();
