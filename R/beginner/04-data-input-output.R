# Data Input and Output in R
# This script demonstrates reading and writing data files

# ============================================================
# 1. WORKING WITH CSV FILES
data <- read.csv("/Users/nelsonlai/sources/freelance/R/datasets/data.csv")

# Read CSV file (using base R)
data <- readr::read_csv("/Users/nelsonlai/sources/freelance/R/datasets/data.csv")
# Read CSV with readr package (faster, better defaults)
library(readr)
write.csv(data, "/Users/nelsonlai/sources/freelance/R/datasets/all_output.csv", row.names = FALSE)

# Write CSV file
readr::write_csv(data, "/Users/nelsonlai/sources/freelance/R/datasets/all_output.csv")

# Write CSV with readr
write_csv(data, "./datasets/all_output.csv")

# ============================================================
# 2. READING CSV FILES WITH OPTIONS
# ============================================================

data <- read.csv("/Users/nelsonlai/sources/freelance/R/datasets/data.csv", 
                 col.names = c("name", "age", "score", "status"))
# Specify column names
data <- read.csv("./datasets/data.csv", 
                 col.names = c("name", "age", "score", "status"))
data <- read.csv("/Users/nelsonlai/sources/freelance/R/datasets/data.csv", skip = 1)

# Skip first row
data <- read.csv("./datasets/data.csv", skip = 1)

data <- readr::read_csv("/Users/nelsonlai/sources/freelance/R/datasets/data.csv", 
                 col_select = c(name, age, score))
# Only read specific columns
data <- read_csv("./datasets/data.csv", 
                 col_select = c(name, age, score))

data <- read.csv("/Users/nelsonlai/sources/freelance/R/datasets/data.csv", 
                 na.strings = c("NA", "", "-"))
# Specify missing value markers
data <- read.csv("./datasets/data.csv", 
                 na.strings = c("NA", "", "-"))

# ============================================================
# 3. EXCEL FILES

# Install and load openxlsx
library(openxlsx)
data <- openxlsx::read.xlsx("/Users/nelsonlai/sources/freelance/R/datasets/data.xlsx", sheet = 1)

# Read Excel file
data <- openxlsx::read.xlsx("/Users/nelsonlai/sources/freelance/R/datasets/data.xlsx", sheet = "Sheet2")

# Read specific sheet
openxlsx::write.xlsx(data, "/Users/nelsonlai/sources/freelance/R/datasets/output.xlsx")

# Write Excel file
write.xlsx(data, "./datasets/output.xlsx")

# Create example data frames
data1 <- data.frame(x = 1:5, y = letters[1:5])
data2 <- data.frame(a = 10:14, b = c("red", "blue", "green", "yellow", "orange"))
openxlsx::write.xlsx(list(
  sheet1 = data1,
  sheet2 = data2
), "/Users/nelsonlai/sources/freelance/R/datasets/output.xlsx")

# ============================================================
# 4. TEXT FILES
# ============================================================
data <- read.delim("/Users/nelsonlai/sources/freelance/R/datasets/data.txt", sep = "\t")

# Read tab-delimited file
data <- read.delim("./datasets/data.txt", sep = "\t")
data <- read.table("/Users/nelsonlai/sources/freelance/R/datasets/data.txt", sep = "|")

# Read with custom delimiter
data <- read.table("./datasets/data.txt", sep = "|")
data <- readr::read_delim("/Users/nelsonlai/sources/freelance/R/datasets/data.txt", delim = "\t")

# Read with readr
data <- read_delim("./datasets/data.txt", delim = "\t")

# ============================================================
# 5. WORKING WITH DATASETS
# ============================================================

# R comes with built-in datasets
data(mtcars)
head(mtcars)

# Explore the data
dim(mtcars)
str(mtcars)
summary(mtcars)

# ============================================================
# 6. WRITING DATA
# ============================================================

# Create sample data
sample_data <- data.frame(
  name = c("Alice", "Bob", "Charlie"),
  age = c(25, 30, 35),
  score = c(85, 90, 78)
)
write.csv(sample_data, "/Users/nelsonlai/sources/freelance/R/datasets/output_sample_data.csv", row.names = FALSE)

# Write to CSV
readr::write_csv(sample_data, "/Users/nelsonlai/sources/freelance/R/datasets/output_sample_data.csv")

# Write to CSV with readr
openxlsx::write.xlsx(sample_data, "/Users/nelsonlai/sources/freelance/R/datasets/sample_data.xlsx")

# Write to Excel
write.xlsx(sample_data, "sample_data.xlsx")

# ============================================================
# 7. SAVING AND LOADING R OBJECTS
save(data, file = "/Users/nelsonlai/sources/freelance/R/datasets/my_data.RData")

# Save an R object
load("/Users/nelsonlai/sources/freelance/R/datasets/my_data.RData")

# Load an R object
save(data1, data2, file = "/Users/nelsonlai/sources/freelance/R/datasets/all_data.RData")

# Save multiple objects (using our example data frames)
saveRDS(data, "/Users/nelsonlai/sources/freelance/R/datasets/my_data.rds")

# Save to RDS format (single object)
saveRDS(data, "./datasets/my_data.rds")
data <- readRDS("/Users/nelsonlai/sources/freelance/R/datasets/my_data.rds")

# Load from RDS
data <- readRDS("./datasets/my_data.rds")

# ============================================================
# 8. PRACTICAL EXAMPLE
# ============================================================

# Example: Read sales data and analyze
sales <- read.csv("/Users/nelsonlai/sources/freelance/R/datasets/sales.csv")

# Read the data
sales <- read.csv("./datasets/sales.csv")

# Check the structure
str(sales)

# View first few rows
head(sales)

# Calculate summary statistics
summary(sales)

# Create a processed version
sales_summary <- data.frame(
  product = unique(sales$product),
  total_sales = aggregate(sales ~ product, 
                          data = sales, 
                          FUN = sum)$sales
)
write.csv(sales_summary, "/Users/nelsonlai/sources/freelance/R/datasets/sales_summary.csv", row.names = FALSE)

# Save the summary
write.csv(sales_summary, "./datasets/sales_summary.csv", row.names = FALSE)

# ============================================================
# SUMMARY
# ============================================================

# You learned:
# 1. How to read CSV files
# 2. How to read Excel files
# 3. How to read text files
# 4. How to write data to files
# 5. How to save and load R objects
# 6. Working with built-in datasets

# Important: Check your working directory
getwd()

## Example using here() (now using absolute paths instead)
# library(here)
# data <- read.csv(here(".", "datasets", "data.csv"))
# Note: Now using absolute paths throughout the script

