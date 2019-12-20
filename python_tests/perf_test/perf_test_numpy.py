import datetime
import numpy

if __name__ == "__main__":
    b = datetime.datetime.now()
    array = numpy.arange(100000000, dtype=numpy.double)
    numpy.sin(array)
    e = datetime.datetime.now()
    print "Duration: "+str(e-b)
    print "Exited"