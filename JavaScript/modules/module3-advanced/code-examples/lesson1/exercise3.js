// Exercise 3: Async/Await Function
async function getUserData(userId) {
    try {
        const user = await fetchUserDataPromise(userId);
        console.log("User:", user);
        return user;
    } catch (error) {
        console.log("Error:", error);
    }
}

// Helper function from exercise 2
function fetchUserDataPromise(userId) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            const user = {
                id: userId,
                name: "Alice",
                email: "alice@example.com"
            };
            resolve(user);
        }, 1000);
    });
}

getUserData(123);
