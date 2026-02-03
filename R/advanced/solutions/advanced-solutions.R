# ADVANCED LEVEL EXERCISES - SOLUTIONS

library(dplyr)
library(ggplot2)
library(car)
library(lmtest)
library(multcomp)

# ============================================================
# EXERCISE 1: Probability Distributions
# ============================================================

# 1. Generate random numbers from normal distribution
set.seed(123)
random_norm <- rnorm(1000, mean = 50, sd = 10)
hist(random_norm, main = "Normal Distribution",
     xlab = "Value", breaks = 30)

# 2. 95th percentile of standard normal
cat("95th percentile:", qnorm(0.95), "\n")

# 3. Probability calculation
prob <- pnorm(35, mean = 30, sd = 5) - pnorm(25, mean = 30, sd = 5)
cat("P(25 < X < 35):", prob, "\n")

# 4. Binomial random numbers
random_binom <- rbinom(20, size = 10, prob = 0.7)
cat("Binomial random numbers:", random_binom, "\n")

# ============================================================
# EXERCISE 2: Hypothesis Testing
# ============================================================

data(mtcars)

# 1. One-sample t-test
t.test(mtcars$mpg, mu = 22)

# 2. Two-sample t-test
automatic <- mtcars$mpg[mtcars$am == 0]
manual <- mtcars$mpg[mtcars$am == 1]
t.test(automatic, manual)

# 3. Check assumptions
shapiro.test(automatic)
shapiro.test(manual)
var.test(automatic, manual)

# 4. Non-parametric test
wilcox.test(automatic, manual)

# 5. ANOVA
fit_anova <- aov(mpg ~ cyl, data = mtcars)
summary(fit_anova)
TukeyHSD(fit_anova)

# ============================================================
# EXERCISE 3: Linear Regression
# ============================================================

# 1. Simple regression
model1 <- lm(mpg ~ wt, data = mtcars)
summary(model1)

# Interpretation:
# Intercept: When wt=0, predicted mpg=37.3
# Slope: Each increase of 1 unit in wt decreases mpg by 5.34
# Both coefficients are significant (p < 0.001)
# R² = 0.753 (75.3% of variance explained)

# 2. Visualization
ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  geom_smooth(method = "lm", se = TRUE) +
  labs(title = "Simple Linear Regression: MPG vs Weight")

# 3. Check assumptions
par(mfrow = c(2, 2))
plot(model1)

# Specific tests
shapiro.test(residuals(model1))
bptest(model1)
dwtest(model1)

# 4. Multiple regression
model2 <- lm(mpg ~ wt + hp + cyl, data = mtcars)
summary(model2)

# Compare models
AIC(model1, model2)
BIC(model1, model2)

# 5. Influential points
cooksd <- cooks.distance(model2)
which(cooksd > 4 / length(cooksd))

plot(model2, which = 4)

# ============================================================
# EXERCISE 4: ANOVA Analysis
# ============================================================

set.seed(123)
anova_data <- data.frame(
  group = factor(rep(c("A", "B", "C"), each = 20)),
  value = c(rnorm(20, 75, 10),
            rnorm(20, 80, 10),
            rnorm(20, 82, 10))
)

# 1. One-way ANOVA
fit <- aov(value ~ group, data = anova_data)
summary(fit)

# 2. Check assumptions
by(anova_data$value, anova_data$group, shapiro.test)
leveneTest(value ~ group, data = anova_data)

# 3. Post-hoc tests
TukeyHSD(fit)
pairwise.t.test(anova_data$value, anova_data$group, 
                p.adjust.method = "bonferroni")

# 4. Effect size
anova_summary <- summary(fit)
ss_effect <- anova_summary[[1]]$`Sum Sq`[1]
ss_total <- sum(anova_summary[[1]]$`Sum Sq`)
eta_sq <- ss_effect / ss_total
cat("Eta-squared:", eta_sq, "\n")

