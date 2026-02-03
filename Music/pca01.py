import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.datasets import load_iris
import pandas as pd

# 1. Load Iris dataset
iris = load_iris()
X = iris.data
y = iris.target


# 2. Apply PCA (2D)
X = iris.data
y = iris.target
feature_names = iris.feature_names
print(f'feature_names - {feature_names}')  # Print feature_names)
target_names = iris.target_names
print(f'target_names - {target_names}')

# Convert to DataFrame
df = pd.DataFrame(X, columns=feature_names)
df['species'] = [target_names[i] for i in y]

# Apply PCA to reduce to 2 dimensions
pca = PCA(n_components=2)
principal_components = pca.fit_transform(X)
df_pca = pd.DataFrame(data=principal_components, columns=['PC1', 'PC2'])
df_pca['species'] = df['species']

# Plot with seaborn
plt.figure(figsize=(8, 6))
sns.scatterplot(
    x='PC1', y='PC2',
    hue='species',
    palette='Set2',
    data=df_pca,
    s=80
)
plt.title('PCA of Iris Dataset')
plt.xlabel(f'PC1 ({pca.explained_variance_ratio_[0]*100:.1f}% variance)')
plt.ylabel(f'PC2 ({pca.explained_variance_ratio_[1]*100:.1f}% variance)')
plt.grid(True)
plt.tight_layout()
plt.show()