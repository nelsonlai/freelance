# --- 安裝必要套件（只需跑一次） ---
# install.packages(c("readxl", "ggplot2", "corrplot", "Hmisc", "psych"))

library(readxl)
library(ggplot2)
library(corrplot)
library(Hmisc)
library(psych)

# --- 1. 讀取 Excel ---
df <- read_excel("Fractional Logit.xlsx")

# 移除非數值欄（如果有）
df_numeric <- df[sapply(df, is.numeric)]

# --- 2. 基本摘要統計 ---
summary_stats <- psych::describe(df_numeric)
print(summary_stats)

# --- 3. 計算相關矩陣（Pearson） ---
corr_matrix <- cor(df_numeric, use = "pairwise.complete.obs", method = "pearson")
print(corr_matrix)

# --- Spearman 相關矩陣 ---
corr_spearman <- cor(df_numeric, use = "pairwise.complete.obs", method = "spearman")

# --- 4. 熱力圖（corrplot 版本） ---
corrplot(corr_matrix, method = "color", title = "Correlation Matrix Heatmap", mar=c(0,0,1,0))

# --- 5. Res_Flood 與各變數的兩兩相關（Pearson + Spearman） ---
target <- "Res_Flood"
other_vars <- setdiff(colnames(df_numeric), target)

results <- data.frame(
  Variable = character(),
  Pearson_r = numeric(),
  Pearson_p = numeric(),
  Spearman_rho = numeric(),
  Spearman_p = numeric(),
  stringsAsFactors = FALSE
)

for (v in other_vars) {
  pear <- cor.test(df_numeric[[target]], df_numeric[[v]], method = "pearson")
  spear <- cor.test(df_numeric[[target]], df_numeric[[v]], method = "spearman")
  results <- rbind(results, data.frame(
    Variable = v,
    Pearson_r = pear$estimate,
    Pearson_p = pear$p.value,
    Spearman_rho = spear$estimate,
    Spearman_p = spear$p.value
  ))
}

print(results)

# --- 6. 多元線性迴歸模型 ---
formula_str <- paste("Res_Flood ~", paste(other_vars, collapse = " + "))
model <- lm(as.formula(formula_str), data = df_numeric)
summary(model)

# --- 7. 輸出結果成 CSV（可選） ---
write.csv(results, "Res_Flood_correlation_results.csv", row.names = FALSE)
write.csv(corr_matrix, "Correlation_Matrix_Pearson.csv")
