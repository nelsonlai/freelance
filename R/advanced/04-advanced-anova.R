# Advanced ANOVA in R
# This script covers one-way, two-way, repeated measures ANOVA, and post-hoc tests

library(car)
library(multcomp)
library(ggplot2)

# ============================================================
# 1. ONE-WAY ANOVA
# ============================================================

# Test if cylinder count affects mpg
fit_oneway <- aov(mpg ~ cyl, data = mtcars)
summary(fit_oneway)

# With ANOVA table
Anova(fit_oneway, type = "II")

# ============================================================
# 2. TWO-WAY ANOVA
# ============================================================

# Test main effects and interaction
# mpg ~ cylinder count + transmission type + interaction

# Create data with multiple factors
set.seed(123)
data_2way <- data.frame(
  score = rnorm(60, mean = 75, sd = 10),
  method = rep(c("Method A", "Method B", "Method C"), each = 20),
  time = rep(c("Morning", "Afternoon"), each = 10, times = 3)
)

# Fit two-way ANOVA
fit_twoway <- aov(score ~ method * time, data = data_2way)
summary(fit_twoway)

# Interpretation:
# - main effect of method
# - main effect of time
# - interaction effect (method × time)

# Type I, II, III sums of squares
Anova(fit_twoway, type = "II")
Anova(fit_twoway, type = "III")

# ============================================================
# 3. REPEATED MEASURES ANOVA
# ============================================================

# Data: subjects measured at multiple times
set.seed(123)
n_subjects <- 15
subject_id <- rep(1:n_subjects, each = 4)
time_point <- rep(c("Baseline", "1 month", "3 months", "6 months"), 
                    n_subjects)
score <- rnorm(n_subjects * 4, mean = 70, sd = 8) + 
         c(0, 5, 10, 15)[rep(1:4, n_subjects)] + 
         rnorm(n_subjects * 4, sd = 3)

data_rm <- data.frame(
  subject = factor(subject_id),
  time = factor(time_point),
  score = score
)

# Check assumption: Sphericity
# (Using ez package for easier handling)
# Note: ez package needs to be installed

# ============================================================
# 4. POST-HOC TESTS
# ============================================================

# Tukey's HSD (most common)
fit <- aov(mpg ~ cyl, data = mtcars)
TukeyHSD(fit)

# Pairwise comparisons with Bonferroni correction
pairwise.t.test(mtcars$mpg, mtcars$cyl, 
                p.adjust.method = "bonferroni")

# Other p-value adjustments
pairwise.t.test(mtcars$mpg, mtcars$cyl, 
                p.adjust.method = "holm")

pairwise.t.test(mtcars$mpg, mtcars$cyl, 
                p.adjust.method = "fdr")

# ============================================================
# 5. GENERAL LINEAR HYPOTHESIS (GLH)
# ============================================================

# For complex comparisons using multcomp
fit <- lm(mpg ~ cyl, data = mtcars)

# Define comparisons
K <- rbind(
  "4 vs 6" = c(1, -1, 0),
  "6 vs 8" = c(0, 1, -1)
)

# Adjust columns if needed (match model coefficients)
# Run GLH test
glht_result <- glht(fit, linfct = mcp(cyl = "Tukey"))
summary(glht_result)
confint(glht_result)

# ============================================================
# 6. ANCOVA (Analysis of Covariance)
# ============================================================

# ANCOVA: ANOVA with continuous covariate
# Example: Test method effect while controlling for baseline score

set.seed(123)
data_ancova <- data.frame(
  method = rep(c("A", "B"), each = 20),
  baseline = rnorm(40, 70, 10),
  score = c(rnorm(20, 75, 8), rnorm(20, 85, 8)) + 
          rnorm(40, 0, 2)
)

# Fit ANCOVA model
fit_ancova <- aov(score ~ baseline + method, data = data_ancova)
summary(fit_ancova)

# Check for homogeneity of regression slopes
fit_interaction <- aov(score ~ baseline * method, 
                       data = data_ancova)
summary(fit_interaction)

# If interaction is NOT significant, proceed with ANCOVA
# If significant, use different approach

# ============================================================
# 7. ASSUMPTIONS CHECKING
# ============================================================

# For ANOVA, check:
# 1. Normality (residuals should be normal)
# 2. Homogeneity of variances (equal variances across groups)
# 3. Independence
# 4. Linearity (for ANCOVA)

# One-way ANOVA assumptions
fit <- aov(mpg ~ cyl, data = mtcars)

# 1. Normality by group
by(mtcars$mpg, mtcars$cyl, shapiro.test)

# 2. Homogeneity of variances
leveneTest(mpg ~ factor(cyl), data = mtcars)
bartlett.test(mpg ~ cyl, data = mtcars)

# 3. Residuals
hist(residuals(fit), main = "Distribution of Residuals")
qqnorm(residuals(fit))
qqline(residuals(fit))

