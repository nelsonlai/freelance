# INTERMEDIATE LEVEL EXERCISES
# Practice data manipulation, visualization, and statistics

library(dplyr)
library(ggplot2)
library(tidyr)

# ============================================================
# EXERCISE 1: Data Manipulation with dplyr
# ============================================================

# Load mtcars dataset
data(mtcars)

# 1. Filter cars with mpg > 20 and 6 or more cylinders
# Your code here:


# 2. Select only mpg, hp, wt columns
# Your code here:


# 3. Create a new column 'hp_per_wt' that is hp divided by wt
# Your code here:


# 4. Arrange by mpg descending
# Your code here:


# 5. Group by cyl and calculate mean mpg for each group
# Your code here:


# ============================================================
# EXERCISE 2: Data Reshaping
# ============================================================

# Create a data frame
sales <- data.frame(
  store = c("A", "B", "C"),
  product = c("Apple", "Apple", "Apple"),
  jan = c(100, 150, 120),
  feb = c(110, 160, 130),
  mar = c(105, 155, 125)
)

# 1. Convert this wide format to long format
#    (columns jan, feb, mar should become 'month' and 'sales')
# Your code here:


# 2. Convert back to wide format
# Your code here:


# ============================================================
# EXERCISE 3: Visualization
# ============================================================

# Using mtcars dataset

# 1. Create a scatter plot of mpg vs weight (wt)
# Your code here:


# 2. Color the points by number of cylinders (cyl)
# Your code here:


# 3. Create a histogram of mpg
# Your code here:


# 4. Create a box plot of mpg by cyl
# Your code here:


# 5. Create a bar chart showing count of cars by cyl
# Your code here:


# ============================================================
# EXERCISE 4: Descriptive Statistics
# ============================================================

# Using mtcars dataset

# 1. Calculate mean, median, and standard deviation of mpg
# Your code here:


# 2. Calculate correlation between mpg and hp
# Your code here:


# 3. Create a frequency table for cyl
# Your code here:


# 4. Calculate mean mpg grouped by cyl
# Your code here:


# 5. Find the car(s) with the highest mpg
# Your code here:


# ============================================================
# EXERCISE 5: Complex Data Manipulation
# ============================================================

# Use mtcars dataset

# 1. Create a data frame that shows:
#    - Mean mpg by cyl
#    - Mean hp by cyl
#    - Count of cars by cyl
#    - Standard deviation of mpg by cyl
# Your code here:


# ============================================================
# EXERCISE 6: Custom Function with dplyr
# ============================================================

# 1. Write a function that calculates fuel efficiency category:
#    "High" if mpg > 22, "Medium" if 15 < mpg <= 22, "Low" otherwise
# 2. Apply this function to mtcars
# 3. Count cars in each category
# Your code here:


# ============================================================
# EXERCISE 7: Multi-step Analysis
# ============================================================

# Using mtcars

# 1. Filter cars with automatic transmission (am == 0)
# 2. Select mpg, hp, wt, cyl
# 3. Create hp_per_wt column
# 4. Find mean hp_per_wt by cyl
# Your code here:


# ============================================================
# EXERCISE 8: Advanced Visualization
# ============================================================

# 1. Create a scatter plot of mpg vs wt, colored by cyl, sized by hp
# 2. Add a smooth trend line
# 3. Add meaningful title and axis labels
# 4. Use a professional theme
# Your code here:


# 2. Create a faceted plot showing mpg vs hp for different cyl values
# Your code here:


# ============================================================
# EXERCISE 9: Real Dataset Analysis
# ============================================================

# Load the diamonds dataset (from ggplot2)
data(diamonds)

# 1. How many diamonds are there in the dataset?
# Your code here:


# 2. What's the average carat by cut?
# Your code here:


# 3. Create a histogram of price
# Your code here:


# 4. Create a box plot of price by cut
# Your code here:


# 5. Find the correlation between carat and price
# Your code here:


# 6. Filter for diamonds with cut = "Premium" or "Ideal"
#    and price < 5000
# Your code here:


# ============================================================
# EXERCISE 10: Capstone Project
# ============================================================

# Perform a complete exploratory data analysis on mtcars:
# 1. Load and explore the data structure
# 2. Calculate descriptive statistics
# 3. Identify any correlations
# 4. Create at least 5 different visualizations
# 5. Group by cyl and summarize key statistics
# 6. Draw insights from your analysis
# Your code here:


# ============================================================
# END OF EXERCISES
# ============================================================

# Check solutions in: ../solutions/intermediate-solutions.R

