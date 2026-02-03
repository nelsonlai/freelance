// Exercise 1: Callback Function
function fetchUserData(userId, callback) {
    setTimeout(() => {
        const user = {
            id: userId,
            name: "Alice",
            email: "alice@example.com"
        };
        callback(null, user);
    }, 1000);
}

fetchUserData(123, (error, user) => {
    if (error) {
        console.log("Error:", error);
    } else {
        console.log("User:", user);
    }
});
