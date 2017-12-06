'''
Gaussian tests from:
http://stackoverflow.com/questions/14873203/plotting-of-1-dimensional-gaussian-distribution-function
'''

from matplotlib import pyplot as mp
import numpy as np
from scipy.stats import norm

def gaussian(x, mu, sig):
    return 1./(np.sqrt(2.*np.pi)*sig)*np.exp(-np.power((x - mu)/sig, 2.)/2)

for mu, sig in [(-1, 1), (0, 2), (2, 3)]:
    mp.plot(gaussian(np.linspace(-3, 3, 120), mu, sig))

mp.show()

#initialize a normal distribution with frozen in mean=-1, std. dev.= 1
rv = norm(loc = -1., scale = 1.0)
rv1 = norm(loc = 0., scale = 2.0)
rv2 = norm(loc = 2., scale = 3.0)

x = np.arange(-10, 10, .1)
print dir(rv)
print rv.__doc__
print norm.__doc__
print rv
#plot the pdfs of these normal distributions 
mp.plot(x, rv.pdf(x), x, rv1.pdf(x), x, rv2.pdf(x))
mp.show()