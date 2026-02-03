# R Training Course - Complete Overview

## Course Structure

This comprehensive R programming course is organized into three levels:

### 📚 Beginner Level
**Duration:** 2-3 weeks (24 hours)  
**Location:** `beginner/`  
**Prerequisites:** None  
**Focus:** R fundamentals

#### Lessons
1. **01-introduction.Rmd** - Getting started with R and RStudio
2. **02-data-types.Rmd** - Vectors, lists, matrices, data frames, factors
3. **03-control-structures.R** - If/else, loops, functions
4. **04-data-input-output.R** - Reading and writing data files

#### Learning Objectives
- Understand R and RStudio interface
- Master basic data types and structures
- Write control flow statements
- Read and write data files
- Write basic R functions

#### Exercises
- 10 practice exercises in `exercises/beginner-exercises.R`
- Complete solutions in `solutions/beginner-solutions.R`

#### Key Topics
- Variables and assignment
- Data structures (vectors, matrices, lists, data frames)
- Indexing and subsetting
- If/else statements and loops
- Functions and R programming basics
- File I/O operations

---

### 📊 Intermediate Level
**Duration:** 3-4 weeks (38 hours)  
**Location:** `intermediate/`  
**Prerequisites:** Completed Beginner Level  
**Focus:** Data manipulation and visualization

#### Lessons
1. **01-data-manipulation.Rmd** - dplyr for data manipulation
2. **02-data-reshaping.R** - tidyr for reshaping data
3. **03-visualization.Rmd** - ggplot2 for visualization
4. **04-descriptive-statistics.R** - Summary statistics

#### Learning Objectives
- Manipulate data using dplyr
- Reshape data between wide and long formats
- Create publication-quality visualizations
- Calculate descriptive statistics
- Perform exploratory data analysis

#### Exercises
- 10 practical exercises in `exercises/intermediate-exercises.R`
- Complete solutions with visualizations in `solutions/intermediate-solutions.R`

#### Key Topics
- dplyr verbs (filter, select, mutate, summarize, group_by)
- Pipe operator `%>%`
- tidyr functions (pivot_longer, pivot_wider, separate, unite)
- ggplot2 grammar of graphics
- Creating various plot types (scatter, bar, histogram, box plots)
- Descriptive statistics and correlation

---

### 🎯 Advanced Level
**Duration:** 4-5 weeks (56 hours)  
**Location:** `advanced/`  
**Prerequisites:** Completed Intermediate Level  
**Focus:** Statistical analysis and modeling

#### Lessons
1. **01-probability-distributions.Rmd** - Normal, t, chi-square, F distributions
2. **02-hypothesis-testing.Rmd** - t-tests, ANOVA, non-parametric tests
3. **03-linear-regression.Rmd** - Simple and multiple regression
4. **04-advanced-anova.R** - One-way, two-way, repeated measures ANOVA
5. **05-model-selection.R** - Model selection and validation

#### Learning Objectives
- Understand probability distributions
- Perform hypothesis tests (t-tests, ANOVA, chi-square)
- Build and interpret regression models
- Conduct ANOVA analyses
- Select and validate statistical models
- Check model assumptions

#### Exercises
- 10 comprehensive exercises in `exercises/advanced-exercises.R`
- Complete statistical reports in `solutions/advanced-solutions.R`