# All diagnostic plots
par(mfrow = c(2, 2))
plot(fit)

# ============================================================
# 8. NON-PARAMETRIC ALTERNATIVES
# ============================================================

# Kruskal-Wallis test (non-parametric one-way ANOVA)
kruskal.test(mpg ~ cyl, data = mtcars)

# Post-hoc: Dunn's test
library(dunn.test)
dunn.test(mtcars$mpg, mtcars$cyl, method = "bonferroni")

# Friedman test (non-parametric repeated measures)
# For repeated measures data
friedman.test(score ~ time | subject, data = data_rm)

# ============================================================
# 9. EFFECT SIZE
# ============================================================

# Calculate eta-squared (effect size for ANOVA)
fit <- aov(mpg ~ cyl, data = mtcars)
anova_summary <- summary(fit)

# Extract sums of squares
ss_effect <- anova_summary[[1]]$`Sum Sq`[1]
ss_total <- sum(anova_summary[[1]]$`Sum Sq`)

# Eta-squared
eta_sq <- ss_effect / ss_total
cat("Eta-squared:", eta_sq, "\n")

# Partial eta-squared
ss_error <- anova_summary[[1]]$`Sum Sq`[2]
partial_eta_sq <- ss_effect / (ss_effect + ss_error)
cat("Partial eta-squared:", partial_eta_sq, "\n")

# ============================================================
# 10. PRACTICAL EXAMPLE: COMPLETE ANALYSIS
# ============================================================

cat("\n=== COMPLETE ANOVA ANALYSIS ===\n")

# Research question: Does cylinder count and transmission type
# affect fuel efficiency?

# Step 1: Visualize the data
ggplot(mtcars, aes(x = factor(cyl), y = mpg, fill = factor(am))) +
  geom_boxplot() +
  labs(title = "MPG by Cylinders and Transmission",
       x = "Number of Cylinders",
       y = "Miles per Gallon",
       fill = "Transmission\n(0=Auto, 1=Manual)")

# Step 2: Fit two-way ANOVA
fit <- aov(mpg ~ factor(cyl) * factor(am), data = mtcars)
summary(fit)

# Step 3: Check assumptions
cat("\n--- Checking Assumptions ---\n")

# Normality
shapiro.test(residuals(fit))

# Equal variances
leveneTest(mpg ~ interaction(factor(cyl), factor(am)), data = mtcars)

# Step 4: Post-hoc tests
cat("\n--- Post-hoc Tests ---\n")
TukeyHSD(fit)

# For simple effects (if interaction is significant)
# Compare transmission types within each cylinder group
mtcars_4cyl <- mtcars[mtcars$cyl == 4, ]
t.test(mpg ~ am, data = mtcars_4cyl)

mtcars_6cyl <- mtcars[mtcars$cyl == 6, ]
t.test(mpg ~ am, data = mtcars_6cyl)

mtcars_8cyl <- mtcars[mtcars$cyl == 8, ]
t.test(mpg ~ am, data = mtcars_8cyl)

# Step 5: Calculate effect sizes
anova_summary <- summary(fit)

# Main effect of cyl
ss_cyl <- anova_summary[[1]]$`Sum Sq`[1]
ss_am <- anova_summary[[1]]$`Sum Sq`[2]
ss_int <- anova_summary[[1]]$`Sum Sq`[3]
ss_error <- anova_summary[[1]]$`Sum Sq`[4]
ss_total <- sum(anova_summary[[1]]$`Sum Sq`)

eta_cyl <- ss_cyl / ss_total
partial_eta_cyl <- ss_cyl / (ss_cyl + ss_error)

cat("\nEffect Size (Cylinder):")
cat("\n  Eta-squared:", eta_cyl)
cat("\n  Partial eta-squared:", partial_eta_cyl)

# Step 6: Report results
cat("\n\n--- STATISTICAL REPORT ---\n")
cat("Two-way ANOVA results:\n")
cat("- Main effect of cylinders: F =", 
    anova_summary[[1]]$`F value`[1], 
    ", p =", anova_summary[[1]]$`Pr(>F)`[1], "\n")
cat("- Main effect of transmission: F =",
    anova_summary[[1]]$`F value`[2],
    ", p =", anova_summary[[1]]$`Pr(>F)`[2], "\n")
cat("- Interaction effect: F =",
    anova_summary[[1]]$`F value`[3],
    ", p =", anova_summary[[1]]$`Pr(>F)`[3], "\n")

# ============================================================
# SUMMARY
# ============================================================

# You learned:
# 1. One-way ANOVA
# 2. Two-way ANOVA with interactions
# 3. Repeated measures ANOVA
# 4. Post-hoc tests (Tukey, pairwise, GLH)
# 5. ANCOVA (covariate adjustment)
# 6. Assumptions checking
# 7. Non-parametric alternatives
# 8. Effect size calculations
# 9. Complete ANOVA workflow

cat("\n✅ Advanced ANOVA analysis complete!\n")

