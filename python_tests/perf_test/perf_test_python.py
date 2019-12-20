import math
import datetime

if __name__ == "__main__":
    b = datetime.datetime.now()
    array = []
    for i in range(0,100000000):
        array.append(i)
    
    for i in array:
        math.sin(i)
    e = datetime.datetime.now()
    print "Duration - sin: "+str(e-b)
    print 'String manipulation'
    result = str();
    for element in array:
        result = "%.3f"%element
    e = datetime.datetime.now()
    print "Duration overall: "+str(e-b)    
    print "Exited"
        