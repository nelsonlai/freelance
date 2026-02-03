# Data Reshaping with tidyr
# This script demonstrates reshaping data from wide to long format and vice versa

library(tidyr)
library(dplyr)

# ============================================================
# 1. LONG vs WIDE FORMAT
# ============================================================

# Wide format: Each column represents a different variable
wide_data <- data.frame(
  name = c("Alice", "Bob", "Charlie"),
  jan = c(100, 120, 90),
  feb = c(110, 130, 95),
  mar = c(105, 125, 92)
)
print("Wide Format:")
print(wide_data)

# Long format: More suitable for analysis
# We'll convert wide to long using pivot_longer()

# ============================================================
# 2. WIDE TO LONG: pivot_longer()
# ============================================================

# Convert wide to long format
long_data <- wide_data %>%
  pivot_longer(
    cols = jan:mar,           # columns to convert
    names_to = "month",        # new column name for variable names
    values_to = "sales"        # new column name for values
  )
print("\nLong Format:")
print(long_data)

# With more options
long_data2 <- wide_data %>%
  pivot_longer(
    cols = c(jan, feb, mar),
    names_to = "month",
    values_to = "sales",
    names_prefix = "",        # Remove any prefix
    values_drop_na = FALSE    # Keep NA values
  )

# ============================================================
# 3. LONG TO WIDE: pivot_wider()
# ============================================================

# Convert long back to wide
wide_again <- long_data %>%
  pivot_wider(
    names_from = month,      # column to create column names from
    values_from = sales      # column containing values
  )
print("\nBack to Wide Format:")
print(wide_again)

# ============================================================
# 4. SEPARATE COLUMNS: separate()
# ============================================================

# Create data with combined columns
combined_data <- data.frame(
  id = 1:3,
  name_age = c("Alice_25", "Bob_30", "Charlie_35")
)

# Separate the columns
separated_data <- combined_data %>%
  separate(
    name_age,
    into = c("name", "age"),
    sep = "_"
  )
print("\nSeparated Data:")
print(separated_data)

# Convert age to numeric
separated_data <- separated_data %>%
  mutate(age = as.numeric(age))

# ============================================================
# 5. UNITE COLUMNS: unite()
# ============================================================

# Unite columns together
united_data <- separated_data %>%
  unite(
    "name_age",
    name, age,
    sep = "_"
  )
print("\nUnited Data:")
print(united_data)

# ============================================================
# 6. COMPLEX EXAMPLE: Sales Data
# ============================================================

# Create more complex wide data
sales_wide <- data.frame(
  store = c("Store A", "Store B", "Store C"),
  product = c("Apple", "Apple", "Apple"),
  q1_2020 = c(100, 150, 120),
  q2_2020 = c(110, 160, 130),
  q3_2020 = c(105, 155, 125),
  q4_2020 = c(115, 165, 135),
  q1_2021 = c(120, 170, 140),
  q2_2021 = c(125, 175, 145)
)

print("\nOriginal Wide Data:")
print(sales_wide)

# Convert to long format
sales_long <- sales_wide %>%
  pivot_longer(
    cols = starts_with("q"),
    names_to = "quarter_year",
    values_to = "sales"
  )
print("\nLong Format:")
print(head(sales_long))

# Separate quarter and year
sales_long <- sales_long %>%
  separate(
    quarter_year,
    into = c("quarter", "year"),
    sep = "_"
  )
print("\nWith Separated Quarter and Year:")
print(head(sales_long))

# ============================================================
# 7. HANDLING MISSING VALUES
# ============================================================

# Data with missing values
missing_data <- data.frame(
  name = c("Alice", "Bob", "Charlie"),
  test1 = c(85, NA, 92),
  test2 = c(78, 88, NA),
  test3 = c(90, 85, 87)
)
print("\nData with Missing Values:")
print(missing_data)

# Convert to long and handle NAs
missing_long <- missing_data %>%
  pivot_longer(
    cols = test1:test3,
    names_to = "test",
    values_to = "score"
  )
print("\nLong Format with NAs:")
print(missing_long)

# Drop NA values
missing_long_clean <- missing_long %>%
  drop_na()
print("\nWithout NAs:")
print(missing_long_clean)

# ============================================================
# 8. PRACTICAL EXAMPLE: Student Grades
# ============================================================

# Student grades in wide format
grades_wide <- data.frame(
  student = c("Alice", "Bob", "Charlie"),
  math = c(85, 90, 78),
  english = c(88, 82, 92),
  science = c(90, 85, 87)
)
print("\nStudent Grades (Wide):")
print(grades_wide)

# Convert to long format for analysis
grades_long <- grades_wide %>%
  pivot_longer(
    cols = c(math, english, science),
    names_to = "subject",
    values_to = "grade"
  )
print("\nStudent Grades (Long):")
print(grades_long)

# Calculate average per subject
grades_long %>%
  group_by(subject) %>%
  summarize(avg_grade = mean(grade))

# Calculate average per student
grades_long %>%
  group_by(student) %>%
  summarize(avg_grade = mean(grade))

# ============================================================
# SUMMARY
# ============================================================

# Key functions learned:
# 1. pivot_longer() - convert wide to long (rows)
# 2. pivot_wider() - convert long to wide (columns)
# 3. separate() - split one column into multiple
# 4. unite() - combine multiple columns into one
# 5. drop_na() - remove rows with missing values

# When to use each format:
# - Wide format: Good for human readability, Excel-like tables
# - Long format: Better for analysis, plotting, statistical operations

# Next: Visualization with ggplot2!

