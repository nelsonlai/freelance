# Descriptive Statistics in R
# This script demonstrates calculating summary statistics and descriptive analyses

library(dplyr)

# ============================================================
# 1. BASIC SUMMARY STATISTICS
# ============================================================

# Create sample data
set.seed(123)
ages <- rnorm(100, mean = 30, sd = 5)
scores <- c(85, 90, 78, 92, 88, 95, 82, 87, 91, 85)

# Mean (average)
mean(ages)
mean(scores)

# Median (middle value)
median(ages)
median(scores)

# Mode (most frequent - not built-in, need to create function)
calculate_mode <- function(x) {
  unique_x <- unique(x)
  unique_x[which.max(tabulate(match(x, unique_x)))]
}

calculate_mode(scores)

# Quartiles and percentiles
quantile(ages)
quantile(scores, 0.25)  # 25th percentile
quantile(scores, 0.75)  # 75th percentile

# Range
range(scores)
min(scores)
max(scores)

# Interquartile Range (IQR)
IQR(scores)

# ============================================================
# 2. MEASURES OF VARIABILITY
# ============================================================

# Variance
var(scores)

# Standard deviation
sd(scores)

# Standard error of the mean
sd(scores) / sqrt(length(scores))

# Coefficient of variation
cv <- sd(scores) / mean(scores)

# ============================================================
# 3. COMPREHENSIVE SUMMARY
# ============================================================

# Using base R summary()
summary(mtcars)

# Custom summary function
custom_summary <- function(x) {
  data.frame(
    mean = mean(x),
    median = median(x),
    sd = sd(x),
    min = min(x),
    max = max(x),
    IQR = IQR(x),
    n = length(x)
  )
}

# Apply to data
mtcars %>%
  select(mpg) %>%
  summarise_all(custom_summary)

# ============================================================
# 4. CORRELATION AND COVARIANCE
# ============================================================

# Pearson correlation
cor(mtcars$mpg, mtcars$hp)
cor(mtcars$mpg, mtcars$wt)

# Correlation matrix
cor(mtcars[, c("mpg", "hp", "wt", "disp")])

# Covariance
cov(mtcars$mpg, mtcars$hp)

# Covariance matrix
cov(mtcars[, c("mpg", "hp", "wt")])

# ============================================================
# 5. FREQUENCY TABLES
# ============================================================

# One-way frequency table
table(mtcars$cyl)

# Convert to proportions
prop.table(table(mtcars$cyl))

# Two-way contingency table
table(mtcars$cyl, mtcars$vs)

# With proportions
prop.table(table(mtcars$cyl, mtcars$vs), margin = 1)

# ============================================================
# 6. USING DPLYR FOR GROUPED STATISTICS
# ============================================================

# Summary by group
mtcars %>%
  group_by(cyl) %>%
  summarize(
    mean_mpg = mean(mpg),
    median_mpg = median(mpg),
    sd_mpg = sd(mpg),
    min_mpg = min(mpg),
    max_mpg = max(mpg),
    count = n()
  )

# Multiple variables by group
mtcars %>%
  group_by(cyl) %>%
  summarize(
    across(c(mpg, hp, wt),
           list(mean = mean, sd = sd),
           .names = "{.col}_{.fn}")
  )

# ============================================================
# 7. DESCRIPTIVE STATISTICS BY GROUPS
# ============================================================

# Create more complex summary
mtcars %>%
  group_by(cyl, am) %>%
  summarize(
    n = n(),
    mean_mpg = round(mean(mpg), 2),
    sd_mpg = round(sd(mpg), 2),
    se_mpg = round(sd(mpg) / sqrt(n()), 2),
    .groups = "drop"
  )

# ============================================================
# 8. HANDLING MISSING VALUES
# ============================================================

# Create data with missing values
data_with_na <- c(1, 2, 3, NA, 5, 6, NA, 8)

# Check for NAs
is.na(data_with_na)

# Count NAs
sum(is.na(data_with_na))

# Mean with NA handling
mean(data_with_na, na.rm = TRUE)

# ============================================================
# 9. OUTLIER DETECTION
# ============================================================

# Calculate z-scores
z_scores <- (mtcars$mpg - mean(mtcars$mpg)) / sd(mtcars$mpg)

# Identify outliers (|z| > 3)
outliers <- which(abs(z_scores) > 3)

# IQR method
Q1 <- quantile(mtcars$mpg, 0.25)
Q3 <- quantile(mtcars$mpg, 0.75)
IQR <- Q3 - Q1
lower <- Q1 - 1.5 * IQR
upper <- Q3 + 1.5 * IQR

outliers_iqr <- which(mtcars$mpg < lower | mtcars$mpg > upper)

# ============================================================
# 10. NORMALITY TESTS
# ============================================================

# Shapiro-Wilk test (good for sample sizes between 3 and 5000)
shapiro.test(scores)

# Robust normality testing helper
# - Uses Shapiro-Wilk when sample size <= 5000
# - Falls back to Lilliefors (nortest::lillie.test) for large samples
# - Avoids using ks.test against a theoretical distribution directly for one-sample
#   because ks.test issues a warning when ties are present (mtcars$mpg contains ties).
normality_test <- function(x) {
  if (!is.numeric(x)) stop("x must be numeric")
  n <- length(x)
  if (n < 3) stop("Need at least 3 observations for normality tests")

  if (n <= 5000) {
    message("Using Shapiro-Wilk test (n <= 5000)")
    return(shapiro.test(x))
  } else {
    if (!requireNamespace("nortest", quietly = TRUE)) {
      stop("Package 'nortest' required for large-sample normality tests. Install with install.packages('nortest').")
    }
    message("Using Lilliefors test via nortest::lillie.test() for large samples")
    return(nortest::lillie.test(x))
  }
}

# Run the normality test on mtcars$mpg using the helper
normality_test(mtcars$mpg)

# ============================================================
# 11. PRACTICAL EXAMPLE: STUDENT PERFORMANCE
# ============================================================

# Create student data
students <- data.frame(
  student_id = 1:50,
  subject = sample(c("Math", "Science", "English"), 50, replace = TRUE),
  score = rnorm(50, mean = 75, sd = 10),
  grade = sample(c("Freshman", "Sophomore", "Junior", "Senior"), 
                 50, replace = TRUE)
)

# Overall statistics
students %>%
  summarize(
    count = n(),
    mean_score = round(mean(score), 2),
    median_score = round(median(score), 2),
    sd_score = round(sd(score), 2)
  )

# By subject
students %>%
  group_by(subject) %>%
  summarize(
    count = n(),
    mean_score = round(mean(score), 2),
    sd_score = round(sd(score), 2)
  )

# By grade
students %>%
  group_by(grade) %>%
  summarize(
    count = n(),
    mean_score = round(mean(score), 2),
    sd_score = round(sd(score), 2)
  )

# ============================================================
# SUMMARY
# ============================================================

# You learned:
# 1. Measures of central tendency (mean, median, mode)
# 2. Measures of variability (variance, SD, IQR, range)
# 3. Correlation and covariance
# 4. Frequency tables and contingency tables
# 5. Grouped summaries with dplyr
# 6. Handling missing values
# 7. Outlier detection
# 8. Normality testing

# Next: Advanced statistical analysis!

