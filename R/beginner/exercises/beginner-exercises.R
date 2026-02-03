# BEGINNER LEVEL EXERCISES
# Try to solve these exercises on your own before checking solutions!

# ============================================================
# EXERCISE 1: Working with Variables and Basic Operations
# ============================================================

# 1. Create a variable called 'age' with your age as its value
# Your code here:
age <- 30


# 2. Calculate your age in days (assuming 365 days per year)
# Your code here:
age_in_days <- age * 365

# print result (example)
age_in_days


# 3. Create a variable with your name
# Your code here:
my_name <- "Alice"
my_name


# ============================================================
# EXERCISE 2: Vectors
# ============================================================

# 1. Create a numeric vector containing the numbers 1 to 20
# Your code here:
num_vec <- 1:20
num_vec


# 2. Create a character vector with 5 fruit names
# Your code here:
fruits <- c("apple", "banana", "orange", "grape", "mango")
fruits


# 3. Extract the first, third, and fifth elements from your numeric vector
# Your code here:
subset_odd <- num_vec[c(1, 3, 5)]
subset_odd


# ============================================================
# EXERCISE 3: Data Frames
# ============================================================

# 1. Create a data frame called 'students' with the following columns:
#    - name: "Alice", "Bob", "Charlie"
#    - age: 20, 22, 21
#    - score: 85, 92, 78
# Your code here:
students <- data.frame(
	name = c("Alice", "Bob", "Charlie"),
	age = c(20, 22, 21),
	score = c(85, 92, 78),
	stringsAsFactors = FALSE
)
students


# 2. Extract the 'score' column
# Your code here:
scores <- students$score
scores


# 3. Find the average score
# Your code here:
avg_score <- mean(scores)
avg_score


# ============================================================
# EXERCISE 4: If/Else Statements
# ============================================================

# 1. Write a function that checks if a number is positive
#    Return "Positive" if > 0, "Negative" if < 0, "Zero" if == 0
# Your code here:
check_number <- function(x) {
	if (!is.numeric(x)) stop("x must be numeric")
	if (x > 0) {
		return("Positive")
	} else if (x < 0) {
		return("Negative")
	} else {
		return("Zero")
	}
}



# 2. Test your function with: -5, 0, and 10
# Your code here:
check_number(-5)
check_number(0)
check_number(10)


# ============================================================
# EXERCISE 5: For Loops
# ============================================================

# 1. Write a for loop that prints all even numbers from 2 to 20
# Your code here:
for (i in seq(2, 20, by = 2)) {
	print(i)
}


# 2. Write a for loop that calculates the sum of numbers 1 to 100
# Your code here:
sum_1_100 <- 0
for (i in 1:100) {
	sum_1_100 <- sum_1_100 + i
}
sum_1_100


# ============================================================
# EXERCISE 6: Functions
# ============================================================

# 1. Write a function called 'calculate_area' that calculates 
#    the area of a rectangle (length × width)
# Your code here:
calculate_area <- function(length, width) {
	length * width
}


# 2. Test your function with length=5 and width=3
# Your code here:
calculate_area(5, 3)


# 3. Write a function called 'letter_grade' that takes a score
#    and returns: "A" if >=90, "B" if >=80, "C" if >=70, "F" otherwise
# Your code here:
letter_grade <- function(score) {
	if (!is.numeric(score)) stop("score must be numeric")
	if (score >= 90) {
		"A"
	} else if (score >= 80) {
		"B"
	} else if (score >= 70) {
		"C"
	} else {
		"F"
	}
}

# example
letter_grade(85)


# ============================================================
# EXERCISE 7: Data Manipulation
# ============================================================

# Given this vector:
numbers <- c(15, 23, 8, 45, 12, 33, 20, 18)

# 1. Find the maximum value
# Your code here:
max_value <- max(numbers)
max_value


# 2. Find the minimum value
# Your code here:
min_value <- min(numbers)
min_value


# 3. Calculate the mean
# Your code here:
mean_value <- mean(numbers)
mean_value


# 4. Create a new vector with only values greater than 20
# Your code here:
greater_than_20 <- numbers[numbers > 20]
greater_than_20


# ============================================================
# EXERCISE 8: Character Vectors
# ============================================================

# 1. Create a character vector with 5 city names
# Your code here:
cities <- c("London", "Paris", "Tokyo", "New York", "Sydney")
cities


# 2. Find the length of each city name
# Your code here:
city_name_lengths <- nchar(cities)
city_name_lengths


# 3. Convert all city names to uppercase
# Your code here:
cities_upper <- toupper(cities)
cities_upper


# ============================================================
# EXERCISE 9: Lists
# ============================================================

# 1. Create a list with the following elements:
#    - name: your name
#    - age: your age
#    - favorite_colors: c("blue", "green")
#    - scores: c(85, 90, 78)
# Your code here:
person <- list(
	name = "Alice",
	age = 30,
	favorite_colors = c("blue", "green"),
	scores = c(85, 90, 78)
)
person


# 2. Extract the 'scores' element
# Your code here:
person_scores <- person$scores
person_scores


# 3. Calculate the average of the scores
# Your code here:
person_avg_score <- mean(person_scores)
person_avg_score


# ============================================================
# EXERCISE 10: Putting it all Together
# ============================================================

# Create a student grading system:
# 1. Create a data frame with at least 5 students' names, scores, and grades
# 2. Write a function that converts scores to grades (A, B, C, D, F)
# 3. Apply this function to create a 'grade' column
# 4. Find the student(s) with the highest score
# 5. Calculate class average
# Your code here:
class_students <- data.frame(
	name = c("Anna", "Ben", "Chloe", "David", "Eva"),
	score = c(95, 82, 76, 64, 88),
	stringsAsFactors = FALSE
)

score_to_grade <- function(x) {
	ifelse(x >= 90, "A",
				 ifelse(x >= 80, "B",
								ifelse(x >= 70, "C",
											 ifelse(x >= 60, "D", "F"))))
}

class_students$grade <- score_to_grade(class_students$score)
class_students

# highest scoring student(s)
top_students <- class_students[class_students$score == max(class_students$score), ]
top_students

# class average
class_avg <- mean(class_students$score)
class_avg


# ============================================================
# END OF EXERCISES
# ============================================================

# Check your solutions in: ../solutions/beginner-solutions.R

