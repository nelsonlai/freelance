# Data Visualization with ggplot2
# This script mirrors the examples from the R Markdown lesson.

# ============================================================
# LOAD PACKAGE
# ============================================================
library(ggplot2)

# ============================================================
# BASIC STRUCTURE TEMPLATE
# ============================================================
# ggplot(data, aes(x = var1, y = var2)) +
#   geom_point()

# ============================================================
# SCATTER PLOTS
# ============================================================

data("mtcars")

# Basic scatter plot
ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point()

# Add color by variable
ggplot(mtcars, aes(x = wt, y = mpg, color = cyl)) +
  geom_point()

# Change point size
ggplot(mtcars, aes(x = wt, y = mpg, size = hp)) +
  geom_point()

# ============================================================
# LINE PLOTS
# ============================================================

time_series <- data.frame(
  year = 2010:2019,
  sales = c(100, 120, 150, 140, 160, 180, 170, 200, 220, 240)
)

# Simple line plot
ggplot(time_series, aes(x = year, y = sales)) +
  geom_line()

# With points
ggplot(time_series, aes(x = year, y = sales)) +
  geom_line() +
  geom_point()

# ============================================================
# BAR CHARTS
# ============================================================

# Count data (no y-axis specified)
ggplot(mtcars, aes(x = cyl)) +
  geom_bar()

# With explicit counts
cyl_counts <- data.frame(
  cyl = c(4, 6, 8),
  count = c(11, 7, 14)
)

ggplot(cyl_counts, aes(x = cyl, y = count)) +
  geom_col()

# Horizontal bars
ggplot(cyl_counts, aes(x = cyl, y = count)) +
  geom_col() +
  coord_flip()

# ============================================================
# HISTOGRAMS
# ============================================================

# Basic histogram
ggplot(mtcars, aes(x = mpg)) +
  geom_histogram()

# Adjust bins
ggplot(mtcars, aes(x = mpg)) +
  geom_histogram(bins = 20)

# Add color by cylinder
ggplot(mtcars, aes(x = mpg, fill = as.factor(cyl))) +
  geom_histogram(bins = 20, alpha = 0.7)

# ============================================================
# BOX AND VIOLIN PLOTS
# ============================================================

# Basic box plot
ggplot(mtcars, aes(x = as.factor(cyl), y = mpg)) +
  geom_boxplot()

# Box plot with fill
ggplot(mtcars, aes(x = as.factor(cyl), y = mpg, fill = as.factor(cyl))) +
  geom_boxplot()

# Violin plot
ggplot(mtcars, aes(x = as.factor(cyl), y = mpg)) +
  geom_violin()

# ============================================================
# DENSITY PLOTS
# ============================================================

# Basic density plot
ggplot(mtcars, aes(x = mpg)) +
  geom_density()

# Multiple densities by cylinder
ggplot(mtcars, aes(x = mpg, color = as.factor(cyl))) +
  geom_density()

# ============================================================
# CUSTOMIZING PLOTS
# ============================================================

ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  labs(
    title = "Fuel Efficiency vs Weight",
    subtitle = "Cars from 1974",
    x = "Weight (1000 lbs)",
    y = "Miles per Gallon",
    caption = "Source: mtcars dataset"
  ) +
  theme_minimal()

# ============================================================
# MULTIPLE LAYERS
# ============================================================

ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  geom_smooth(method = "lm", se = TRUE) +
  labs(
    title = "MPG vs Weight with Trend Line",
    x = "Weight",
    y = "MPG"
  )

# ============================================================
# FACETS
# ============================================================

ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point() +
  facet_wrap(~ cyl)

# ============================================================
# THEMES
# ============================================================

p <- ggplot(mtcars, aes(x = wt, y = mpg)) +
  geom_point()

# Theme minimal
p + theme_minimal()

# Theme classic
p + theme_classic()

# Theme dark
p + theme_dark()

# Custom theme
p +
  theme(
    plot.title = element_text(size = 16, face = "bold"),
    axis.title = element_text(size = 12),
    panel.background = element_rect(fill = "white"),
    panel.grid.major = element_line(color = "gray80")
  )

# ============================================================
# COLOR SCALES
# ============================================================

# Discrete color scale
ggplot(mtcars, aes(x = wt, y = mpg, color = as.factor(cyl))) +
  geom_point() +
  scale_color_brewer(palette = "Set1")

# Continuous color scale
ggplot(mtcars, aes(x = wt, y = mpg, color = hp)) +
  geom_point() +
  scale_color_gradient(low = "blue", high = "red")

# ============================================================
# SAVING PLOTS (EXAMPLES)
# ============================================================

# ggsave("my_plot.png", width = 8, height = 6, dpi = 300)
# ggsave("my_plot.pdf", width = 8, height = 6)

# ============================================================
# ADVANCED EXAMPLE
# ============================================================

ggplot(mtcars, aes(x = wt, y = mpg, color = as.factor(cyl))) +
  geom_point(aes(size = hp), alpha = 0.6) +
  geom_smooth(method = "lm", se = FALSE) +
  facet_wrap(~ cyl) +
  labs(
    title = "Fuel Efficiency Analysis",
    subtitle = "By Number of Cylinders",
    x = "Weight (1000 lbs)",
    y = "Miles per Gallon",
    color = "Cylinders",
    size = "Horsepower"
  ) +
  theme_minimal() +
  theme(legend.position = "bottom")

