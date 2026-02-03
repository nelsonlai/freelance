# Data Manipulation with dplyr
# This script demonstrates data manipulation using the dplyr package

# ============================================================
# LOAD PACKAGE
# ============================================================
library(dplyr)

# ============================================================
# THE FIVE KEY VERBS
# ============================================================
# 1. filter() - keep rows that match conditions
# 2. select() - pick variables (columns)
# 3. mutate() - create new variables
# 4. arrange() - sort rows
# 5. summarize() - collapse to summary statistics

# ============================================================
# FILTER ROWS WITH filter()
# ============================================================

# Load built-in dataset
data("mtcars")

# Filter cars with mpg greater than 20
mtcars %>%
  filter(mpg > 20)

# Multiple conditions
mtcars %>%
  filter(mpg > 20, cyl == 4)

# Using 'or' operator
mtcars %>%
  filter(mpg > 30 | hp < 100)

# ============================================================
# SELECT COLUMNS WITH select()
# ============================================================

# Select specific columns
mtcars %>%
  select(mpg, hp, wt)

# Select a range of columns
mtcars %>%
  select(mpg:wt)

# Select columns to exclude
mtcars %>%
  select(-mpg, -hp)

# Select columns by name pattern
mtcars %>%
  select(starts_with("m"))

# ============================================================
# CREATE VARIABLES WITH mutate()
# ============================================================

mtcars %>%
  mutate(
    hp_per_cyl = hp / cyl,
    weight_kg = wt * 453.592
  ) %>%
  head()

# Use ifelse() in mutate
mtcars %>%
  mutate(
    fuel_category = ifelse(mpg > 20, "Efficient", "Less Efficient")
  ) %>%
  select(mpg, fuel_category)

# ============================================================
# ARRANGE ROWS WITH arrange()
# ============================================================

# Sort by mpg (ascending)
mtcars %>%
  arrange(mpg) %>%
  head()

# Sort by mpg (descending)
mtcars %>%
  arrange(desc(mpg)) %>%
  head()

# Sort by multiple columns
mtcars %>%
  arrange(desc(mpg), desc(hp)) %>%
  head()

# ============================================================
# SUMMARIZE DATA WITH summarize()
# ============================================================

mtcars %>%
  summarize(
    mean_mpg = mean(mpg),
    median_mpg = median(mpg),
    max_hp = max(hp),
    count = n()
  )

# ============================================================
# GROUP OPERATIONS WITH group_by()
# ============================================================

mtcars %>%
  group_by(cyl) %>%
  summarize(
    mean_mpg = mean(mpg),
    count = n()
  )

# ============================================================
# THE PIPE OPERATOR %>%
# ============================================================

# Without pipe (nested functions)
arrange(filter(mtcars, mpg > 20), desc(hp))

# With pipe (readable!)
mtcars %>%
  filter(mpg > 20) %>%
  arrange(desc(hp))

# Complex operation
mtcars %>%
  filter(mpg > 20) %>%
  select(mpg, hp, wt) %>%
  mutate(hp_per_weight = hp / wt) %>%
  arrange(desc(hp_per_weight)) %>%
  head()

# ============================================================
# COMBINING MULTIPLE OPERATIONS
# ============================================================

result <- mtcars %>%
  filter(cyl == 4 | cyl == 6) %>%
  select(mpg, hp, cyl) %>%
  mutate(
    efficient = mpg > 22,
    powerful = hp > 100
  ) %>%
  arrange(desc(mpg))

head(result)

# ============================================================
# ADDITIONAL USEFUL FUNCTIONS
# ============================================================

# distinct() - get unique values
mtcars %>%
  distinct(cyl)

# rename() - rename columns
mtcars %>%
  rename(horsepower = hp) %>%
  head()

# slice() - select rows by position
mtcars %>%
  slice(1:5)

mtcars %>%
  slice_max(mpg, n = 5)

mtcars %>%
  slice_min(mpg, n = 5)

# ============================================================
# PRACTICE EXERCISE
# ============================================================

# Exercise: From mtcars data
# 1. Filter cars with 4 or 6 cylinders
# 2. Select mpg, cyl, hp, wt
# 3. Create a variable: hp_per_weight
# 4. Find cars with hp_per_weight > 50
# 5. Arrange by hp_per_weight descending

# Your solution here:
exercise_result <- mtcars %>%
  filter(cyl == 4 | cyl == 6) %>%
  select(mpg, cyl, hp, wt) %>%
  mutate(hp_per_weight = hp / wt) %>%
  filter(hp_per_weight > 50) %>%
  arrange(desc(hp_per_weight))

head(exercise_result)

# ============================================================
# SUMMARY
# ============================================================

# You learned:
# - How to filter rows with filter()
# - How to select columns with select()
# - How to create new variables with mutate()
# - How to sort with arrange()
# - How to summarize with summarize()
# - How to group operations with group_by()
# - How to chain operations with %>%