#### Key Topics
- Probability distributions in R
- Hypothesis testing workflow
- Type I and Type II errors
- p-values and interpretation
- Linear regression (simple and multiple)
- Model diagnostics (assumptions checking)
- ANOVA (one-way, two-way, repeated measures)
- Post-hoc tests (Tukey, Bonferroni)
- Effect sizes (eta-squared, Cohen's d)
- Model selection (AIC, BIC, stepwise)
- Cross-validation
- Regularization methods

---

## Course Materials

### File Formats
- **`.Rmd`** - R Markdown files (rich content with code, text, and output)
- **`.R`** - R script files (pure code with comments)
- **`.md`** - Markdown documentation files
- **`.csv`** - Sample datasets for practice

### Supporting Files
- **install-packages.R** - Install all required packages
- **README.md** - Main project documentation
- **COURSE_OVERVIEW.md** - This file
- **datasets/** - Sample datasets for exercises

---

## Getting Started

### 1. Install R and RStudio
- Download R from [CRAN](https://cran.r-project.org/)
- Download RStudio from [RStudio website](https://rstudio.com/)

### 2. Install Required Packages
Open RStudio and run:
```r
source("install-packages.R")
```

### 3. Start Learning
- Begin with `beginner/README.md`
- Follow the lessons in order
- Complete exercises before checking solutions
- Practice with provided datasets

---

## Learning Path

```
BEGINNER
   ↓ (Complete beginner level)
INTERMEDIATE
   ↓ (Complete intermediate level)
ADVANCED
   ↓ (Complete advanced level)
STATISTICAL CONSULTING READY
```

### Progression Guide

**After Beginner Level:**
- You can write basic R programs
- You understand data structures
- You can read and manipulate data

**After Intermediate Level:**
- You can clean and analyze real-world data
- You can create professional visualizations
- You can perform exploratory data analysis

**After Advanced Level:**
- You can conduct statistical tests
- You can build and interpret models
- You can perform regression and ANOVA
- You can write statistical reports

---

## Course Features

✅ **Comprehensive coverage** - From basics to advanced statistics  
✅ **Multiple formats** - R Markdown, R scripts, and documentation  
✅ **Practical exercises** - Real-world problems with solutions  
✅ **Sample datasets** - Ready-to-use data for practice  
✅ **Step-by-step** - Progressive difficulty across levels  
✅ **Theory + Practice** - Both concepts and implementation  
✅ **Statistical focus** - Hypothesis testing, regression, ANOVA  
✅ **Model diagnostics** - Assumptions checking and validation

---

## Estimated Completion Time

- **Total:** 118 hours (15-20 weeks part-time)
- **Beginner:** 24 hours
- **Intermediate:** 38 hours
- **Advanced:** 56 hours

---

## Resources

### Additional Learning Resources
- [R for Data Science](https://r4ds.had.co.nz/) by Hadley Wickham
- [RStudio Cheat Sheets](https://www.rstudio.com/resources/cheatsheets/)
- [CRAN Task Views](https://cran.r-project.org/web/views/)

### Package Documentation
- [Tidyverse](https://www.tidyverse.org/)
- [ggplot2](https://ggplot2.tidyverse.org/)
- [dplyr](https://dplyr.tidyverse.org/)

---

## Tips for Success

1. **Practice regularly** - Code along with every example
2. **Complete exercises** - Don't skip the practice problems
3. **Read solutions** - Learn from complete solutions
4. **Experiment** - Modify code to see what happens
5. **Use help** - `?function_name` is your friend
6. **Join communities** - R help mailing lists, Stack Overflow
7. **Build projects** - Apply skills to real problems
8. **Review regularly** - Revisit previous lessons

---

## Assessment

### Self-Assessment Questions

**Beginner:**
- Can I create and manipulate vectors and data frames?
- Can I write a function?
- Can I read CSV files?

**Intermediate:**
- Can I manipulate data with dplyr?
- Can I create publication-quality plots?
- Can I reshape data from wide to long?

**Advanced:**
- Can I perform hypothesis tests?
- Can I build and diagnose regression models?
- Can I conduct ANOVA and interpret results?

---

## Support

For questions or issues:
- Review the solutions files
- Check R documentation: `?function_name`
- Consult the lesson material
- Practice with sample datasets
- Refer to external resources

---

## Course Completion

Upon completing all three levels, you will:
- ✓ Be proficient in R programming
- ✓ Understand statistical analysis in R
- ✓ Be able to conduct hypothesis tests
- ✓ Be capable of building regression models
- ✓ Know how to perform ANOVA analyses
- ✓ Be able to create statistical reports
- ✓ Be ready for statistical consulting work

---

**Good luck with your R learning journey!**

