# Import examples to be used for correlation and reading of external resources

from pytesmo import metrics
import scipy.io as scio

print scio.idl.readsav.__doc__

print metrics.pearsonr.__doc__
print metrics.spearmanr.__doc__


