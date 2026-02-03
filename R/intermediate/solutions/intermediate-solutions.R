# INTERMEDIATE LEVEL EXERCISES - SOLUTIONS

library(dplyr)
library(ggplot2)
library(tidyr)

# ============================================================
# EXERCISE 1: Data Manipulation with dplyr
# ============================================================

data(mtcars)

# 1. Filter cars with mpg > 20 and 6 or more cylinders
filtered <- mtcars %>%
  filter(mpg > 20, cyl >= 6)
print("Filtered cars:")
print(head(filtered))

# 2. Select only mpg, hp, wt columns
selected <- mtcars %>%
  select(mpg, hp, wt)
print("\nSelected columns:")
print(head(selected))

# 3. Create a new column 'hp_per_wt' that is hp divided by wt
mutated <- mtcars %>%
  mutate(hp_per_wt = hp / wt)
print("\nWith new column:")
print(head(mutated))

# 4. Arrange by mpg descending
arranged <- mtcars %>%
  arrange(desc(mpg))
print("\nArranged by mpg:")
print(head(arranged))

# 5. Group by cyl and calculate mean mpg for each group
summary_by_cyl <- mtcars %>%
  group_by(cyl) %>%
  summarize(mean_mpg = mean(mpg))
print("\nMean mpg by cyl:")
print(summary_by_cyl)

# ============================================================
# EXERCISE 2: Data Reshaping
# ============================================================

sales <- data.frame(
  store = c("A", "B", "C"),
  product = c("Apple", "Apple", "Apple"),
  jan = c(100, 150, 120),
  feb = c(110, 160, 130),
  mar = c(105, 155, 125)
)

# 1. Convert to long format
sales_long <- sales %>%
  pivot_longer(
    cols = jan:mar,
    names_to = "month",
    values_to = "sales"
  )
print("\nLong format:")
print(sales_long)

# 2. Convert back to wide
sales_wide <- sales_long %>%
  pivot_wider(
    names_from = month,
    values_from = sales
  )
print("\nBack to wide:")
print(sales_wide)

# ============================================================
# EXERCISE 3: Visualization
# ============================================================

# 1. Scatter plot of mpg vs weight
p1 <- ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point()
print(p1)

# 2. Color by cyl
p2 <- ggplot(mtcars, aes(x = wt, y = mpg, color = as.factor(cyl))) +
  geom_point()
print(p2)

# 3. Histogram of mpg
p3 <- ggplot(mtcars, aes(x = mpg)) +
  geom_histogram(bins = 20)
print(p3)

# 4. Box plot of mpg by cyl
p4 <- ggplot(mtcars, aes(x = as.factor(cyl), y = mpg)) +
  geom_boxplot()
print(p4)

# 5. Bar chart count by cyl
p5 <- ggplot(mtcars, aes(x = as.factor(cyl))) +
  geom_bar()
print(p5)

# ============================================================
# EXERCISE 4: Descriptive Statistics
# ============================================================

# 1. Mean, median, and SD of mpg
cat("\nMean mpg:", mean(mtcars$mpg))
cat("\nMedian mpg:", median(mtcars$mpg))
cat("\nSD mpg:", sd(mtcars$mpg))

# 2. Correlation between mpg and hp
cat("\n\nCorrelation mpg-hp:", cor(mtcars$mpg, mtcars$hp))

# 3. Frequency table for cyl
cat("\n\nFrequency table:")
print(table(mtcars$cyl))

# 4. Mean mpg grouped by cyl
mpg_by_cyl <- mtcars %>%
  group_by(cyl) %>%
  summarize(mean_mpg = mean(mpg))
print("\nMean mpg by cyl:")
print(mpg_by_cyl)

# 5. Car(s) with highest mpg
max_mpg <- mtcars[mtcars$mpg == max(mtcars$mpg), ]
print("\nCar(s) with highest mpg:")
print(max_mpg)

# ============================================================
# EXERCISE 5: Complex Data Manipulation
# ============================================================

complex_summary <- mtcars %>%
  group_by(cyl) %>%
  summarize(
    mean_mpg = mean(mpg),
    mean_hp = mean(hp),
    count = n(),
    sd_mpg = sd(mpg)
  )
print("\nComplex summary:")
print(complex_summary)

# ============================================================
# EXERCISE 6: Custom Function
# ============================================================

fuel_category <- function(mpg) {
  if (mpg > 22) {
    return("High")
  } else if (mpg > 15) {
    return("Medium")
  } else {
    return("Low")
  }
}

# Apply function
mtcars <- mtcars %>%
  mutate(fuel_category = sapply(mpg, fuel_category))

# Count by category
category_counts <- table(mtcars$fuel_category)
print("\nFuel category counts:")
print(category_counts)

# ============================================================
# EXERCISE 7: Multi-step Analysis
# ============================================================

automatic_summary <- mtcars %>%
  filter(am == 0) %>%
  select(mpg, hp, wt, cyl) %>%
  mutate(hp_per_wt = hp / wt) %>%
  group_by(cyl) %>%
  summarize(mean_hp_per_wt = mean(hp_per_wt))
