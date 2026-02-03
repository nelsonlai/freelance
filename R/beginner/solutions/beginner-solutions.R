# BEGINNER LEVEL EXERCISES - SOLUTIONS
# Compare your solutions with these worked examples

# ============================================================
# EXERCISE 1: Working with Variables and Basic Operations
# ============================================================

# 1. Create a variable called 'age' with your age as its value
age <- 25

# 2. Calculate your age in days (assuming 365 days per year)
age_in_days <- age * 365
print(age_in_days)

# 3. Create a variable with your name
my_name <- "Alice"

# ============================================================
# EXERCISE 2: Vectors
# ============================================================

# 1. Create a numeric vector containing the numbers 1 to 20
num_vec <- 1:20
# Alternative: num_vec <- c(1, 2, 3, ... , 20)

# 2. Create a character vector with 5 fruit names
fruits <- c("apple", "banana", "orange", "grape", "kiwi")

# 3. Extract the first, third, and fifth elements
num_vec[c(1, 3, 5)]

# ============================================================
# EXERCISE 3: Data Frames
# ============================================================

# 1. Create a data frame called 'students'
students <- data.frame(
  name = c("Alice", "Bob", "Charlie"),
  age = c(20, 22, 21),
  score = c(85, 92, 78)
)

# 2. Extract the 'score' column
students$score

# 3. Find the average score
mean(students$score)

# ============================================================
# EXERCISE 4: If/Else Statements
# ============================================================

# 1. Write a function that checks if a number is positive
check_number <- function(n) {
  if (n > 0) {
    return("Positive")
  } else if (n < 0) {
    return("Negative")
  } else {
    return("Zero")
  }
}

# 2. Test your function
check_number(-5)
check_number(0)
check_number(10)

# ============================================================
# EXERCISE 5: For Loops
# ============================================================

# 1. Write a for loop that prints all even numbers from 2 to 20
for (i in 2:20) {
  if (i %% 2 == 0) {
    print(i)
  }
}

# 2. Write a for loop that calculates the sum of numbers 1 to 100
total <- 0
for (i in 1:100) {
  total <- total + i
}
print(total)

# Or simply:
sum(1:100)

# ============================================================
# EXERCISE 6: Functions
# ============================================================

# 1. Write a function called 'calculate_area'
calculate_area <- function(length, width) {
  area <- length * width
  return(area)
}

# 2. Test your function
calculate_area(5, 3)

# 3. Write a function called 'letter_grade'
letter_grade <- function(score) {
  if (score >= 90) {
    return("A")
  } else if (score >= 80) {
    return("B")
  } else if (score >= 70) {
    return("C")
  } else {
    return("F")
  }
}

# ============================================================
# EXERCISE 7: Data Manipulation
# ============================================================

# Given this vector:
numbers <- c(15, 23, 8, 45, 12, 33, 20, 18)

# 1. Find the maximum value
max(numbers)

# 2. Find the minimum value
min(numbers)

# 3. Calculate the mean
mean(numbers)

# 4. Create a new vector with only values greater than 20
numbers[numbers > 20]

# ============================================================
# EXERCISE 8: Character Vectors
# ============================================================

# 1. Create a character vector with 5 city names
cities <- c("London", "Paris", "Tokyo", "New York", "Sydney")

# 2. Find the length of each city name
nchar(cities)

# 3. Convert all city names to uppercase
toupper(cities)

# ============================================================
# EXERCISE 9: Lists
# ============================================================

# 1. Create a list
my_info <- list(
  name = "Alice",
  age = 25,
  favorite_colors = c("blue", "green"),
  scores = c(85, 90, 78)
)

# 2. Extract the 'scores' element
my_info$scores

# 3. Calculate the average of the scores
mean(my_info$scores)

# ============================================================
# EXERCISE 10: Putting it all Together
# ============================================================

# 1. Create a data frame with at least 5 students
students <- data.frame(
  name = c("Alice", "Bob", "Charlie", "Diana", "Eve"),
  score = c(95, 87, 72, 88, 91)
)

# 2. Write a function that converts scores to grades
score_to_grade <- function(score) {
  if (score >= 90) return("A")
  else if (score >= 80) return("B")
  else if (score >= 70) return("C")
  else if (score >= 60) return("D")
  else return("F")
}

# 3. Apply function to create a 'grade' column
students$grade <- sapply(students$score, score_to_grade)

# 4. Find the student(s) with the highest score
students[students$score == max(students$score), ]

# 5. Calculate class average
mean(students$score)

# Display the final data frame
print(students)

