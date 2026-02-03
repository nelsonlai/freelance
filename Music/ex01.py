from sklearn.preprocessing import StandardScaler
import numpy as np

X = np.array([
    [1, 2], 
    [3, 4], 
    [5, 6]])

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

print("Means:", scaler.mean_)
print("Standard deviations:", np.sqrt(scaler.var_))
print("Scaled data:\n", X_scaled)