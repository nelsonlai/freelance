# Feature Engineering: Comprehensive Description and Algorithms

## 1. What Is Feature Engineering?

**Feature engineering** is the process of **creating, transforming, selecting, and preparing variables (features)** from raw data so that machine learning algorithms can learn effectively. The goal is to represent the underlying problem in a way that makes patterns easier for models to discover.

### Why It Matters

- **Models are only as good as their inputs.** Algorithms learn from the features we provide; they cannot invent information that isn’t there.
- **Raw data is rarely model-ready.** Dates, categories, text, and skewed distributions need to be converted into numerical, well-scaled, and meaningful representations.
- **Impact on performance:** In practice, thoughtful feature engineering often improves results more than switching to a fancier algorithm.
- **Domain knowledge:** Good features encode what experts already know (e.g., ratios, rates, risk scores) so the model can leverage that structure.

### The Feature Engineering Loop

1. **Understand the data** — distributions, missingness, types, domain meaning.
2. **Create features** — derive new variables from existing ones.
3. **Transform features** — scale, encode, handle skew, impute.
4. **Select features** — remove noise, redundancy, and irrelevant variables.
5. **Evaluate** — train a model and measure performance; iterate.

---

## 2. Algorithms and Techniques for Feature Engineering

Feature engineering is not a single algorithm but a **set of techniques**. Below they are grouped by purpose, with the main “algorithms” or methods in each group.

---

### 2.1 Scaling and Normalization

Used to bring features to a common scale so that distance-based and gradient-based methods behave properly.

