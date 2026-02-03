# Sample Datasets

This folder contains sample datasets for use in exercises and examples throughout the R training course.

## Available Datasets

### 1. sales_data.csv
**Purpose:** Beginner/Intermediate exercises - data manipulation
- **Format:** Wide format (months as columns)
- **Columns:** store, product, jan, feb, mar, apr, may, jun
- **Use for:** 
  - Data reading/writing practice
  - Reshaping wide-to-long
  - Group by operations
  - Visualization exercises

### 2. student_grades.csv
**Purpose:** Beginner/Intermediate exercises
- **Columns:** student_id, name, age, math, english, science, grade
- **Use for:**
  - Basic data frame operations
  - Computing summary statistics
  - Creating visualizations
  - Data manipulation exercises

### 3. pharmacy_study.csv
**Purpose:** Advanced exercises - ANOVA and hypothesis testing
- **Columns:** participant_id, drug, gender, age, bp_before, bp_after
- **Use for:**
  - Two-way ANOVA
  - Hypothesis testing
  - Paired tests
  - Interaction effects

### 4. treatment_data.csv
**Purpose:** Advanced exercises - experimental design
- **Columns:** subject_id, group, pre_treatment, post_treatment, age, gender
- **Use for:**
  - Paired t-tests
  - Repeated measures ANOVA
  - ANCOVA
  - Effect size calculations

### 5. experimental_design.csv
**Purpose:** Advanced exercises - two-factor ANOVA
- **Columns:** subject, factor1, factor2, response
- **Use for:**
  - Two-way ANOVA
  - Interaction effects
  - Post-hoc tests
  - Effect size calculations

## Usage

### Reading Datasets in R

```r
# Basic CSV reading
data <- read.csv("datasets/sales_data.csv")

# With readr package (recommended)
library(readr)
data <- read_csv("datasets/sales_data.csv")
```

### Using Relative Paths

```r
# From project root
sales <- read.csv("datasets/sales_data.csv")

# Using 'here' package
library(here)
sales <- read.csv(here("datasets", "sales_data.csv"))
```

## Built-in Datasets

R also includes many built-in datasets that are used throughout the course:

- **mtcars** - Motor Trend car data
- **iris** - Fisher's iris measurements
- **mtcars** - Car fuel efficiency data

### Loading Built-in Datasets

```r
# Load built-in dataset
data(mtcars)
```

## Creating Your Own Data

You can also create your own sample data in R:

```r
# Create sample data
set.seed(123)
my_data <- data.frame(
  id = 1:100,
  group = sample(c("A", "B", "C"), 100, replace = TRUE),
  score = rnorm(100, mean = 75, sd = 10)
)
```

## Data Requirements by Level

### Beginner
- Basic structures (sales_data.csv, student_grades.csv)
- Small, simple datasets
- Good for indexing and subsetting

### Intermediate
- Real-world styled data
- Multiple variables
- Suitable for dplyr and ggplot2
- Can be used for both sales_data.csv and student_grades.csv

### Advanced
- Experimental designs (pharmacy_study.csv, treatment_data.csv, experimental_design.csv)
- Suitable for statistical tests
- Balanced or unbalanced designs
- Multiple factors and interactions

## Notes

- All datasets are in CSV format for easy import
- Datasets are intentionally simple for learning
- Some datasets use created data suitable for statistical exercises
- Datasets may be used across multiple lessons
- Feel free to modify datasets for additional practice

## Contributing

If you create additional datasets:
- Keep them realistic and educational
- Include a description in this README
- Ensure data can be used in exercises
- Provide clear variable names
- Include appropriate sample sizes

