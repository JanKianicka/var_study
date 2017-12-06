# Lesson 2
# 
# Create Data - We begin by creating our own data set for analysis. This prevents the end user reading this tutorial from having to download any files to replicate the results below. We will export this data set to a text file so that you can get some experience pulling data from a text file.
# Get Data - We will learn how to read in the text file containing the baby names. The data consist of baby names born in the year 1880.
# Prepare Data - Here we will simply take a look at the data and make sure it is clean. By clean I mean we will take a look inside the contents of the text file and look for any anomalities. These can include missing data, inconsistencies in the data, or any other data that seems out of place. If any are found we will then have to make decisions on what to do with these records.
# Analyze Data - We will simply find the most popular name in a specific year.
# Present Data - Through tabular data and a graph, clearly show the end user what is the most popular name in a specific year.

# Import all libraries needed for the tutorial
import pandas as pd
from numpy import random
import matplotlib.pyplot as plt
import os

# The inital set of baby names
names = ['Bob','Jessica','Mary','John','Mel']

random.seed(500)
random_names = [names[random.randint(low=0,high=len(names))] for i in range(1000)]

# Print first 10 records
print random_names[:10]

# The number of births per name for the year 1880
births = [random.randint(low=0,high=1000) for i in range(1000)]
print births[:10]

BabyDataSet = zip(random_names,births)
print BabyDataSet[:10]

df = pd.DataFrame(data = BabyDataSet, columns=['Names', 'Births'])
print df[:10]

df.to_csv('births1880.txt',index=False,header=False)

print df.info()
print df.head()
print df.tail()
print df['Names'].unique()
print df['Names'].describe()

# Create a groupby object
name = df.groupby('Names')

# Apply the sum function to the groupby object
df1 = name.sum()
print df1

# Analyzing the data
print "Births",df1['Births'].max()

# Create graph
df1['Births'].plot(kind='bar')

print "The most popular name"
df1.sort(columns='Births', ascending=False)
plt.show()

os.remove('births1880.txt')