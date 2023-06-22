import numpy as np
from scipy.stats import norm, chi2, genpareto

random_numbers = np.random.standard_normal(10000)
mhat, shat = norm.fit(random_numbers)
print(mhat)
print(shat)