# 5. Visualizations
ggplot(anova_data, aes(x = group, y = value, fill = group)) +
  geom_boxplot() +
  labs(title = "One-Way ANOVA", 
       x = "Group", 
       y = "Value") +
  theme_minimal()

# Means with error bars
summary_data <- anova_data %>%
  group_by(group) %>%
  summarize(
    mean = mean(value),
    se = sd(value) / sqrt(n()),
    .groups = "drop"
  )

ggplot(summary_data, aes(x = group, y = mean)) +
  geom_point(size = 3) +
  geom_errorbar(aes(ymin = mean - se, ymax = mean + se), width = 0.1) +
  labs(title = "Group Means with Standard Error", 
       x = "Group", 
       y = "Mean Value") +
  theme_minimal()

# ============================================================
# EXERCISE 5: Two-Way ANOVA
# ============================================================

set.seed(123)
twoway_data <- data.frame(
  factor1 = factor(rep(c("Low", "High"), each = 30)),
  factor2 = factor(rep(rep(c("A", "B", "C"), each = 10), times = 2)),
  response = rnorm(60, 70, 10) + 
             c(0, 5)[rep(1:2, each = 30)] +
             c(0, 3, 6)[rep(1:3, 10, times = 2)]
)

# 1. Two-way ANOVA
fit_twoway <- aov(response ~ factor1 * factor2, data = twoway_data)
summary(fit_twoway)

# 2. Check interaction
# p-value for factor1:factor2 indicates significance of interaction

# 3. Simple effects (if needed)
# Compare factor2 within each level of factor1
twoway_data_low <- twoway_data[twoway_data$factor1 == "Low", ]
fit_simple_low <- aov(response ~ factor2, data = twoway_data_low)
summary(fit_simple_low)

# 4. Interaction plot
ggplot(twoway_data, aes(x = factor2, y = response, 
                        color = factor1, group = factor1)) +
  geom_point() +
  stat_summary(fun = mean, geom = "line", size = 1) +
  stat_summary(fun = mean, geom = "point", size = 3) +
  labs(title = "Interaction Plot",
       x = "Factor 2", 
       y = "Response",
       color = "Factor 1") +
  theme_minimal()

# 5. Effect sizes
anova_sum <- summary(fit_twoway)
ss_f1 <- anova_sum[[1]]$`Sum Sq`[1]
ss_f2 <- anova_sum[[1]]$`Sum Sq`[2]
ss_int <- anova_sum[[1]]$`Sum Sq`[3]
ss_error <- anova_sum[[1]]$`Sum Sq`[4]
ss_total <- sum(anova_sum[[1]]$`Sum Sq`)

eta_f1 <- ss_f1 / ss_total
eta_f2 <- ss_f2 / ss_total
eta_int <- ss_int / ss_total

cat("Effect sizes:\n")
cat("Factor 1:", eta_f1, "\n")
cat("Factor 2:", eta_f2, "\n")
cat("Interaction:", eta_int, "\n")

# ============================================================
# EXERCISE 6: Model Selection
# ============================================================

data(mtcars)

# 1. Full model
full_model <- lm(mpg ~ ., data = mtcars)
summary(full_model)

# 2. Stepwise selection
step_model <- step(full_model, direction = "both", trace = 0)
print(formula(step_model))

# 3. Compare models
models <- list(full_model, step_model)
compare_models <- function(models) {
  data.frame(
    AIC = sapply(models, AIC),
    BIC = sapply(models, BIC)
  )
}
compare_models(models)

# 4. Cross-validation (simplified)
set.seed(123)
n <- nrow(mtcars)
train_indices <- sample(1:n, size = round(0.8 * n))
train_data <- mtcars[train_indices, ]
test_data <- mtcars[-train_indices, ]

