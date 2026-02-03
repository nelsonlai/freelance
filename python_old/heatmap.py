import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Create example data (6x6 matrix)
data = np.random.rand(4, 8)

# Optional: create labels for rows and columns
rows = ['A', 'B', 'C', 'D']
cols = ['Col1', 'Col2', 'Col3', 'Col4', 'Col5', 'Col6', 'Col7', 'Col8']
df = pd.DataFrame(data, index=rows, columns=cols)

# Set Seaborn style
sns.set_theme(style="white")

# Create a heatmap
plt.figure(figsize=(8, 6))
sns.heatmap(df, annot=True, fmt=".2f", cmap="inferno", cbar=True)

plt.title("Example Heatmap with Seaborn")
plt.tight_layout()
plt.show()