print("\nAutomatic cars summary:")
print(automatic_summary)

# ============================================================
# EXERCISE 8: Advanced Visualization
# ============================================================

# Complex scatter plot
p6 <- ggplot(mtcars, aes(x = wt, y = mpg, color = as.factor(cyl), size = hp)) +
  geom_point(alpha = 0.6) +
  geom_smooth(method = "lm", se = FALSE) +
  labs(
    title = "Fuel Efficiency Analysis",
    subtitle = "By Weight, Cylinders, and Horsepower",
    x = "Weight (1000 lbs)",
    y = "Miles per Gallon",
    color = "Cylinders",
    size = "Horsepower"
  ) +
  theme_minimal()
print(p6)

# Faceted plot
p7 <- ggplot(mtcars, aes(x = hp, y = mpg)) +
  geom_point() +
  facet_wrap(~ cyl) +
  labs(
    title = "MPG vs Horsepower by Cylinders",
    x = "Horsepower",
    y = "Miles per Gallon"
  ) +
  theme_minimal()
print(p7)

# ============================================================
# EXERCISE 9: Diamonds Dataset
# ============================================================

data(diamonds)

# 1. Count
cat("\n\nNumber of diamonds:", nrow(diamonds))

# 2. Average carat by cut
carat_by_cut <- diamonds %>%
  group_by(cut) %>%
  summarize(mean_carat = mean(carat))
print("\nAverage carat by cut:")
print(carat_by_cut)

# 3. Histogram of price
p8 <- ggplot(diamonds, aes(x = price)) +
  geom_histogram(bins = 50) +
  labs(title = "Distribution of Diamond Prices")
print(p8)

# 4. Box plot of price by cut
p9 <- ggplot(diamonds, aes(x = cut, y = price)) +
  geom_boxplot() +
  labs(title = "Price Distribution by Cut")
print(p9)

# 5. Correlation
cat("\n\nCorrelation carat-price:", cor(diamonds$carat, diamonds$price))

# 6. Filtered data
filtered_diamonds <- diamonds %>%
  filter(cut %in% c("Premium", "Ideal"), price < 5000)
print("\n\nFiltered diamonds:")
print(head(filtered_diamonds))
cat("\nCount:", nrow(filtered_diamonds))

# ============================================================
# EXERCISE 10: Capstone Project
# ============================================================

# Exploratory Data Analysis on mtcars
cat("\n\n=== CAPSTONE: EXPLORATORY DATA ANALYSIS ===\n")

# 1. Structure
cat("\n1. Data Structure:")
str(mtcars)
cat("\nDimensions:", dim(mtcars))

# 2. Descriptive statistics
cat("\n\n2. Descriptive Statistics:")
summary(mtcars)

# 3. Correlations
cat("\n\n3. Correlation Matrix (key variables):")
cor(mtcars[, c("mpg", "hp", "wt", "disp", "cyl")])

# 4. Visualizations
print("\n4. Creating visualizations...")

# Distribution of mpg
p_cap1 <- ggplot(mtcars, aes(x = mpg)) +
  geom_histogram(bins = 15, fill = "steelblue") +
  labs(title = "Distribution of MPG", x = "MPG", y = "Frequency") +
  theme_minimal()
print(p_cap1)

# Scatter: mpg vs weight
p_cap2 <- ggplot(mtcars, aes(x = wt, y = mpg, color = as.factor(cyl))) +
  geom_point(size = 3) +
  geom_smooth(method = "lm", se = FALSE) +
  labs(title = "MPG vs Weight by Cylinders", x = "Weight", y = "MPG") +
  theme_minimal()
print(p_cap2)

# Box plot by cyl
p_cap3 <- ggplot(mtcars, aes(x = as.factor(cyl), y = mpg, fill = as.factor(cyl))) +
  geom_boxplot() +
  labs(title = "MPG by Number of Cylinders", x = "Cylinders", y = "MPG") +
  theme_minimal()
print(p_cap3)

# Correlation heatmap data
cor_matrix <- cor(mtcars[, c("mpg", "hp", "wt", "disp", "cyl", "drat", "qsec", "vs", "am")])

# 5. Grouped summary
grouped_summary <- mtcars %>%
  group_by(cyl) %>%
  summarize(
    count = n(),
    mean_mpg = round(mean(mpg), 2),
    sd_mpg = round(sd(mpg), 2),
    mean_hp = round(mean(hp), 2),
    mean_wt = round(mean(wt), 2)
  )
print("\n5. Summary by Cylinders:")
print(grouped_summary)

# 6. Insights
cat("\n\n6. KEY INSIGHTS:")
cat("\n- Cars with fewer cylinders tend to have better fuel efficiency")
cat("\n- Weight and horsepower are inversely related to mpg")
cat("\n- Cylinder count is a strong predictor of fuel consumption")

cat("\n\n✅ Analysis complete!")

