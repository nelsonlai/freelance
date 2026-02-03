# R Package Installation Script
# This script installs all required packages for the R training course

# List of required packages
required_packages <- c(
  # Data manipulation
  "dplyr",
  "tidyr",
  "readr",
  "readxl",
  "openxlsx",
  
  # Visualization
  "ggplot2",
  "plotly",
  "corrplot",
  "RColorBrewer",
  
  # Statistics and modeling
  "car",
  "lmtest",
  "MASS",
  "multcomp",
  "nortest",
  "effects",
  
  # Reporting
  "knitr",
  "rmarkdown",
  "kableExtra",
  
  # Additional utilities
  "here"
)

# Check and install packages
install_if_missing <- function(pkg) {
  if (!require(pkg, character.only = TRUE)) {
    install.packages(pkg, dependencies = TRUE)
    library(pkg, character.only = TRUE)
  }
}

# Install all packages
cat("Installing required packages...\n")
for (pkg in required_packages) {
  cat("Checking", pkg, "...\n")
  install_if_missing(pkg)
}

cat("\n✅ All packages installed successfully!\n")
cat("You're ready to start the R training course.\n")

