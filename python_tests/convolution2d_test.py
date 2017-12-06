'''
Excersise from:
https://docs.scipy.org/doc/scipy-0.15.1/reference/generated/scipy.signal.convolve2d.html
scipy.signal.convolve2d

'''

from scipy import signal
from scipy import misc
import numpy as np
lena = misc.lena()
scharr = np.array([[ -3-3j, 0-10j,  +3 -3j],
                   [-10+0j, 0+ 0j, +10 +0j],
                   [ -3+3j, 0+10j,  +3 +3j]]) # Gx + j*Gy
grad = signal.convolve2d(lena, scharr, boundary='symm', mode='same')

import matplotlib.pyplot as plt
#fig, (ax_orig, ax_mag, ax_ang) = plt.subplot(1, 3) -- this does not work in this version
plt.subplot(1,3,1)
plt.imshow(lena, cmap='gray')
plt.title('Original')
plt.axis('off')
plt.subplot(1,3,2)
plt.imshow(np.absolute(grad), cmap='gray')
plt.title('Gradient magnitude')
plt.axis('off')
plt.subplot(1,3,3)
plt.imshow(np.angle(grad), cmap='hsv') # hsv is cyclic, like angles
plt.title('Gradient orientation')
plt.axis('off')
plt.show()


