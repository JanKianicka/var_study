'''
Seismograms of various formats (e.g. SAC, MiniSEED, GSE2, SEISAN, Q,
etc.) can be imported into a Stream object using the read() function.
Streams are list-like objects which contain multiple Trace objects,
i.e. gap-less continuous time series and related header/meta
information.  Each Trace object has a attribute called data pointing
to a NumPy ndarray of the actual time series and the attribute stats
which contains all meta information in a dictionary-like Stats
object. Both attributes starttime and endtime of the Stats object are
UTCDateTime objects.  The following example demonstrates how a single
GSE2-formatted seismogram file is read into a ObsPy Stream
object. There exists only one Trace in the given seismogram:
'''

from obspy import read

st = read('data/RJOB_061005_072159.ehz.new')
print(st)
print "lenght of stream:", len(st)
# There is just one trace
tr = st[0]
print(tr)
print "dir(Trace): ", dir(tr)
print "tr.data type, tr.data shape:", tr.data.dtype, tr.data.shape

print(tr.stats)

st.plot()



