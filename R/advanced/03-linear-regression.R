# Linear Regression examples converted from RMarkdown
# Run interactively or source this file. It uses built-in `mtcars` dataset.

# Required packages
required_pkgs <- c("ggplot2", "car", "lmtest", "MASS", "boot")
missing_pkgs <- required_pkgs[!(required_pkgs %in% installed.packages()[,"Package"]) ]
if(length(missing_pkgs) > 0) {
  message("Missing packages: ", paste(missing_pkgs, collapse = ", "), 
          ". Install them with install.packages() if you want to run everything.")
}

library(ggplot2)
library(car)
library(lmtest)
library(MASS)
library(boot)

# ---------------------------
# Simple Linear Regression
# ---------------------------

# Load data
data(mtcars)

# Fit simple linear regression: mpg ~ wt
model <- lm(mpg ~ wt, data = mtcars)
cat("--- Simple model summary ---\n")
print(summary(model))

# Scatter plot with regression line (will open a graphics device)
p <- ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  geom_smooth(method = "lm", se = TRUE) +
  labs(title = "Simple Linear Regression: MPG vs Weight",
       x = "Weight (1000 lbs)", y = "Miles per Gallon")
print(p)

# Coefficients, confidence intervals, predictions
cat("\nCoefficients:\n")
print(coef(model))
cat("\nConf Int:\n")
print(confint(model))

new_data <- data.frame(wt = c(2.5, 3.0, 3.5))
cat("\nPredictions (point):\n")
print(predict(model, new_data))
cat("\nPredictions (CI):\n")
print(predict(model, new_data, interval = "confidence"))
cat("\nPredictions (PI):\n")
print(predict(model, new_data, interval = "prediction"))

# ---------------------------
# Multiple Linear Regression
# ---------------------------
model_multiple <- lm(mpg ~ wt + hp + qsec, data = mtcars)
cat("\n--- Multiple model summary ---\n")
print(summary(model_multiple))

# Stepwise selection
full_model <- lm(mpg ~ ., data = mtcars)
cat("\nRunning stepwise selection (may take a moment)...\n")
step_model <- step(full_model, direction = "both", trace = 0)
cat("\n--- Stepwise model summary ---\n")
print(summary(step_model))

# ---------------------------
# Model Diagnostics
# ---------------------------
cat("\n--- Model diagnostics (plots will be shown) ---\n")

# 1. Linearity: residuals vs fitted and crPlots
plot(model, which = 1)
if(requireNamespace("car", quietly = TRUE)) {
  crPlots(model)
}

# 2. Independence: Durbin-Watson
cat("\nDurbin-Watson test:\n")
print(dwtest(model))

# 3. Homoscedasticity
plot(model, which = 3)
cat("\nBreusch-Pagan test:\n")
print(bptest(model))

# 4. Normality of residuals
plot(model, which = 2)
hist(residuals(model), main = "Distribution of Residuals")
cat("\nShapiro-Wilk test for residuals:\n")
print(shapiro.test(residuals(model)))

# 5. Leverage and Influence
plot(model, which = 4)
plot(model, which = 5)
cat("\nInfluence measures:\n")
print(influence.measures(model))

cooksd <- cooks.distance(model)
cat("Potential outliers (Cook's distance > 4/n):\n")
print(which(cooksd > 4 / length(cooksd)))

# All diagnostic plots
par(mfrow = c(2,2))
plot(model)
par(mfrow = c(1,1))

# ---------------------------
# Correcting Violations
# ---------------------------
cat("\n--- Transformations and robust regression ---\n")
model_log <- lm(mpg ~ log(wt), data = mtcars)
print(summary(model_log))

model_poly <- lm(mpg ~ wt + I(wt^2), data = mtcars)
print(summary(model_poly))

if(requireNamespace("MASS", quietly = TRUE)) {
  bc <- tryCatch({
    boxcox(mpg ~ wt, data = mtars <- mtcars)
  }, error = function(e) NULL)
}

# Robust regression
if(requireNamespace("MASS", quietly = TRUE)) {
  model_robust <- rlm(mpg ~ wt + hp, data = mtcars)
  cat("\nRobust regression summary:\n")
  print(summary(model_robust))
}

