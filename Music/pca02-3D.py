import pandas as pd
import numpy as np
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 1. Load Iris dataset
iris = load_iris()
X = iris.data
y = iris.target
feature_names = iris.feature_names
target_names = iris.target_names

# 2. Create DataFrame and add synthetic features
df = pd.DataFrame(X, columns=feature_names)
df['species'] = [target_names[i] for i in y]
df['sepal area'] = df['sepal length (cm)'] * df['sepal width (cm)']
df['petal area'] = df['petal length (cm)'] * df['petal width (cm)']
df['sepal/petal ratio'] = (df['sepal length (cm)'] + 1) / (df['petal length (cm)'] + 1)

# 3. Standardize features
features = df.columns.difference(['species'])
scaler = StandardScaler()
df_scaled = pd.DataFrame(scaler.fit_transform(df[features]), columns=features)
df_scaled['species'] = df['species']

# 4. Apply KMeans clustering
kmeans = KMeans(n_clusters=3, random_state=42)
df_scaled['cluster'] = kmeans.fit_predict(df_scaled[features])

# 5. Apply PCA (3D)
pca = PCA(n_components=3)
pca_components = pca.fit_transform(df_scaled[features])
df_pca = pd.DataFrame(pca_components, columns=['PC1', 'PC2', 'PC3'])
df_pca['cluster'] = df_scaled['cluster']
df_pca['species'] = df['species']

# 6. Save to CSV
df_pca.to_csv("iris_pca_3d_clusters.csv", index=False)

# 7. Plot 3D PCA
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')
colors = ['r', 'g', 'b']

for cluster_id in range(3):
    ax.scatter(
        df_pca[df_pca['cluster'] == cluster_id]['PC1'],
        df_pca[df_pca['cluster'] == cluster_id]['PC2'],
        df_pca[df_pca['cluster'] == cluster_id]['PC3'],
        label=f'Cluster {cluster_id}',
        s=60,
        alpha=0.8
    )

ax.set_title("3D PCA with KMeans Clustering on Complex Iris Dataset")
ax.set_xlabel(f'PC1 ({pca.explained_variance_ratio_[0]*100:.1f}%)')
ax.set_ylabel(f'PC2 ({pca.explained_variance_ratio_[1]*100:.1f}%)')
ax.set_zlabel(f'PC3 ({pca.explained_variance_ratio_[2]*100:.1f}%)')
ax.legend()
plt.tight_layout()
plt.show()