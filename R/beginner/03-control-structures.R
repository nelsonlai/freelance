# Control Structures in R
# This script covers conditional statements, loops, and functions

# ============================================================
# 1. IF/ELSE STATEMENTS
# ============================================================

# Basic if statement
x <- 10

if (x > 5) {
  print("x is greater than 5")
}

# If-else statement
if (x > 15) {
  print("x is greater than 15")
} else {
  print("x is not greater than 15")
}

# If-else if-else (nested conditions)
score <- 85

if (score >= 90) {
  grade <- "A"
} else if (score >= 80) {
  grade <- "B"
} else if (score >= 70) {
  grade <- "C"
} else {
  grade <- "F"
}

print(grade)

# ============================================================
# 2. FOR LOOPS
# ============================================================

# Basic for loop
for (i in 1:5) {
  print(i)
}

# Loop through a vector
numbers <- c(10, 20, 30, 40, 50)
for (num in numbers) {
  print(num)
}

# Calculate sum using a loop
sum_result <- 0
for (i in 1:10) {
  sum_result <- sum_result + i
}
print(sum_result)

# ============================================================
# 3. WHILE LOOPS
# ============================================================

# Basic while loop
counter <- 1
while (counter <= 5) {
  print(counter)
  counter <- counter + 1
}

# Countdown example
count <- 10
while (count >= 0) {
  print(count)
  count <- count - 1
}

# ============================================================
# 4. FUNCTIONS
# ============================================================

# Simple function
add_numbers <- function(a, b) {
  result <- a + b
  return(result)
}

# Use the function
sum_result <- add_numbers(5, 3)
print(sum_result)

# Function with default value
greet <- function(name, greeting = "Hello") {
  return(paste(greeting, name))
}

greet("Alice")
greet("Bob", "Hi")

# Function with multiple statements
calculate_stats <- function(numbers) {
  total <- sum(numbers)
  count <- length(numbers)
  mean_val <- total / count
  return(list(
    sum = total,
    count = count,
    mean = mean_val
  ))
}

result <- calculate_stats(c(1, 2, 3, 4, 5))
print(result)

# ============================================================
# 5. APPLY FAMILY FUNCTIONS
# ============================================================

# Apply (for matrices or data frames)
mat <- matrix(1:12, nrow = 3, ncol = 4)
mat

# Apply function to rows
apply(mat, 1, sum)

# Apply function to columns
apply(mat, 2, sum)

# lapply (for lists)
my_list <- list(a = 1:5, b = 6:10, c = 11:15)
lapply(my_list, mean)

# sapply (simplified apply)
sapply(my_list, mean)

# ============================================================
# 6. PRACTICE EXAMPLES
# ============================================================

# Example 1: Check if numbers are even or odd
check_even_odd <- function(number) {
  if (number %% 2 == 0) {
    return("Even")
  } else {
    return("Odd")
  }
}

check_even_odd(10)
check_even_odd(7)

# Example 2: Calculate factorial
factorial_calc <- function(n) {
  if (n == 0 || n == 1) {
    return(1)
  }
  result <- 1
  for (i in 2:n) {
    result <- result * i
  }
  return(result)
}

factorial_calc(5)

# Example 3: Find maximum in a vector
find_max <- function(vec) {
  max_val <- vec[1]
  for (num in vec) {
    if (num > max_val) {
      max_val <- num
    }
  }
  return(max_val)
}

find_max(c(3, 7, 1, 9, 4, 6))

# ============================================================
# SUMMARY
# ============================================================

# You learned:
# 1. If/else statements for conditional logic
# 2. For loops for iteration
# 3. While loops for repeated execution
# 4. Functions to create reusable code
# 5. Apply family functions for efficient operations

# Next: Try completing the exercises!

