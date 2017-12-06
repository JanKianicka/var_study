'''
Interesting parts of ObsPy tutorial.
'''

''' UTCDateTime based on POSIX time is used not the python datetime due to precision issues. '''

from obspy.core import UTCDateTime

DT1 = UTCDateTime("2012-09-07T12:15:00")
print "UTCDateTime of \"2012-09-07T12:15:00\" is: %s"%DT1
DT2 = UTCDateTime(2012, 9, 7, 12, 15, 0)
print "UTCDateTime(2012, 9, 7, 12, 15, 0) is %s"%DT2
DT3 = UTCDateTime(1347020100.0)
print "UTCDateTime(1347020100.0) is %s"%DT3

time = UTCDateTime("2012-09-07T12:15:00")
print "Attribute access:"
print "time.year: %d, time.julday: %d, time.timestamp: %.2f, time.weekday: %d"%(time.year, time.julday, time.timestamp, time.weekday)
print "Difference:"
print "(time - (time - 3600)): ",(time - (time - 3600))

