import numpy as np
from numpy.linalg import inv

yVals = np.array([119.77, 118.85, 123.22, 123.45, 122.44])
xArray = np.array([[1   , 1   , 1   , 1, 1],
                   [2**4, 2**3, 2**2, 2, 1],
                   [3**4, 3**3, 3**2, 3, 1],
                   [4**4, 4**4, 4**2, 4, 1],
                   [5**4, 4**3, 5**2, 5, 1]])
Coef = np.matmul(yVals, inv(np.transpose(xArray)))

print("The coefficients of the polynomial are ", Coef)
