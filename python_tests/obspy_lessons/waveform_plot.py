'''
We will use two different ObsPy Stream objects
throughout this tutorial. The first one, singlechannel, just contains one continuous Trace and the other one,
threechannel, contains three channels of a seismograph.
'''

from obspy.core import read
singlechannel = read('data/COP.BHZ.DK.2009.050')
print(singlechannel)
print type(singlechannel), dir(singlechannel)
print "lenght of singlechannel stream:", len(singlechannel)
print singlechannel[0].stats

threechannels = read('data/COP.BHE.DK.2009.050')
threechannels += read('data/COP.BHN.DK.2009.050')
threechannels += read('data/COP.BHZ.DK.2009.050')
print threechannels
print "lenght of threechannels stream:", len(threechannels)

dt = singlechannel[0].stats.starttime
# singlechannel.plot(color='red')
singlechannel.plot(color='red', number_of_ticks=7,
                   tick_rotation=5, tick_format='%I:%M %p',
                   starttime= dt+60*60, endtime= dt+60*60+120)

singlechannel.plot(outfile='singlechannel.png', size=(1500, 500), number_of_ticks=7,
                   starttime= dt+60*60, endtime= dt+60*60+120)

# plotting multiply channels
threechannels.plot(size=(800, 600))

# creating one day plot
singlechannel.plot(type='dayplot')


