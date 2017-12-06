'''The example uses a zero-phase-shift low-pass filter with a
corner frequency of 1 Hz using 2 corners. This is done in two runs forward and backward, so we end up with 4 corners
de facto.
The available filters are:
- bandpass
- bandstop
- lowpass
- highpass

'''

from obspy import read
import matplotlib.pyplot as plt
import numpy as np

st = read('data/RJOB_061005_072159.ehz.new')
# There is just one trace
tr = st[0]

# Filtering with a lowpass on a copy of the original Trace
tr_filt = tr.copy()
print tr_filt.filter.__doc__

tr_filt.filter('lowpass', freq=1.0, corners=2, zerophase=True)

# Now let's plot the raw and filtered data...
t = np.arange(0, tr.stats.npts / tr.stats.sampling_rate, tr.stats.delta)
plt.subplot(211)
plt.plot(t, tr.data, 'k')
plt.ylabel('Raw Data')
plt.subplot(212)
plt.plot(t, tr_filt.data, 'k')
plt.ylabel('Lowpassed Data')
plt.xlabel('Time [s]')
plt.suptitle(tr.stats.starttime)
plt.show()


'''
IIR filters in scipy - example from the documentation.
'''

from scipy import signal
# b, a = signal.iirfilter(17, [50, 200], rs=60, btype='band',
#                        analog=True, ftype='cheby2')

b, a = signal.iirfilter(2, 1, btype='lowpass')
print b, a

w, h = signal.freqs(b, a, 1000)
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(w, 20 * np.log10(abs(h)))
ax.set_xscale('log')
ax.set_title('Chebyshev Type II bandpass frequency response')
ax.set_xlabel('Frequency [radians / second]')
ax.set_ylabel('Amplitude [dB]')
ax.axis((10, 1000, -100, 10))
ax.grid(which='both', axis='both')
plt.show()

'''
Applying scipy filter to seismic data.
'''
output_signal = signal.filtfilt(b, a, tr.data, method='pad')
print "In shape: ", tr.data.shape
print tr.data
print "Out shape: ", output_signal.shape
print "b, a shapes: ", b.shape, a.shape
fig2 = plt.figure()
ax = fig2.add_subplot(111)
print output_signal

# this does not work, we should know more about filters at this point
plt.plot(t, output_signal, 'k')
plt.ylabel('Cheby filtered Data - filtfilt method pad')
plt.xlabel('Time [s]')
plt.show()

'''
Second option is to use lfilter
'''
output_signal2 = signal.lfilter(b, a, tr.data)
print output_signal2.shape, output_signal2
fig3 = plt.figure()
ax = fig3.add_subplot(111)
plt.plot(output_signal2, 'k')
plt.ylabel('Cheby filtered Data - lfilter method')
plt.xlabel('Time [s]')
plt.show()