train_model <- lm(formula(step_model), data = train_data)
predictions <- predict(train_model, test_data)
cv_error <- mean((test_data$mpg - predictions)^2)
cat("\nCV Error:", cv_error, "\n")

# 5. Variable importance
coef(step_model)
summary(step_model)$coefficients[, c("Estimate", "Pr(>|t|)")]

# ============================================================
# EXERCISE 7: Regression Diagnostics
# ============================================================

# 1. Fit model
model <- lm(mpg ~ wt + hp, data = mtcars)
summary(model)

# 2. Diagnostic plots
par(mfrow = c(2, 2))
plot(model)

# 3. Outliers and influence
cooksd <- cooks.distance(model)
which(cooksd > 4 / length(cooksd))

# Leverage
hat_values <- hatvalues(model)
which(hat_values > 3 * mean(hat_values))

# 4. Multicollinearity
vif(model)  # Should be < 10 (or < 5 for stricter criterion)

# 5. Autocorrelation
dwtest(model)

# ============================================================
# EXERCISE 8: Case Study
# ============================================================

set.seed(123)
pharma_data <- data.frame(
  drug = factor(rep(c("A", "B", "C"), each = 30)),
  gender = factor(rep(rep(c("M", "F"), each = 15), times = 3)),
  bp_before = rnorm(90, 140, 15),
  bp_after = NA
)

pharma_data$bp_after <- pharma_data$bp_before - 
                        c(10, 15, 12)[as.numeric(pharma_data$drug)] +
                        c(0, -2)[as.numeric(pharma_data$gender)] +
                        rnorm(90, 0, 5)

# 1. Change scores
pharma_data$change <- pharma_data$bp_before - pharma_data$bp_after

# 2. Two-way ANOVA
fit_pharma <- aov(change ~ drug * gender, data = pharma_data)
summary(fit_pharma)

# 3. Assumptions
leveneTest(change ~ drug * gender, data = pharma_data)
shapiro.test(residuals(fit_pharma))

# 4. Post-hoc tests
TukeyHSD(fit_pharma)

# 5. Visualizations
ggplot(pharma_data, aes(x = drug, y = change, fill = gender)) +
  geom_boxplot() +
  labs(title = "Blood Pressure Change by Drug and Gender",
       x = "Drug",
       y = "Blood Pressure Change (mmHg)") +
  theme_minimal()

# Interaction plot
ggplot(pharma_data, aes(x = drug, y = change, color = gender, group = gender)) +
  stat_summary(fun = mean, geom = "line", size = 1) +
  stat_summary(fun = mean, geom = "point", size = 3) +
  labs(title = "Interaction: Drug × Gender",
       x = "Drug",
       y = "Mean Change") +
  theme_minimal()

# 6. Statistical Report
cat("\n=== STATISTICAL REPORT ===\n\n")
cat("RESEARCH QUESTION:\n")
cat("Do three drugs have different effects on blood pressure,\n")
cat("and does the effect differ by gender?\n\n")

cat("METHODS:\n")
cat("Two-way ANOVA with factors: Drug (A, B, C) and Gender (M, F)\n")
cat("Response variable: Change in blood pressure\n\n")

cat("RESULTS:\n")
print(summary(fit_pharma))
print(TukeyHSD(fit_pharma))

cat("\nCONCLUSIONS:\n")
if (summary(fit_pharma)[[1]]$`Pr(>F)`[1] < 0.05) {
  cat("- Main effect of Drug is significant\n")
}
if (summary(fit_pharma)[[1]]$`Pr(>F)`[2] < 0.05) {
  cat("- Main effect of Gender is significant\n")
}
if (summary(fit_pharma)[[1]]$`Pr(>F)`[3] < 0.05) {
  cat("- Interaction effect is significant\n")
}

# ============================================================
# EXERCISE 9: Advanced Regression
# ============================================================

# 1. Polynomial regression
model_poly <- lm(mpg ~ wt + I(wt^2), data = mtcars)
summary(model_poly)

