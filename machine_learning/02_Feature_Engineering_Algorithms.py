"""
Feature Engineering: Sample Python Code for Key Algorithms
==========================================================
This script demonstrates the main feature engineering techniques with
scikit-learn and pandas. Run each section to see inputs, parameters, and outputs.

Requirements: pandas, numpy, scikit-learn
Install: pip install pandas numpy scikit-learn
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import (
    MinMaxScaler,
    StandardScaler,
    RobustScaler,
    MaxAbsScaler,
    LabelEncoder,
    OneHotEncoder,
    OrdinalEncoder,
    KBinsDiscretizer,
    PolynomialFeatures,
    PowerTransformer,
)
from sklearn.impute import SimpleImputer, KNNImputer
from sklearn.feature_selection import (
    VarianceThreshold,
    SelectKBest,
    chi2,
    f_classif,
    mutual_info_classif,
    RFE,
)
from sklearn.linear_model import LogisticRegression
from sklearn.decomposition import PCA
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer

# ---------------------------------------------------------------------------
# 1. SCALING AND NORMALIZATION
# ---------------------------------------------------------------------------

def demo_scaling():
    """Min-Max, Standardization, Robust, MaxAbs scaling."""
    print("\n" + "=" * 60)
    print("1. SCALING AND NORMALIZATION")
    print("=" * 60)

    X = np.array([[10.0], [20.0], [30.0], [40.0], [50.0]])

    # 1a. Min-Max: scale to [0, 1]
    scaler_mm = MinMaxScaler()
    X_mm = scaler_mm.fit_transform(X)
    print("\n1a. Min-Max Scaling (range [0,1]):")
    print("   Formula: x' = (x - min) / (max - min)")
    print("   Before:", X.ravel())
    print("   After: ", X_mm.ravel().round(4))

    # 1b. Standardization (Z-score): mean=0, std=1
    scaler_std = StandardScaler()
    X_std = scaler_std.fit_transform(X)
    print("\n1b. Standardization (Z-score):")
    print("   Formula: x' = (x - mean) / std")
    print("   Before:", X.ravel())
    print("   After (mean≈0, std≈1):", X_std.ravel().round(4))

    # 1c. Robust: use median and IQR (good with outliers)
    X_out = np.array([[10.0], [20.0], [30.0], [40.0], [100.0]])  # 100 is outlier
    scaler_rob = RobustScaler()
    X_rob = scaler_rob.fit_transform(X_out)
    print("\n1c. Robust Scaling (median, IQR):")
    print("   Formula: x' = (x - median) / IQR")
    print("   Before (has outlier 100):", X_out.ravel())
    print("   After: ", X_rob.ravel().round(4))

    # 1d. MaxAbs: scale by max absolute value -> [-1, 1]
    scaler_ma = MaxAbsScaler()
    X_ma = scaler_ma.fit_transform(X)
    print("\n1d. Max-Abs Scaling (divide by max|x|):")
    print("   Before:", X.ravel())
    print("   After: ", X_ma.ravel().round(4))


# ---------------------------------------------------------------------------
# 2. ENCODING CATEGORICAL VARIABLES
# ---------------------------------------------------------------------------

def demo_encoding():
    """Label, Ordinal, One-Hot, Target, Frequency encoding."""
    print("\n" + "=" * 60)
    print("2. ENCODING CATEGORICAL VARIABLES")
    print("=" * 60)

    # Sample: color (nominal) and size (ordinal)
    df = pd.DataFrame({
        "color": ["red", "blue", "green", "red", "blue"],
        "size": ["S", "M", "L", "M", "S"],
        "target": [0, 1, 1, 0, 1],
    })

    # 2a. Label Encoding: arbitrary integer per category
    le = LabelEncoder()
    df["color_label"] = le.fit_transform(df["color"])
    print("\n2a. Label Encoding (arbitrary integers):")
    print(df[["color", "color_label"]].drop_duplicates().to_string(index=False))

    # 2b. Ordinal Encoding: user-defined order
    size_order = [["S", "M", "L"]]  # order matters
    oe = OrdinalEncoder(categories=size_order)
    df["size_ordinal"] = oe.fit_transform(df[["size"]])
    print("\n2b. Ordinal Encoding (ordered: S=0, M=1, L=2):")
    print(df[["size", "size_ordinal"]].drop_duplicates().to_string(index=False))

    # 2c. One-Hot Encoding: one binary column per category
    ohe = OneHotEncoder(sparse_output=False, drop="first")  # drop first to avoid redundancy
    color_ohe = ohe.fit_transform(df[["color"]])
    ohe_cols = [f"color_{c}" for c in ohe.categories_[0][1:]]  # after drop first
    df_ohe = pd.DataFrame(color_ohe, columns=ohe_cols)
    print("\n2c. One-Hot Encoding (binary columns, drop first):")
    print(pd.concat([df[["color"]], df_ohe], axis=1).to_string(index=False))

    # 2d. Target Encoding: replace category with mean of target (watch for leakage!)
    target_mean = df.groupby("color")["target"].mean().to_dict()
    df["color_target_enc"] = df["color"].map(target_mean)
    print("\n2d. Target Encoding (mean of target per category):")
    print(df[["color", "target", "color_target_enc"]].to_string(index=False))

    # 2e. Frequency Encoding: replace with count or proportion
    freq = df["color"].value_counts(normalize=True).to_dict()
    df["color_freq_enc"] = df["color"].map(freq)
    print("\n2e. Frequency Encoding (proportion of each category):")
    print(df[["color", "color_freq_enc"]].to_string(index=False))


# ---------------------------------------------------------------------------
# 3. HANDLING MISSING VALUES
# ---------------------------------------------------------------------------

def demo_missing_values():
    """Simple imputation (mean, median, mode), KNN imputation."""
    print("\n" + "=" * 60)
    print("3. HANDLING MISSING VALUES")
    print("=" * 60)

    df = pd.DataFrame({
        "A": [1.0, 2.0, np.nan, 4.0, 5.0],
        "B": [10.0, np.nan, 30.0, 40.0, 50.0],
        "C": ["x", "y", "y", np.nan, "x"],
    })
    print("\nOriginal (with NaN):")
    print(df.to_string())

    # 3a. Mean imputation (numeric)
    imp_mean = SimpleImputer(strategy="mean")
    df["A_mean"] = imp_mean.fit_transform(df[["A"]])
    print("\n3a. Mean Imputation for column A:")
    print(df[["A", "A_mean"]].to_string())

    # 3b. Median imputation (numeric, robust to outliers)
    imp_median = SimpleImputer(strategy="median")
    df["A_median"] = imp_median.fit_transform(df[["A"]])
    print("\n3b. Median Imputation for column A:")
    print(df[["A", "A_median"]].to_string())

    # 3c. Most-frequent (mode) for categorical
    imp_mode = SimpleImputer(strategy="most_frequent")
    df["C_mode"] = imp_mode.fit_transform(df[["C"]]).ravel()
    print("\n3c. Mode (Most Frequent) Imputation for column C:")
    print(df[["C", "C_mode"]].to_string())

    # 3d. KNN Imputation: use k nearest rows (by other columns) to impute
    df_num = df[["A", "B"]].copy()
    imp_knn = KNNImputer(n_neighbors=2)
    df_knn = pd.DataFrame(imp_knn.fit_transform(df_num), columns=["A", "B"])
    print("\n3d. KNN Imputation (n_neighbors=2) for A and B:")
    print(df_knn.to_string())


# ---------------------------------------------------------------------------
# 4. FEATURE TRANSFORMATION (Numerical)
# ---------------------------------------------------------------------------

def demo_transformation():
    """Log, Sqrt, Box-Cox, Yeo-Johnson, Binning, Polynomial."""
    print("\n" + "=" * 60)
    print("4. FEATURE TRANSFORMATION")
    print("=" * 60)

    # Right-skewed data (e.g. incomes, counts)
    X = np.array([[1], [2], [5], [10], [50], [200], [1000]])

    # 4a. Log transform
    X_log = np.log1p(X)  # log(1+x) to handle zeros
    print("\n4a. Log Transform: x' = log(1 + x)")
    print("   Before (skewed):", X.ravel())
    print("   After:          ", X_log.ravel().round(4))

    # 4b. Square root
    X_sqrt = np.sqrt(X)
    print("\n4b. Square Root: x' = sqrt(x)")
    print("   Before:", X.ravel())
    print("   After: ", X_sqrt.ravel().round(4))

    # 4c. Box-Cox (for positive data only)
    pt_bc = PowerTransformer(method="box-cox")
    X_bc = pt_bc.fit_transform(X)
    print("\n4c. Box-Cox (lambda chosen to maximize normality):")
    print("   Before:", X.ravel())
    print("   After: ", X_bc.ravel().round(4))

    # 4d. Yeo-Johnson (allows zero and negative)
    X_yj = np.array([[0], [1], [2], [5], [10], [-1]])
    pt_yj = PowerTransformer(method="yeo-johnson")
    X_yj_out = pt_yj.fit_transform(X_yj)
    print("\n4d. Yeo-Johnson (works with 0 and negative):")
    print("   Before:", X_yj.ravel())
    print("   After: ", X_yj_out.ravel().round(4))

    # 4e. Binning (discretization)
    X_bin = np.array([[1], [5], [10], [15], [20], [25], [30]])
    kb = KBinsDiscretizer(n_bins=3, encode="ordinal", strategy="uniform")
    X_binned = kb.fit_transform(X_bin)
    print("\n4e. Binning (3 equal-width bins, ordinal):")
    print("   Before: ", X_bin.ravel())
    print("   After:  ", X_binned.ravel().astype(int))

    # 4f. Polynomial features
    X_poly = np.array([[1], [2], [3]])
    pf = PolynomialFeatures(degree=2, include_bias=False)
    X_p2 = pf.fit_transform(X_poly)
    print("\n4f. Polynomial Features (degree=2): [x, x^2]")
    print("   Before:  ", X_poly.ravel())
    print("   After:   ", X_p2.tolist())
    print("   Names:   ", pf.get_feature_names_out().tolist())


# ---------------------------------------------------------------------------
# 5. FEATURE SELECTION
# ---------------------------------------------------------------------------

def demo_feature_selection():
    """Variance Threshold, Correlation, Chi-Square, F-statistic, Mutual Information, RFE."""
    print("\n" + "=" * 60)
    print("5. FEATURE SELECTION")
    print("=" * 60)

    # Dataset: 5 features, 1 constant (zero variance), 2 correlated, 2 useful
    np.random.seed(42)
    X = pd.DataFrame({
        "const": [0] * 20,           # zero variance -> remove
        "useful1": np.random.randn(20) * 2 + 10,
        "useful2": np.random.randn(20) + 5,
        "redundant": np.random.randn(20) * 3 + 1,  # we'll correlate with useful1
        "noise": np.random.randn(20),
    })
    X["redundant"] = X["useful1"] * 0.9 + np.random.randn(20) * 0.5  # correlated with useful1
    y = (X["useful1"] + X["useful2"] + np.random.randn(20) * 0.5 > 15).astype(int)

    # 5a. Variance Threshold: remove (near-)constant features
    vt = VarianceThreshold(threshold=0.01)
    X_vt = vt.fit_transform(X)
    kept = X.columns[vt.get_support()].tolist()
    print("\n5a. Variance Threshold (remove near-constant):")
    print("   Dropped (variance < 0.01):", [c for c in X.columns if c not in kept])
    print("   Kept:", kept)

    # 5b. Correlation: drop one of highly correlated pairs (manual example)
    corr = X[["useful1", "useful2", "redundant", "noise"]].corr()
    print("\n5b. Correlation (example): useful1 vs redundant are highly correlated;")
    print("   consider dropping one of them. Corr matrix (subset):")
    print(corr.round(3).to_string())

    # 5c. Chi-Square (categorical X, categorical Y) — we binarize for demo
    X_cat = (X[["useful1", "useful2"]] > X[["useful1", "useful2"]].median()).astype(int)
    skb_chi = SelectKBest(chi2, k=2)
    skb_chi.fit(X_cat, y)
    print("\n5c. Chi-Square (SelectKBest, k=2):")
    print("   Scores:", skb_chi.scores_.round(4))
    print("   Selected:", X_cat.columns[skb_chi.get_support()].tolist())

    # 5d. F-statistic (ANOVA): numeric X, categorical Y
    skb_f = SelectKBest(f_classif, k=3)
    X_num = X.drop(columns=["const"])
    skb_f.fit(X_num, y)
    print("\n5d. F-statistic / ANOVA (numeric X, categorical Y):")
    print("   F-scores:", skb_f.scores_.round(4))
    print("   Selected:", X_num.columns[skb_f.get_support()].tolist())

    # 5e. Mutual Information
    skb_mi = SelectKBest(mutual_info_classif, k=3)
    skb_mi.fit(X_num, y)
    print("\n5e. Mutual Information:")
    print("   MI scores:", skb_mi.scores_.round(4))
    print("   Selected:", X_num.columns[skb_mi.get_support()].tolist())

    # 5f. RFE (Recursive Feature Elimination)
    rfe = RFE(estimator=LogisticRegression(max_iter=500), n_features_to_select=2, step=1)
    rfe.fit(X_num, y)
    print("\n5f. RFE (Recursive Feature Elimination, n_to_select=2):")
    print("   Ranking (1=selected):", rfe.ranking_)
    print("   Selected:", X_num.columns[rfe.support_].tolist())


# ---------------------------------------------------------------------------
# 6. DIMENSIONALITY REDUCTION: PCA
# ---------------------------------------------------------------------------

def demo_pca():
    """Principal Component Analysis."""
    print("\n" + "=" * 60)
    print("6. DIMENSIONALITY REDUCTION: PCA")
    print("=" * 60)

    np.random.seed(42)
    # 3D data with 2 main directions of variance
    X = np.random.randn(50, 3) * np.array([3, 1, 0.5])  # first component dominates

    pca = PCA(n_components=2)
    X_pca = pca.fit_transform(X)
    print("\nPCA: project 3 features -> 2 components (maximize variance):")
    print("   Explained variance ratio:", pca.explained_variance_ratio_.round(4))
    print("   Cumulative:             ", np.cumsum(pca.explained_variance_ratio_).round(4))
    print("   Shape: X", X.shape, "-> X_pca", X_pca.shape)
    print("   First 3 rows of X_pca:\n", X_pca[:3].round(4))


# ---------------------------------------------------------------------------
# 7. TEXT: BAG OF WORDS AND TF-IDF
# ---------------------------------------------------------------------------

def demo_text_features():
    """Bag of Words and TF-IDF."""
    print("\n" + "=" * 60)
    print("7. TEXT FEATURES: BAG OF WORDS & TF-IDF")
    print("=" * 60)

    docs = [
        "the cat sat on the mat",
        "the dog sat on the log",
        "the cat and the dog",
    ]

    # 7a. Bag of Words (count)
    cv = CountVectorizer()
    X_bow = cv.fit_transform(docs)
    df_bow = pd.DataFrame(X_bow.toarray(), columns=cv.get_feature_names_out())
    print("\n7a. Bag of Words (word counts):")
    print(df_bow.to_string())

    # 7b. TF-IDF
    tfidf = TfidfVectorizer()
    X_tfidf = tfidf.fit_transform(docs)
    df_tfidf = pd.DataFrame(
        X_tfidf.toarray().round(4),
        columns=tfidf.get_feature_names_out(),
    )
    print("\n7b. TF-IDF (term frequency × inverse document frequency):")
    print("   Down-weights words that appear in many documents.")
    print(df_tfidf.to_string())


# ---------------------------------------------------------------------------
# 8. FEATURE CREATION (Derived, Time, Interaction)
# ---------------------------------------------------------------------------

def demo_feature_creation():
    """Derived, time/date, and interaction features."""
    print("\n" + "=" * 60)
    print("8. FEATURE CREATION")
    print("=" * 60)

    # 8a. Derived / ratio
    df = pd.DataFrame({"price": [100, 200, 150], "area": [50, 100, 75]})
    df["price_per_sqft"] = df["price"] / df["area"]
    print("\n8a. Derived: price_per_sqft = price / area")
    print(df.to_string())

    # 8b. Time/date features
    df["date"] = pd.to_datetime(["2024-01-15", "2024-02-20", "2024-06-10"])
    df["year"] = df["date"].dt.year
    df["month"] = df["date"].dt.month
    df["day_of_week"] = df["date"].dt.dayofweek
    df["is_weekend"] = (df["day_of_week"] >= 5).astype(int)
    print("\n8b. Time/Date: year, month, day_of_week, is_weekend")
    print(df[["date", "year", "month", "day_of_week", "is_weekend"]].to_string())

    # 8c. Interaction
    df["price_x_area"] = df["price"] * df["area"]
    print("\n8c. Interaction: price_x_area = price * area")
    print(df[["price", "area", "price_x_area"]].to_string())


# ---------------------------------------------------------------------------
# RUN ALL DEMOS
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    print("\n" + "#" * 60)
    print("#  FEATURE ENGINEERING ALGORITHMS — DEMONSTRATIONS")
    print("#" * 60)

    demo_scaling()
    demo_encoding()
    demo_missing_values()
    demo_transformation()
    demo_feature_selection()
    demo_pca()
    demo_text_features()
    demo_feature_creation()

    print("\n" + "#" * 60)
    print("#  END OF DEMONSTRATIONS")
    print("#" * 60 + "\n")
