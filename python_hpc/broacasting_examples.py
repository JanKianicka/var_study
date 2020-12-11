# Example: A 3x2 array multiplied by a 1x2 array:
import numpy

a = numpy.arange(6).reshape(3,2)
b = numpy.array([7,11], float).reshape(1,2)

print(a)
# output: [[0 1],
#          [2 3],
#          [4 5]]

print(b)
# output: [[ 7.  11.]]

c = a * b

print(c)
# output: [[  0.  11.],
#          [ 14.  33.],
#          [ 28.  55.]]


# Example: calculate distances to a fixed point (origin) from a list of coordinates (points):

points = numpy.random.random((100, 3))  # 100 coordinates in 3D
origin = numpy.array((1.0, 2.2, -2.2))  # fixed point

# calculate distances
distances = (points - origin)**2
distances = numpy.sqrt(numpy.sum(distances, axis=1))

# find the most distant point
i = numpy.argmax(distances)
# Doc of argmax: Returns the indices of the maximum values along an axis.

print('Most distant point', points[i])