# ---------------------------
# Interaction Effects
# ---------------------------
model_int <- lm(mpg ~ wt * hp, data = mtcars)
cat("\nInteraction model summary:\n")
print(summary(model_int))

p_int <- ggplot(mtcars, aes(x = wt, y = mpg, color = as.factor(cyl))) +
  geom_point() + geom_smooth(method = "lm", se = FALSE) +
  labs(title = "Interaction Effect")
print(p_int)

# ---------------------------
# Dummy Variables
# ---------------------------
model_dummy <- lm(mpg ~ factor(cyl) + wt, data = mtcars)
cat("\nDummy variable model summary:\n")
print(summary(model_dummy))

mtcars$cyl_ref <- relevel(factor(mtcars$cyl), ref = "4")
model_ref <- lm(mpg ~ cyl_ref + wt, data = mtcars)
cat("\nReference-level model summary:\n")
print(summary(model_ref))

# ---------------------------
# Model Comparison
# ---------------------------
model1 <- lm(mpg ~ wt, data = mtcars)
model2 <- lm(mpg ~ wt + hp, data = mtcars)
model3 <- lm(mpg ~ wt * hp, data = mtcars)
cat("\nModel comparison (AIC, BIC):\n")
print(AIC(model1, model2, model3))
print(BIC(model1, model2, model3))
cat("\nANOVA comparison:\n")
print(anova(model1, model2, model3))

# ---------------------------
# Cross-Validation
# ---------------------------
# Leave-one-out cross-validation using boot::cv.glm
if(requireNamespace("boot", quietly = TRUE)) {
  cat("\nLOO CV (cv.glm)\n")
  loo <- tryCatch({
    cv.glm(mtcars, model_multiple)$delta
  }, error = function(e) {
    message("cv.glm failed: ", e$message); NULL
  })
  print(loo)
}

# k-fold CV implementation
cv_10fold <- function(model, data, k = 10) {
  # model: lm object
  f <- formula(model)
  folds <- cut(seq(1, nrow(data)), breaks = k, labels = FALSE)
  errors <- numeric(k)
  for(i in seq_len(k)) {
    test_indices <- which(folds == i)
    train_data <- data[-test_indices, , drop = FALSE]
    test_data <- data[test_indices, , drop = FALSE]
    train_model <- lm(f, data = train_data)
    predictions <- predict(train_model, test_data)
    errors[i] <- mean((test_data$mpg - predictions)^2)
  }
  mean(errors)
}
cat("\n10-fold CV MSE for model_multiple:\n")
print(cv_10fold(model_multiple, mtcars, k = 10))

# ---------------------------
# Predictive accuracy
# ---------------------------
cat("\nPredictive accuracy metrics for model_multiple:\n")
print(summary(model_multiple)$r.squared)
print(summary(model_multiple)$adj.r.squared)
cat("RMSE:\n")
print(sqrt(mean(residuals(model_multiple)^2)))
cat("MAE:\n")
print(mean(abs(residuals(model_multiple))))

# ---------------------------
# Complete example workflow
# ---------------------------
cat("\n--- Complete example workflow ---\n")
# pairs plot (opens graphics)
pairs(mtcars[, c("mpg", "wt", "hp", "cyl", "disp")])

model_full <- lm(mpg ~ ., data = mtcars)
print(summary(model_full))

par(mfrow = c(2,2)); plot(model_full); par(mfrow = c(1,1))

model_log2 <- lm(mpg ~ wt + hp, data = mtcars)
print(summary(model_log2))

final_model <- lm(mpg ~ wt + hp + factor(cyl), data = mtcars)
print(summary(final_model))

# Diagnostics for final model
cat("Shapiro test, Breusch-Pagan and Durbin-Watson for final model:\n")
print(shapiro.test(residuals(final_model)))
print(bptest(final_model))
print(dwtest(final_model))

cat("\n=== FINAL MODEL SUMMARY ===\n")
print(summary(final_model))
cat("\nR-squared =", round(summary(final_model)$r.squared, 3))
cat("\nAdjusted R-squared =", round(summary(final_model)$adj.r.squared, 3), "\n")

# End of script