| Algorithm / Method | Formula / Idea | When to Use |
|-------------------|----------------|-------------|
| **Min-Max Scaling** | \( x' = \frac{x - x_{min}}{x_{max} - x_{min}} \) → [0, 1] | Bounded range needed; no strong outliers. |
| **Standardization (Z-score)** | \( x' = \frac{x - \mu}{\sigma} \) → mean 0, std 1 | Many algorithms (e.g. linear models, neural nets, SVM, k-NN). |
| **Max-Abs Scaling** | \( x' = \frac{x}{|x_{max}|} \) → [-1, 1] | Sparse data; preserving zeros. |
| **Robust Scaling** | \( x' = \frac{x - \text{median}}{IQR} \) | Data with outliers; use median and IQR instead of mean and std. |

---

### 2.2 Encoding Categorical Variables

Turn categories into numbers while preserving or exploiting their structure.

| Algorithm / Method | Idea | When to Use |
|-------------------|------|-------------|
| **Label Encoding** | Map each category to a unique integer (e.g. 0, 1, 2, …) | Ordinal data or tree-based models where order doesn’t matter. |
| **Ordinal Encoding** | Map categories to integers following a defined order (e.g. low=0, mid=1, high=2) | Ordinal variables with a clear ranking. |
| **One-Hot Encoding** | One binary column per category; 1 if that category, else 0 | Nominal data; few categories; linear/logistic models. |
| **Target Encoding (Mean Encoding)** | Replace category with mean (or similar) of the target for that category | High-cardinality categories; always guard against leakage. |
| **Frequency Encoding** | Replace category with its frequency (count or proportion) in the dataset | When “how often it appears” may be predictive. |
| **Binary Encoding** | Encode categories as binary digits, then split into multiple binary columns | High cardinality; fewer columns than one-hot. |

---

### 2.3 Handling Missing Values

| Algorithm / Method | Idea | When to Use |
|-------------------|------|-------------|
| **Deletion** | Drop rows or columns with missing values | Few missing; missing is random; enough data left. |
| **Constant / Mode Imputation** | Fill with a fixed value (e.g. 0, -1) or the mode | Simple baseline; “unknown” as a valid category. |
| **Mean / Median Imputation** | Fill with column mean or median | Numeric; missing at random; roughly symmetric (mean) or skewed (median). |
| **KNN Imputation** | For each missing cell, use the mean (or median) of the k nearest rows in other columns | Multivariate structure; missing not fully at random. |
| **Iterative Imputation (MICE)** | Model each column with missing values using the others; iterate until convergence | Multivariate; more sophisticated than KNN. |
| **“Missing” as Category** | Treat missing as its own category and encode it | When “missing” can carry information (e.g. “did not answer”). |

---

### 2.4 Feature Transformation (Numerical)

Change the distribution or form of numeric features to make them easier for models to use.

| Algorithm / Method | Idea | When to Use |
|-------------------|------|-------------|
| **Log Transform** | \( x' = \log(x + 1) \) or \( \log(x) \) | Right-skewed data; multiplicative effects (e.g. prices, counts). |
| **Square Root** | \( x' = \sqrt{x} \) | Moderate right skew; counts. |
| **Box-Cox** | \( x' = \frac{x^\lambda - 1}{\lambda} \) for \( x > 0 \); \(\lambda\) chosen to maximize normality | Right-skewed, positive data. |
| **Yeo-Johnson** | Extension of Box-Cox to allow zero and negative values | Skewed data that can be zero or negative. |
| **Binning / Discretization** | Split a continuous variable into intervals (equal width, equal frequency, or custom) | Non-linear effects; robustness to outliers; interpretability. |
| **Polynomial Features** | Create \( x, x^2, x^3, \ldots \) and optionally interactions | Capture non-linearity when the relationship is polynomial. |

---

### 2.5 Feature Creation

| Technique | Idea | When to Use |
|-----------|------|-------------|
| **Derived / Ratio Features** | e.g. `price_per_sqft = price / area`, `BMI = weight / height²` | Domain-driven; often more interpretable and stable. |
| **Aggregation** | Mean, sum, count, min, max, std per group (e.g. per user, per product) | When group-level statistics matter. |
| **Time / Date Features** | Extract year, month, day, day-of-week, is_weekend, time since event, cyclical encoding | Time-series and event-based data. |
| **Interaction Features** | Products or combinations of existing features (e.g. `age * income`) | When the effect of one feature depends on another. |

---

### 2.6 Feature Selection

Reduce the number of features to avoid overfitting, speed up training, and improve interpretability.

| Type | Algorithm / Method | Idea | When to Use |
|------|--------------------|------|-------------|
| **Filter** | **Variance Threshold** | Remove features with (near-)zero variance | Quick cleanup of constants. |
| **Filter** | **Correlation** | Remove one of two highly correlated features | Reduce redundancy. |
| **Filter** | **Chi-Square (\( \chi^2 \))** | Test independence between categorical feature and target | Categorical X, categorical Y. |
| **Filter** | **Mutual Information** | Measure dependence between feature and target; works for numeric and categorical | General dependence; non-linear. |
| **Filter** | **F-statistic / ANOVA** | Test if group means differ across categories of the target | Numeric X, categorical Y. |
| **Wrapper** | **RFE (Recursive Feature Elimination)** | Train model, remove least important feature, repeat | When you have a model that provides importance or coefficients. |
| **Embedded** | **Lasso (L1)** | L1 penalty drives some coefficients to zero | Sparse linear models; automatic feature selection. |
| **Embedded** | **Tree-based Importance** | Use importance from Random Forest, XGBoost, etc. | Any tree-based model; non-linear. |

---

### 2.7 Dimensionality Reduction

Create a smaller set of (often composite) features that retain most of the information.

| Algorithm | Idea | When to Use |
|-----------|------|-------------|
| **PCA (Principal Component Analysis)** | Linear projection to orthogonal directions of maximal variance | Numeric data; reduce dimensions; decorrelate; visualization. |
| **Kernel PCA** | PCA in a high-dimensional (kernel) space | Non-linear structure. |
| **t-SNE** | Non-linear projection that preserves local structure | Visualization (2D/3D); not for feature input to models. |
| **UMAP** | Similar to t-SNE; often faster and better at preserving global structure | Visualization and sometimes as input to downstream models. |

---

### 2.8 Text-Specific Feature Engineering

| Algorithm / Method | Idea | When to Use |
|-------------------|------|-------------|
| **Bag of Words (BoW)** | Count (or binary) of each word in a vocabulary per document | Simple baseline; small vocab; order doesn’t matter. |
| **TF-IDF** | Term frequency × inverse document frequency; down-weights common words | Text classification; information retrieval. |
| **N-grams** | Count sequences of n consecutive tokens (e.g. bigrams, trigrams) | Capture phrases and local context. |
| **Character N-grams** | N-grams over characters | Morphology; typos; languages with no clear word boundaries. |

---

## 3. Summary: Algorithms at a Glance

| Category | Main Algorithms / Methods |
|----------|---------------------------|
| **Scaling** | Min-Max, Standardization, MaxAbs, Robust |
| **Encoding** | Label, Ordinal, One-Hot, Target, Frequency, Binary |
| **Missing Values** | Deletion, Mean/Median/Mode, KNN, MICE, “Missing” as category |
| **Transformation** | Log, Sqrt, Box-Cox, Yeo-Johnson, Binning, Polynomial |
| **Creation** | Ratios, Aggregations, Time/Date, Interactions |
| **Selection** | Variance Threshold, Correlation, Chi-Square, Mutual Information, ANOVA, RFE, Lasso, Tree importance |
| **Dimensionality** | PCA, Kernel PCA, t-SNE, UMAP |
| **Text** | BoW, TF-IDF, N-grams |

---

## 4. How to Use the Accompanying Python Code

The file **`02_Feature_Engineering_Algorithms.py`** contains runnable examples for the main algorithms above. Each section:

1. Builds a small synthetic or simple dataset.
2. Applies the algorithm with **scikit-learn** or **pandas**.
3. Prints inputs, parameters, and outputs so you can see the effect.

**Run the script:**

```bash
pip install -r requirements.txt   # or: pip install pandas numpy scikit-learn
python 02_Feature_Engineering_Algorithms.py
```

You can also run individual sections by calling the demo functions (e.g. `demo_scaling()`, `demo_encoding()`) from a Python REPL or by uncommenting them in `if __name__ == "__main__"`.

Covered in code: **scaling** (Min-Max, Z-score, Robust, MaxAbs), **encoding** (Label, Ordinal, One-Hot, Target, Frequency), **missing values** (mean, median, mode, KNN), **transforms** (log, sqrt, Box-Cox, Yeo-Johnson, binning, polynomial), **feature selection** (Variance Threshold, correlation, Chi-Square, F-statistic, Mutual Information, RFE), **PCA**, **text** (Bag of Words, TF-IDF), and **feature creation** (derived, time/date, interaction).

---

*Part of the teaching project on feature engineering, deep learning, and machine learning.*
