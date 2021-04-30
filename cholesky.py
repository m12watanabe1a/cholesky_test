import numpy as np

cov = np.array([
    [1.0, 0.2, 0.0],
    [0.2, 1.0, 0.0],
    [0.0, 0.0, 1.0]
])

L = np.linalg.cholesky(cov)

print(cov)
print(L)
