// Exercise 2: Promise-based Function
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

fetchUserDataPromise(123)
    .then((user) => {
        console.log("User:", user);
    })
    .catch((error) => {
        console.log("Error:", error);
    });
