'''
Hierarchical clustering and dendrogram visualization of event dissimilarity.

'''
import pickle, urllib
import matplotlib.pyplot as plt
import hcluster

# For using with published example:
# url = "http://examples.obspy.org/dissimilarities.pkl"
# dissimilarity = pickle.load(urllib.urlopen(url))
dissimilarity = pickle.load(open("dissimilarities.pkl","rb"))
# Storing local pickle object:
# dis_temp = pickle.dumps(dissimilarity)
# pickle.dump(dissimilarity, open("dissimilarities.pkl","wb"))

plt.subplot(121)
plt.imshow(dissimilarity, interpolation="nearest")
dissimilarity = hcluster.squareform(dissimilarity)
threshold = 0.3
linkage = hcluster.linkage(dissimilarity, method = "single")
clusters = hcluster.fcluster(linkage, threshold, criterion = "distance")

plt.subplot(122)
hcluster.dendrogram(linkage, color_threshold=threshold)
plt.show()


'''
>> print hcluster.__doc__
Function Reference
------------------

These functions cut hierarchical clusterings into flat clusterings
or find the roots of the forest formed by a cut by providing the flat
cluster ids of each observation.

+------------------+-------------------------------------------------+
|*Function*        | *Description*                                   |
+------------------+-------------------------------------------------+
|fcluster          |forms flat clusters from hierarchical clusters.  |
+------------------+-------------------------------------------------+
|fclusterdata      |forms flat clusters directly from data.          |
+------------------+-------------------------------------------------+
|leaders           |singleton root nodes for flat cluster.           |
+------------------+-------------------------------------------------+

These are routines for agglomerative clustering.

+------------------+-------------------------------------------------+
|*Function*        | *Description*                                   |
+------------------+-------------------------------------------------+
|linkage           |agglomeratively clusters original observations.  |
+------------------+-------------------------------------------------+
|single            |the single/min/nearest algorithm. (alias)        |
+------------------+-------------------------------------------------+
|complete          |the complete/max/farthest algorithm. (alias)     |
+------------------+-------------------------------------------------+
...
See also here, quite interesting:
http://reference.wolfram.com/language/HierarchicalClustering/tutorial/HierarchicalClustering.html

'''