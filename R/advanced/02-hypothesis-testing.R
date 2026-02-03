# Hypothesis Testing in R
# Script version of the R Markdown lesson.

# ============================================================
# SETUP
# ============================================================

data("mtcars")

if (!requireNamespace("car", quietly = TRUE)) {
  stop("Package 'car' is required. Install it with install.packages('car').")
}
library(car)


# ============================================================
# ONE-SAMPLE T-TEST
# ============================================================

# Test if mean mpg = 20
t.test(mtcars$mpg, mu = 20)

# Alternative hypotheses
t.test(mtcars$mpg, mu = 20, alternative = "greater")
t.test(mtcars$mpg, mu = 20, alternative = "less")

# Confidence interval
t.test(mtcars$mpg, conf.level = 0.95)

# ============================================================
# TWO-SAMPLE T-TEST (INDEPENDENT)
# ============================================================

automatic <- mtcars$mpg[mtcars$am == 0]
manual <- mtcars$mpg[mtcars$am == 1]

# Two-sample t-test
t.test(automatic, manual)

# Assume equal variances
t.test(automatic, manual, var.equal = TRUE)

# One-tailed: automatic < manual
t.test(automatic, manual, alternative = "less")

# ============================================================
# CHECKING ASSUMPTIONS FOR T-TESTS
# ============================================================

# Normality tests
shapiro.test(automatic)
shapiro.test(manual)

# Visual inspection
old_par <- par(mfrow = c(1, 2))
hist(automatic, main = "Automatic")
hist(manual, main = "Manual")

# Q-Q plots
qqnorm(automatic)
qqline(automatic)
qqnorm(manual)
qqline(manual)
par(old_par)

# Equal variances (F-test)
var.test(automatic, manual)

# ============================================================
# PAIRED T-TEST
# ============================================================

set.seed(123)
before <- rnorm(30, mean = 75, sd = 10)
after <- before + rnorm(30, mean = 5, sd = 3)

t.test(before, after, paired = TRUE)

# Differences approach
diffs <- after - before
t.test(diffs, mu = 0)

# ============================================================
# WILCOXON TESTS
# ============================================================

# Rank-sum (Mann-Whitney)
wilcox.test(automatic, manual)
wilcox.test(automatic, manual, alternative = "less")

# Signed-rank (paired)
wilcox.test(before, after, paired = TRUE)

# ============================================================
# CHI-SQUARE TEST FOR INDEPENDENCE
# ============================================================

contingency <- table(mtcars$cyl, mtcars$vs)
contingency

chisq.test(contingency)

chi_result <- chisq.test(contingency)
chi_result$expected

# Warning for small expected counts
small_table <- contingency
chisq.test(small_table)

# Fisher's exact test for small samples
fisher.test(small_table)

# ============================================================
# ANOVA (ANALYSIS OF VARIANCE)
# ============================================================

anova_result <- aov(mpg ~ factor(cyl), data = mtcars)
summary(anova_result)

# Post-hoc tests
TukeyHSD(anova_result)
pairwise.t.test(mtcars$mpg, mtcars$cyl, p.adjust.method = "bonferroni")

# ============================================================
# CHECKING ANOVA ASSUMPTIONS
# ============================================================

by(mtcars$mpg, mtcars$cyl, shapiro.test)
leveneTest(mpg ~ factor(cyl), data = mtcars)
plot(anova_result)

# ============================================================
# ONE-WAY ANOVA EXAMPLES
# ============================================================

fit <- lm(mpg ~ cyl, data = mtcars)
anova(fit)

fit_full <- aov(mpg ~ factor(cyl), data = mtcars)
summary(fit_full)

# ============================================================
# PRACTICAL EXAMPLE: COMPLETE ANALYSIS
# ============================================================

boxplot(mpg ~ cyl, data = mtcars,
        main = "MPG by Cylinder Count",
        xlab = "Cylinders",
        ylab = "MPG")

shapiro.test(mtcars$mpg)
leveneTest(mpg ~ factor(cyl), data = mtcars)

fit <- aov(mpg ~ factor(cyl), data = mtcars)
summary(fit)
TukeyHSD(fit)

ss_cyl <- 824.8
ss_total <- 1126.0
eta_sq <- ss_cyl / (ss_cyl + ss_total)
print(paste("Effect size (eta-squared):", round(eta_sq, 3)))

# ============================================================
# COHEN'S D (EFFECT SIZE)
# ============================================================

# Manual calculation of Cohen's d
calculate_cohens_d <- function(x, y) {
  # Calculate means and standard deviations
  mean_x <- mean(x)
  mean_y <- mean(y)
  sd_x <- sd(x)
  sd_y <- sd(y)
  n_x <- length(x)
  n_y <- length(y)
  
  # Pooled standard deviation
  pooled_sd <- sqrt(((n_x - 1) * sd_x^2 + (n_y - 1) * sd_y^2) / (n_x + n_y - 2))
  
  # Cohen's d
  d <- (mean_x - mean_y) / pooled_sd
  
  return(d)
}

cohens_d_result <- calculate_cohens_d(automatic, manual)
print(paste("Cohen's d:", round(cohens_d_result, 3)))

# Interpretation guide:
# |d| < 0.2: negligible
# |d| < 0.5: small
# |d| < 0.8: medium
# |d| >= 0.8: large

