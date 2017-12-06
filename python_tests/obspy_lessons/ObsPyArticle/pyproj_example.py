'''
Conversion of coordinates using Python package pyproj.
There was problem with installing pyproj.
The following procedure was needed for our old CentOS 6.4
> yum erase python-pip.noarch
> rpm -ivh http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
> yum install python-setuptools python-setuptools-devel
> easy_install pip
> pip search pypro
> pip install pyproj
> pip show pyproj

'''
import pyproj
lat = [49.6919, 48.1629]
lon = [11.2217, 11.2752]
'''
EPSG:4326 WGS 84 / Latlong, degrees
EPSG:31468 DHDN / 3-degree Gauss-Kruger zone 4, meters
'''
proj_wgs84 = pyproj.Proj(init="epsg:4326")
proj_gk4   = pyproj.Proj(init="epsg:31468")
x,y = pyproj.transform(proj_wgs84, proj_gk4, lon, lat)
print x, y
# [4443949.9483748153, 4446189.8523829319] [5506426.9135883218, 5336352.4457970206]

'''
>>> print pyproj.Proj.__doc__

    performs cartographic transformations (converts from
    longitude,latitude to native map projection x,y coordinates and
    vice versa) using proj (http://trac.osgeo.org/proj/).

    A Proj class instance is initialized with proj map projection
    control parameter key/value pairs. The key/value pairs can
    either be passed in a dictionary, or as keyword arguments,
    or as a proj4 string (compatible with the proj command). See
    http://www.remotesensing.org/geotiff/proj_list for examples of
    key/value pairs defining different map projections.

    Calling a Proj class instance with the arguments lon, lat will
    convert lon/lat (in degrees) to x/y native map projection
    coordinates (in meters).  If optional keyword 'inverse' is True
    (default is False), the inverse transformation from x/y to
    lon/lat is performed. If optional keyword 'radians' is True
    (default is False) lon/lat are interpreted as radians instead of
    degrees. If optional keyword 'errcheck' is True (default is
    False) an exception is raised if the transformation is invalid.
    If errcheck=False and the transformation is invalid, no
    exception is raised and 1.e30 is returned. If the optional keyword
    'preserve_units' is True, the units in map projection coordinates
    are not forced to be meters.

    Works with numpy and regular python array objects, python
    sequences and scalars.

'''