'''
Presentation of Machine Learning Python.
Continuous wavelet transform.

Issue: mlpy0.1.0 does not conain cwt function, nor wavelet module (might be mlpy.wavelet.cwt).
'''
import matplotlib.pyplot as plt
from obspy.core import read
import numpy as np
# import mlpy
# instead of using erroneous mlpy we use obspy native cwt function 
from obspy.signal.tf_misfit import cwt
# from obspy.imaging.cm import obspy_sequential - not available in our version of obspy

# http://examples.obspy.org/a02i.2008.240.mseed
stream = read("a02i.2008.240.mseed")
trace = stream[0]
# time resolution of the trace is 0.001 second
omega = 8

# in the article was this version
# spec, scale = mlpy.cwt(trace.data, dt=trace.stats.delta, dj=0.05,
#                        wf='morlet', p=omega0, extmethod='none',
#                        extlength='powerof2')                                     

# this is from https://docs.obspy.org/tutorial/code_snippets/continuous_wavelet_transform.html
f_min = 1
f_max = 50
npts = trace.stats.npts
dt = trace.stats.delta
t = np.linspace(0, dt * npts, npts) 
scalogram = cwt(trace.data, dt, omega, f_min, f_max)
print scalogram.shape
print scalogram
# again from the article - non logarithimc plot
tt = np.arange(trace.stats.npts)/trace.stats.sampling_rate
plt.imshow(np.abs(scalogram), extent=(t[0], t[-1], 1, 50))
plt.show()
fig = plt.figure()
ax = fig.add_subplot(111)

x, y = np.meshgrid(
    t,
    np.logspace(np.log10(f_min), np.log10(f_max), scalogram.shape[0]))
print x.shape, y.shape
ax.pcolormesh(x, y, np.abs(scalogram))
ax.set_xlabel("Time after %s [s]" % trace.stats.starttime)
ax.set_ylabel("Frequency [Hz]")
ax.set_yscale('log')
ax.set_ylim(f_min, f_max)
plt.show()


