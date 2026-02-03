# ADVANCED LEVEL EXERCISES
# Statistical analysis and modeling exercises

library(dplyr)
library(ggplot2)
library(car)
library(lmtest)

# ============================================================
# EXERCISE 1: Probability Distributions
# ============================================================

# 1. Generate 1000 random numbers from a normal distribution
#    with mean=50, sd=10. Create a histogram.
# Your code here:


# 2. Calculate the 95th percentile of a standard normal distribution
# Your code here:


# 3. If X ~ Normal(30, 5), calculate P(25 < X < 35)
# Your code here:


# 4. Generate 20 random numbers from a binomial distribution
#    with n=10 and p=0.7
# Your code here:


# ============================================================
# EXERCISE 2: Hypothesis Testing
# ============================================================

data(mtcars)

# 1. Test if mean mpg is significantly different from 22
#    (use one-sample t-test)
# Your code here:


# 2. Test if automatic and manual cars have different mpg
#    (use two-sample t-test)
# Your code here:


# 3. Check assumptions for the two-sample t-test
#    (normality, equal variances)
# Your code here:


# 4. If normality is violated, use appropriate non-parametric test
# Your code here:


# 5. Perform ANOVA to test if mpg differs by cylinder count
#    Include post-hoc tests
# Your code here:


# ============================================================
# EXERCISE 3: Linear Regression
# ============================================================

# Use mtcars dataset

# 1. Fit a simple linear regression: mpg ~ weight
#    Interpret the coefficients and p-values
# Your code here:


# 2. Create a scatter plot with regression line
# Your code here:


# 3. Check regression assumptions
#    (linearity, independence, homoscedasticity, normality)
# Your code here:


# 4. Fit multiple regression: mpg ~ weight + hp + cylinders
#    Compare with simple regression
# Your code here:


# 5. Identify influential points using Cook's distance
# Your code here:


# ============================================================
# EXERCISE 4: ANOVA Analysis
# ============================================================

# Create a dataset for ANOVA
set.seed(123)
anova_data <- data.frame(
  group = factor(rep(c("A", "B", "C"), each = 20)),
  value = c(rnorm(20, 75, 10),
            rnorm(20, 80, 10),
            rnorm(20, 82, 10))
)

# 1. Perform one-way ANOVA
# Your code here:


# 2. Check ANOVA assumptions
#    (normality, homogeneity of variances)
# Your code here:


# 3. Perform post-hoc tests
# Your code here:


# 4. Calculate effect size (eta-squared)
# Your code here:


# 5. Create visualizations (box plot, means plot with error bars)
# Your code here:


# ============================================================
# EXERCISE 5: Two-Way ANOVA
# ============================================================

# Create two-way ANOVA dataset
set.seed(123)
twoway_data <- data.frame(
  factor1 = factor(rep(c("Low", "High"), each = 30)),
  factor2 = factor(rep(rep(c("A", "B", "C"), each = 10), times = 2)),
  response = rnorm(60, 70, 10) + 
             c(0, 5)[rep(1:2, each = 30)] +
             c(0, 3, 6)[rep(1:3, 10, times = 2)]
)

# 1. Perform two-way ANOVA with interaction
# Your code here:


# 2. Check for interaction effect
# Your code here:


# 3. Perform simple effects analysis if interaction is significant
# Your code here:


# 4. Create interaction plot
# Your code here:


# 5. Calculate effect sizes for main effects and interaction
# Your code here:


# ============================================================
# EXERCISE 6: Model Selection
# ============================================================

data(mtcars)

# 1. Fit a full model with all predictors
# Your code here:


# 2. Use stepwise regression to select the best model
# Your code here:


# 3. Compare models using AIC and BIC
# Your code here:


# 4. Calculate cross-validation error for your selected model
# Your code here:


# 5. Identify which variables are most important
# Your code here:


# ============================================================
# EXERCISE 7: Regression Diagnostics
# ============================================================

# 1. Fit a regression model: mpg ~ wt + hp
# Your code here:


# 2. Create all diagnostic plots
# Your code here:


# 3. Identify outliers and influential points
# Your code here:


# 4. Test for multicollinearity (VIF)
# Your code here:


# 5. Check for autocorrelation (Durbin-Watson)
# Your code here:


# ============================================================
# EXERCISE 8: Case Study: Complete Analysis
# ============================================================

# Scenario: A pharmaceutical company wants to test if three
# different drugs (A, B, C) have different effects on blood pressure.
# They also want to see if the effect differs by gender.

set.seed(123)
pharma_data <- data.frame(
  drug = factor(rep(c("A", "B", "C"), each = 30)),
  gender = factor(rep(rep(c("M", "F"), each = 15), times = 3)),
  bp_before = rnorm(90, 140, 15),
  bp_after = NA
)

# Simulate drug effects
pharma_data$bp_after <- pharma_data$bp_before - 
                        c(10, 15, 12)[as.numeric(pharma_data$drug)] +
                        c(0, -2)[as.numeric(pharma_data$gender)] +
                        rnorm(90, 0, 5)

# 1. Calculate change scores
# Your code here:


# 2. Perform two-way ANOVA: change ~ drug * gender
# Your code here:


# 3. Check assumptions
# Your code here:


# 4. Perform post-hoc tests if needed
# Your code here:


# 5. Create publication-quality visualizations
# Your code here:


# 6. Write a statistical report with conclusions
# Your code here:


# ============================================================
# EXERCISE 9: Advanced Regression Techniques
# ============================================================

# 1. Fit a polynomial regression: mpg ~ wt + wt^2
# Your code here:


# 2. Compare polynomial vs linear regression
# Your code here:


# 3. Fit a regression with interaction: mpg ~ hp * wt
# Your code here:


# 4. Visualize the interaction effect
# Your code here:


# ============================================================
# EXERCISE 10: Capstone Project
# ============================================================

# Conduct a complete statistical analysis on mtcars dataset:

# 1. Formulate research questions
# Your code here (comments):


# 2. Perform exploratory data analysis
# Your code here:


# 3. Conduct appropriate statistical tests
# Your code here:


# 4. Build regression models
# Your code here:


# 5. Check all assumptions
# Your code here:


# 6. Perform model selection
# Your code here:


# 7. Create comprehensive visualizations
# Your code here:


# 8. Write a complete statistical report with:
#    - Introduction and research questions
#    - Methods
#    - Results (with tables and figures)
#    - Conclusions
#    - Interpretations and limitations
# Your code here:


# ============================================================
# END OF EXERCISES
# ============================================================

# Check solutions in: ../solutions/advanced-solutions.R

