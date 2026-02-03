# Model Selection in R
# This script demonstrates variable selection, model comparison, and validation

library(MASS)
library(car)

# ============================================================
# 1. INFORMATION CRITERIA
# ============================================================

# Load data
data(mtcars)

# Fit multiple models
model1 <- lm(mpg ~ wt, data = mtcars)
model2 <- lm(mpg ~ wt + hp, data = mtcars)
model3 <- lm(mpg ~ wt + hp + disp + cyl, data = mtcars)
model4 <- lm(mpg ~ ., data = mtcars)

# Compare using AIC (Akaike Information Criterion)
AIC(model1, model2, model3, model4)

# BIC (Bayesian Information Criterion)
BIC(model1, model2, model3, model4)

# Lower is better for both AIC and BIC

# ============================================================
# 2. STEPWISE REGRESSION
# ============================================================

# Backward selection
full_model <- lm(mpg ~ ., data = mtcars)

model_backward <- step(full_model, direction = "backward")
summary(model_backward)

# Forward selection
empty_model <- lm(mpg ~ 1, data = mtcars)

model_forward <- step(empty_model, 
                      scope = formula(full_model),
                      direction = "forward")

# Both directions
model_both <- step(full_model, direction = "both")

# With specific criterion
model_criterion <- step(full_model, direction = "both", k = log(nrow(mtcars)))
# k = log(n) gives BIC instead of AIC

# ============================================================
# 3. SUBSET SELECTION
# ============================================================

# Best subsets (exhaustive search)
# Note: This can be slow for many variables

library(leaps)

# Using leaps package
predictors <- mtcars[, c("wt", "hp", "disp", "cyl", "drat", "qsec", "vs", "am", "gear", "carb")]
subsets <- regsubsets(x = predictors, y = mtcars$mpg, nvmax = 10)

# Plot results
par(mfrow = c(2, 2))
plot(subsets, scale = "adjr2")  # Adjusted R-squared
plot(subsets, scale = "bic")     # BIC
plot(subsets, scale = "Cp")      # Mallows' Cp

# Get best model summary
summary(subsets)

# Identify best model by each criterion
coef(subsets, which.min(summary(subsets)$bic))

# ============================================================
# 4. REGULARIZATION METHODS
# ============================================================

# Ridge Regression
library(glmnet)

# Prepare data
X <- as.matrix(mtcars[, -1])  # All predictors
y <- mtcars$mpg

# Fit ridge regression
# alpha = 0 for ridge, alpha = 1 for lasso, 0 < alpha < 1 for elastic net
ridge <- glmnet(X, y, alpha = 0, lambda = seq(0, 1, 0.01))

# Plot regularization path
plot(ridge, xvar = "lambda", label = TRUE)

# Cross-validation for lambda
cv.ridge <- cv.glmnet(X, y, alpha = 0, lambda = seq(0, 1, 0.01))
plot(cv.ridge)
best_lambda_ridge <- cv.ridge$lambda.min

# Lasso Regression
lasso <- glmnet(X, y, alpha = 1, lambda = seq(0, 0.1, 0.001))
plot(lasso, xvar = "lambda", label = TRUE)

cv.lasso <- cv.glmnet(X, y, alpha = 1)
plot(cv.lasso)
best_lambda_lasso <- cv.lasso$lambda.min

# Coefficients at optimal lambda
coef(cv.lasso, s = "lambda.min")
coef(cv.lasso, s = "lambda.1se")  # More conservative

# ============================================================
# 5. CROSS-VALIDATION
# ============================================================

# Leave-one-out cross-validation
library(boot)

# CV function
cv_function <- function(data, indices) {
  test_data <- data[indices, ]
  train_data <- data[-indices, ]
  
  model <- lm(mpg ~ wt + hp, data = train_data)
  predictions <- predict(model, test_data)
  actual <- test_data$mpg
  
  return(sum((actual - predictions)^2))
}

# LOOCV
cv_result <- cv.glm(mtcars, glm(mpg ~ wt + hp, data = mtcars))
cv_result$delta  # MSE

# k-fold Cross-validation
k_fold_cv <- function(model, data, k = 10) {
  n <- nrow(data)
  fold_size <- n %/% k
  folds <- cut(seq(1, n), breaks = k, labels = FALSE)
  
  errors <- numeric(k)
  
  for (i in 1:k) {
    test_indices <- which(folds == i)
    train_data <- data[-test_indices, ]
    test_data <- data[test_indices, ]
    
    # Fit model
    train_model <- lm(formula(model), data = train_data)
    
    # Predict
    predictions <- predict(train_model, test_data)
    actual <- test_data$mpg
    
    # Calculate error
    errors[i] <- mean((actual - predictions)^2)
  }
  
  return(list(
    mean_error = mean(errors),
    sd_error = sd(errors),
    errors = errors
  ))
}

cv_model1 <- k_fold_cv(model1, mtcars)
cv_model2 <- k_fold_cv(model2, mtcars)

