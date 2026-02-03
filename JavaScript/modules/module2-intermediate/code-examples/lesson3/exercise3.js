// Exercise 3: Dynamic Content
let product = "Laptop";
let price = 999.99;
let discount = 0.15;
let finalPrice = price * (1 - discount);

let description = `Product: ${product}
Original Price: $${price}
Discount: ${discount * 100}%
Final Price: $${finalPrice.toFixed(2)}`;

console.log(description);
