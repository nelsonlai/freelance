import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

# 1. Generate a list of 500 random integers between 1 and 100
random_numbers = np.random.randint(1, 101, 500)

# 2. Use Pandas to create a DataFrame
df = pd.DataFrame(random_numbers, columns=['Random Numbers'])

# 3. Create a histogram using Seaborn
sns.histplot(data=df, x='Random Numbers', bins=20, kde=True)
plt.title("Distribution of Random Numbers")
plt.xlabel("Random Numbers")
plt.ylabel("Frequency")

# 4. Display the plot
plt.show()