# Probability Distributions in R
# This script mirrors the examples from the R Markdown lesson.

# ============================================================
# NORMAL DISTRIBUTION
# ============================================================

# Probability Density Function
x <- seq(-4, 4, length = 100)
norm_density <- dnorm(x, mean = 0, sd = 1)
plot(
  x,
  norm_density,
  type = "l",
  main = "Standard Normal Distribution",
  xlab = "x",
  ylab = "Density"
)

# Cumulative Distribution Function
pnorm(0)       # P(X < 0)
pnorm(1.96)    # P(X < 1.96) ≈ 0.975
pnorm(-1.96)   # P(X < -1.96) ≈ 0.025

# Quantile Function
qnorm(0.95)   # 95th percentile
qnorm(0.025)  # 2.5th percentile (for 95% CI)
qnorm(0.975)  # 97.5th percentile

# Random Generation
set.seed(123)
random_normal <- rnorm(1000, mean = 0, sd = 1)
hist(
  random_normal,
  main = "Normal Distribution",
  xlab = "Value",
  breaks = 30
)

# ============================================================
# T-DISTRIBUTION
# ============================================================

x <- seq(-4, 4, length = 100)
plot(
  x,
  dnorm(x),
  type = "l",
  lty = 2,
  main = "t-Distribution vs Normal",
  xlab = "x",
  ylab = "Density"
)
lines(x, dt(x, df = 5), col = "red")
lines(x, dt(x, df = 10), col = "blue")
lines(x, dt(x, df = 30), col = "green")
legend(
  "topright",
  legend = c("Normal", "t(df=5)", "t(df=10)", "t(df=30)"),
  lty = c(2, 1, 1, 1),
  col = c("black", "red", "blue", "green")
)

# Critical values for t-tests
qt(0.975, df = 20)  # 95% confidence, two-tailed
qt(0.95, df = 20)   # One-tailed

# ============================================================
# CHI-SQUARE DISTRIBUTION
# ============================================================

x <- seq(0, 20, length = 100)
plot(
  x,
  dchisq(x, df = 5),
  type = "l",
  main = "Chi-Square Distribution",
  xlab = "x",
  ylab = "Density"
)

# Critical values for chi-square tests
qchisq(0.95, df = 5)
qchisq(0.025, df = 5)
qchisq(0.975, df = 5)

# ============================================================
# F-DISTRIBUTION
# ============================================================

x <- seq(0, 5, length = 100)
plot(
  x,
  df(x, df1 = 10, df2 = 20),
  type = "l",
  main = "F-Distribution",
  xlab = "x",
  ylab = "Density"
)

# Critical value for F-tests
qf(0.95, df1 = 3, df2 = 30)

# ============================================================
# BERNOULLI AND BINOMIAL DISTRIBUTIONS
# ============================================================

x <- 0:10
probs <- dbinom(x, size = 10, prob = 0.5)
barplot(
  probs,
  names.arg = x,
  main = "Binomial Distribution (n=10, p=0.5)",
  xlab = "Number of Successes",
  ylab = "Probability"
)

# ============================================================
# POISSON DISTRIBUTION
# ============================================================

x <- 0:20
lambda <- 5
poisson_probs <- dpois(x, lambda = lambda)
barplot(
  poisson_probs,
  names.arg = x,
  main = "Poisson Distribution (lambda=5)",
  xlab = "Count",
  ylab = "Probability"
)

# ============================================================
# EXPONENTIAL DISTRIBUTION
# ============================================================

x <- seq(0, 10, length = 100)
rate <- 1
exp_density <- dexp(x, rate = rate)
plot(
  x,
  exp_density,
  type = "l",
  main = "Exponential Distribution",
  xlab = "Time",
  ylab = "Density"
)

# ============================================================
# PRACTICAL APPLICATIONS
# ============================================================

# Example: Testing Normality
set.seed(123)
data <- rnorm(100)
hist(
  data,
  main = "Distribution Check",
  xlab = "Value",
  breaks = 15
)
qqnorm(data)
qqline(data, col = "red")
shapiro.test(data)

# Example: Sampling Distribution
set.seed(123)
population <- rnorm(10000, mean = 50, sd = 10)
samples <- replicate(1000, mean(sample(population, size = 30)))
hist(
  samples,
  main = "Sampling Distribution of the Mean",
  xlab = "Sample Mean",
  breaks = 30
)
abline(v = mean(samples), col = "red", lwd = 2)
mean(samples)
sd(samples)
10 / sqrt(30)  # Theoretical standard error

