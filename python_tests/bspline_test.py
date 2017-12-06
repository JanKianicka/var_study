'''
Exercise from:
http://docs.scipy.org/doc/scipy-0.14.0/reference/tutorial/signal.html

cspline2d(input {, lambda, precision}) -> ck

  Description:

    Return the third-order B-spline coefficients over a regularly spacedi
    input grid for the two-dimensional input image.  The lambda argument
    specifies the amount of smoothing.  The precision argument allows specifying
    the precision used when computing the infinite sum needed to apply mirror-
    symmetric boundary conditions.


'''

import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
from scipy import signal, misc

img=mpimg.imread('Screenshot.png')
print img
imgplot = plt.imshow(img)
#plt.show()
image = misc.lena().astype("float32")
imgplot = plt.imshow(image)
plt.show()
derfilt = np.array([1.0,-2,1.0],"float32")
ck = signal.cspline2d(image,8.0)
deriv = signal.sepfir2d(ck, derfilt, [1]) + \
    signal.sepfir2d(ck, [1], derfilt)
'''
Alternative:
laplacian = array([[0,1,0],[1,-4,1],[0,1,0]],float32)
deriv2 = signal.convolve2d(ck,laplacian,mode='same',boundary='symm')
'''
plt.gray()
imgplot = plt.imshow(deriv)
plt.show()


