## --------------------------------------------------------
## 1. Load packages
## --------------------------------------------------------
library(readxl)
library(ggplot2)

## --------------------------------------------------------
## 2. Read Excel data
## --------------------------------------------------------
df <- read_excel("Fractional Logit.xlsx")

## Keep only numeric columns
df_num <- df[sapply(df, is.numeric)]

## --------------------------------------------------------
## 3. Run PCA (standardized)
## --------------------------------------------------------
pca <- prcomp(df_num, center = TRUE, scale. = TRUE)

## --------------------------------------------------------
## 4. Eigenvalues (Standard deviations^2)
## --------------------------------------------------------
eigenvalues <- pca$sdev^2
eigenvalues

## Explained variance ratio
explained_var <- eigenvalues / sum(eigenvalues)
cumulative_var <- cumsum(explained_var)

explained_df <- data.frame(
  PC = paste0("PC", 1:length(eigenvalues)),
  Eigenvalue = eigenvalues,
  Explained_Variance = explained_var,
  Cumulative = cumulative_var
)

print(explained_df)

## --------------------------------------------------------
## 5. Scree Plot
## --------------------------------------------------------
ggplot(explained_df, aes(x = seq_along(Eigenvalue), y = Eigenvalue)) +
  geom_point(color = "orange", size = 3) +
  geom_line(color = "orange", size = 1) +
  xlab("Principal Component") +
  ylab("Eigenvalue") +
  ggtitle("Scree Plot") +
  theme_minimal()

## --------------------------------------------------------
## 6. PCA Loadings (variable contributions)
## --------------------------------------------------------
loadings <- pca$rotation
print(loadings)

## If you want top loadings per PC:
top_loadings <- apply(loadings, 2, function(x) x[order(abs(x), decreasing = TRUE)][1:10])
print(top_loadings)

## --------------------------------------------------------
## 7. PCA scores (each row's PC1, PC2, PC3 ...)
## --------------------------------------------------------
scores <- pca$x
head(scores)

## Save scores to CSV
write.csv(scores, "PCA_scores.csv")

## Save loadings to CSV
write.csv(loadings, "PCA_loadings.csv")

## Save explained variance table
write.csv(explained_df, "PCA_explained_variance.csv")