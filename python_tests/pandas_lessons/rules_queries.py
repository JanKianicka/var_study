'''
Using queries and combining rules.
'''

import pandas as pd
import numpy as np

A = np.arange(0,10, dtype=float)
PdA = pd.DataFrame(A)
print PdA.describe()

# setting the rules
rule0 = PdA > 2
rule1 = PdA < 6

# Combining rules
print [rule0 & rule1]

# Getting just the matching records
print PdA[(rule0) & (rule1)].dropna()

