import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Load the CSV - df - dataframe
df = pd.read_csv("./student_scores.csv")    # df - dataframe
print(df.head(10))
# Set seaborn style
sns.set(style="whitegrid")

# Boxplot
plt.figure(figsize=(10, 6))
sns.boxplot(data=df[['Math', 'Science', 'English']])
plt.title("Boxplot of Scores by Subject")
plt.ylabel("Score")
plt.show()

# Histogram
plt.figure(figsize=(8, 5))
sns.histplot(df['Math'], bins=8, kde=True)
plt.title("Distribution of Math Scores")
plt.xlabel("Math Score")
plt.ylabel("Frequency")
plt.show()

# Scatter plot
plt.figure(figsize=(8, 5))
sns.scatterplot(data=df, x='Math', y='Science', hue='Gender', style='Gender', s=100)
plt.title("Math vs Science Scores by Gender")
plt.xlabel("Math Score")
plt.ylabel("Science Score")
plt.show()