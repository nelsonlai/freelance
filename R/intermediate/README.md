# Intermediate Level - Data Manipulation and Visualization

## Overview

This section focuses on data science skills using R's tidyverse collection of packages. You'll learn to manipulate, clean, and visualize data effectively.

## Learning Objectives

By the end of this section, you will be able to:
- Manipulate data using dplyr functions
- Reshape data with tidyr
- Create publication-quality visualizations with ggplot2
- Calculate descriptive statistics
- Perform exploratory data analysis (EDA)
- Handle real-world messy datasets

## Prerequisites

- Completed Beginner Level
- Understanding of basic R syntax
- Familiarity with data frames
- Basic knowledge of control structures

## Required Packages

Make sure you have installed:
- `dplyr` - data manipulation
- `tidyr` - data reshaping
- `ggplot2` - visualization
- `readr` - reading data

If you haven't, run `source("../install-packages.R")`

## Course Materials

### 1. Data Manipulation with dplyr
**File:** `01-data-manipulation.Rmd`
- `filter()` - subset rows
- `select()` - choose columns
- `mutate()` - create new variables
- `summarize()` - calculate summaries
- `group_by()` - group operations
- Pipe operator `%>%`

### 2. Data Reshaping with tidyr
**File:** `02-data-reshaping.R`
- `pivot_longer()` - make data longer
- `pivot_wider()` - make data wider
- `separate()` and `unite()` - split/combine columns
- Handling missing values

### 3. Data Visualization with ggplot2
**File:** `03-visualization.Rmd`
- Grammar of graphics
- Scatter plots
- Bar charts and histograms
- Box plots and violin plots
- Customizing themes
- Adding labels and annotations

### 4. Descriptive Statistics
**File:** `04-descriptive-statistics.R`
- Central tendency measures
- Variability measures
- Correlation and covariance
- Cross-tabulations
- Data summaries

## Exercises

Work through `exercises/intermediate-exercises.R` using real datasets.

Full solutions with visualizations are in `solutions/intermediate-solutions.R`.

## How to Use This Section

1. Read each lesson thoroughly
2. Run all code examples
3. Practice with the sample datasets
4. Complete exercises progressively
5. Create your own visualizations

## Estimated Time

- **Week 1:** Data Manipulation (10 hours)
- **Week 2:** Data Reshaping and Visualization (10 hours)
- **Week 3:** Descriptive Statistics and Exercises (10 hours)
- **Week 4:** Review and advanced exercises (8 hours)

**Total:** 38 hours

## Tips for Success

- Master the pipe operator `%>%`
- Think in terms of data transformations
- Always visualize your data
- Learn ggplot2's grammar of graphics
- Practice with messy real-world data
- Document your code with comments

## Key Concepts

- **Tidyverse:** Collection of R packages for data science
- **Tidy data:** Data where each column is a variable, each row is an observation
- **Grammar of Graphics:** Systematic approach to building plots
- **Pipeline:** Chain of operations on data

## Next Steps

After mastering these skills, advance to **Advanced Level** for statistical analysis!