# 2. Compare with linear
model_linear <- lm(mpg ~ wt, data = mtcars)
AIC(model_linear, model_poly)

ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  geom_smooth(method = "lm", se = TRUE, linetype = "dashed") +
  stat_smooth(method = "lm", formula = y ~ poly(x, 2), 
              color = "red", se = TRUE) +
  labs(title = "Polynomial vs Linear Regression")

# 3. Interaction model
model_int <- lm(mpg ~ hp * wt, data = mtcars)
summary(model_int)

# 4. Visualize interaction
# Create grid of values
wt_seq <- seq(min(mtcars$wt), max(mtcars$wt), length = 50)
hp_seq <- quantile(mtcars$hp, c(0.25, 0.50, 0.75))

plot_data <- expand.grid(wt = wt_seq, hp = hp_seq)
plot_data$predicted <- predict(model_int, plot_data)

ggplot(plot_data, aes(x = wt, y = predicted, color = factor(hp))) +
  geom_line(size = 1) +
  labs(title = "Interaction Effect: hp × wt",
       x = "Weight",
       y = "Predicted MPG",
       color = "Horsepower") +
  theme_minimal()

# ============================================================
# EXERCISE 10: Capstone Project
# ============================================================

cat("\n=== CAPSTONE: COMPLETE STATISTICAL ANALYSIS ===\n")

# 1. Research questions
cat("\nRESEARCH QUESTIONS:\n")
cat("1. What factors predict fuel efficiency?\n")
cat("2. Does cylinder count affect fuel efficiency?\n")
cat("3. Is there an interaction between weight and horsepower?\n")

# 2. Exploratory analysis
cat("\n\n2. EXPLORATORY DATA ANALYSIS:\n")
summary(mtcars)
pairs(mtcars[, 1:7])

# 3. Statistical tests
cat("\n3. STATISTICAL TESTS:\n")

# ANOVA
fit_anova <- aov(mpg ~ cyl, data = mtcars)
summary(fit_anova)

# t-tests
automatic <- mtcars$mpg[mtcars$am == 0]
manual <- mtcars$mpg[mtcars$am == 1]
t.test(automatic, manual)

# 4. Regression models
model1 <- lm(mpg ~ wt, data = mtcars)
model2 <- lm(mpg ~ wt + hp, data = mtcars)
model3 <- lm(mpg ~ wt * hp, data = mtcars)

cat("\n4. MODEL COMPARISON:\n")
print(data.frame(
  Model = c("wt", "wt + hp", "wt * hp"),
  AIC = c(AIC(model1), AIC(model2), AIC(model3)),
  R_squared = c(summary(model1)$r.squared,
                summary(model2)$r.squared,
                summary(model3)$r.squared)
))

# 5. Assumptions
cat("\n5. ASSUMPTIONS CHECKING:\n")
shapiro.test(residuals(model2))
bptest(model2)
dwtest(model2)
vif(model2)

# 6. Model selection
final_model <- step(lm(mpg ~ ., data = mtcars), 
                    direction = "both", trace = 0)
cat("\n6. FINAL SELECTED MODEL:\n")
print(formula(final_model))

# 7. Visualizations
p1 <- ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  geom_smooth(method = "lm") +
  labs(title = "MPG vs Weight")
print(p1)

p2 <- ggplot(mtcars, aes(x = factor(cyl), y = mpg, fill = factor(cyl))) +
  geom_boxplot() +
  labs(title = "MPG by Cylinders")
print(p2)

# 8. Complete report
cat("\n\n8. STATISTICAL REPORT:\n")
cat("========================\n")
cat("The analysis reveals that weight and horsepower are\n")
cat("significant predictors of fuel efficiency. Cylinder\n")
cat("count also significantly affects mpg. The best model\n")
cat("includes weight, horsepower, and their interaction.\n")

cat("\n✅ Analysis complete!\n")

