import numpy as np
import matplotlib.pyplot as plt
import random

n = 10000

# average
mu = np.array([[-5], [5]])

# covariance
cov = np.array(
    [[1, 0],
     [0, 1]])

L = np.linalg.cholesky(cov)
print(L)
dim = len(cov)

x_list = []
y_list = []
for i in range(n):
    v = np.random.randn(dim, 1)
    rand = L @ v+mu
    x,y = rand
    x_list.append(x)
    y_list.append(y)

plt.scatter(x_list, y_list, s=1)
plt.show()