cat("CV Error for Model 1:", cv_model1$mean_error, "\n")
cat("CV Error for Model 2:", cv_model2$mean_error, "\n")

# ============================================================
# 6. MODEL COMPARISON
# ============================================================

# Function to compare models
compare_models <- function(model_list) {
  results <- data.frame(
    model = character(),
    AIC = numeric(),
    BIC = numeric(),
    R_squared = numeric(),
    adj_R_squared = numeric(),
    RMSE = numeric(),
    stringsAsFactors = FALSE
  )
  
  for (i in 1:length(model_list)) {
    model <- model_list[[i]]
    
    # Calculate metrics
    aic_val <- AIC(model)
    bic_val <- BIC(model)
    r_sq <- summary(model)$r.squared
    adj_r_sq <- summary(model)$adj.r.squared
    rmse <- sqrt(mean(residuals(model)^2))
    
    # Add to results
    results <- rbind(results, data.frame(
      model = paste("Model", i),
      AIC = round(aic_val, 2),
      BIC = round(bic_val, 2),
      R_squared = round(r_sq, 3),
      adj_R_squared = round(adj_r_sq, 3),
      RMSE = round(rmse, 2)
    ))
  }
  
  return(results)
}

# Compare models
models <- list(model1, model2, model3, model4)
comparison <- compare_models(models)
print(comparison)

# ============================================================
# 7. FEATURE IMPORTANCE
# ============================================================

# Extract coefficients and their significance
model <- model2
summary_model <- summary(model)

# Create importance dataframe
importance <- data.frame(
  variable = names(coef(model)),
  coefficient = coef(model),
  p_value = summary_model$coefficients[, 4]
)

# Add significance stars
importance$significance <- ifelse(importance$p_value < 0.001, "***",
                                  ifelse(importance$p_value < 0.01, "**",
                                         ifelse(importance$p_value < 0.05, "*",
                                                ifelse(importance$p_value < 0.1, ".", ""))))

print(importance)

# ============================================================
# 8. OVERFITTING AND GENERALIZATION
# ============================================================

# Train-test split
set.seed(123)
train_indices <- sample(1:nrow(mtcars), size = round(0.8 * nrow(mtcars)))
train_data <- mtcars[train_indices, ]
test_data <- mtcars[-train_indices, ]

# Train models
model_train <- lm(mpg ~ wt + hp, data = train_data)
model_train_complex <- lm(mpg ~ ., data = train_data)

# Predict on training data
train_pred_simple <- predict(model_train, train_data)
train_pred_complex <- predict(model_train_complex, train_data)

# Predict on test data
test_pred_simple <- predict(model_train, test_data)
test_pred_complex <- predict(model_train_complex, test_data)

# Calculate errors
train_error_simple <- mean((train_data$mpg - train_pred_simple)^2)
train_error_complex <- mean((train_data$mpg - train_pred_complex)^2)

test_error_simple <- mean((test_data$mpg - test_pred_simple)^2)
test_error_complex <- mean((test_data$mpg - test_pred_complex)^2)

cat("\n=== Overfitting Analysis ===\n")
cat("Simple Model:\n")
cat("  Train MSE:", train_error_simple, "\n")
cat("  Test MSE:", test_error_simple, "\n")

cat("\nComplex Model:\n")
cat("  Train MSE:", train_error_complex, "\n")
cat("  Test MSE:", test_error_complex, "\n")

# ============================================================
# 9. PRACTICAL EXAMPLE
# ============================================================

cat("\n=== MODEL SELECTION WORKFLOW ===\n")

# Step 1: Fit full model
full <- lm(mpg ~ ., data = mtcars)
summary(full)

# Step 2: Stepwise selection
stepwise <- step(full, direction = "both", trace = 0)
cat("\nSelected model:")
print(formula(stepwise))
summary(stepwise)

# Step 3: Compare with regularization
X <- as.matrix(mtcars[, -1])
y <- mtcars$mpg

cv.lasso_final <- cv.glmnet(X, y, alpha = 1)
best_model_lasso <- glmnet(X, y, alpha = 1, lambda = cv.lasso_final$lambda.min)
coef(best_model_lasso)

# Step 4: Final model evaluation
final_model <- stepwise

# Diagnostics
par(mfrow = c(2, 2))
plot(final_model)

# Summary
cat("\n=== FINAL MODEL ===\n")
print(summary(final_model))
cat("\nR-squared:", round(summary(final_model)$r.squared, 3))
cat("\nAdjusted R-squared:", 
    round(summary(final_model)$adj.r.squared, 3))
cat("\nAIC:", round(AIC(final_model), 2))
cat("\nBIC:", round(BIC(final_model), 2))

# ============================================================
# SUMMARY
# ============================================================

# You learned:
# 1. Information criteria (AIC, BIC)
# 2. Stepwise regression
# 3. Subset selection
# 4. Regularization (Ridge, Lasso, Elastic Net)
# 5. Cross-validation
# 6. Model comparison
# 7. Feature importance
# 8. Detecting overfitting
# 9. Complete selection workflow

cat("\n✅ Model selection complete!\n")

