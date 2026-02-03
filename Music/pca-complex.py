import pandas as pd
import numpy as np
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler, PolynomialFeatures
from sklearn.decomposition import PCA
import seaborn as sns
import matplotlib.pyplot as plt

# Step 1: Load the Iris dataset
iris = load_iris()
X = iris.data
y = iris.target
feature_names = iris.feature_names
target_names = iris.target_names

# Step 2: Create a DataFrame
df = pd.DataFrame(X, columns=feature_names)
df['species'] = [target_names[i] for i in y]

# Step 3: Add polynomial features (degree 3, include interactions)
poly = PolynomialFeatures(degree=3, include_bias=False)
X_poly = poly.fit_transform(df[feature_names])
poly_feature_names = poly.get_feature_names_out(feature_names)

df_poly = pd.DataFrame(X_poly, columns=poly_feature_names)
df_poly['species'] = df['species']

# Step 4: Standardize the features
features = df_poly.columns.difference(['species'])
scaler = StandardScaler()
X_scaled = scaler.fit_transform(df_poly[features])

# Step 5: Apply PCA to reduce to 2 dimensions
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

# Step 6: Create a new DataFrame for the PCA results
df_pca = pd.DataFrame(X_pca, columns=['PC1', 'PC2'])
df_pca['species'] = df_poly['species']

# Step 7: Plot the results using seaborn
plt.figure(figsize=(10, 7))
sns.scatterplot(
    data=df_pca,
    x='PC1',
    y='PC2',
    hue='species',
    palette='Set1',
    s=100,
    edgecolor='w'
)
plt.title('Very Complex PCA with Polynomial Features (Iris Dataset)', fontsize=14)
plt.xlabel(f'PC1 ({pca.explained_variance_ratio_[0]*100:.2f}% variance)')
plt.ylabel(f'PC2 ({pca.explained_variance_ratio_[1]*100:.2f}% variance)')
plt.grid(True)
plt.tight_layout()
plt.show()