import pandas as pd
from sklearn.datasets import load_iris
from sklearn.feature_selection import SelectKBest, f_classif
import seaborn as sns
import matplotlib.pyplot as plt

# Load the dataset
iris = load_iris()
X = iris.data
y = iris.target
feature_names = iris.feature_names
target_names = iris.target_names

# Step 1: Apply feature selection
selector = SelectKBest(score_func=f_classif, k=2)  # select top 2 features
X_selected = selector.fit_transform(X, y)

# Get selected feature names
selected_features = [feature_names[i] for i in selector.get_support(indices=True)]
print(f"Selected features: {selected_features}")

# Step 2: Create DataFrame for plotting
df_selected = pd.DataFrame(X_selected, columns=['Feature 1', 'Feature 2'])
df_selected['species'] = [target_names[i] for i in y]

# Step 3: Visualize
plt.figure(figsize=(8, 6))
sns.scatterplot(data=df_selected, x='Feature 1', y='Feature 2', hue='species', palette='Set2', s=80)
plt.title('Iris Dataset - Feature Selection (Top 2 Features by ANOVA F-value)')
plt.grid(True)
plt.tight_layout()
plt.show()