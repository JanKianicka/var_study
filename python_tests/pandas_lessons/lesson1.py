# 
# Lesson 1
# 
# Create Data - We begin by creating our own data set for analysis. This prevents the end user reading this tutorial from having to download any files to replicate the results below. We will export this data set to a text file so that you can get some experience pulling data from a text file.
# Get Data - We will learn how to read in the text file. The data consist of baby names and the number of baby names born in the year 1880.
# Prepare Data - Here we will simply take a look at the data and make sure it is clean. By clean I mean we will take a look inside the contents of the text file and look for any anomalities. These can include missing data, inconsistencies in the data, or any other data that seems out of place. If any are found we will then have to make decisions on what to do with these records.
# Analyze Data - We will simply find the most popular name in a specific year.
# Present Data - Through tabular data and a graph, clearly show the end user what is the most popular name in a specific year.

# Import all libraries needed for the tutorial

# General syntax to import a library but no functions: 
##import (library) as (give the library a nickname/alias)
import matplotlib.pyplot as plt
import pandas as pd #this is how I usually import pandas
import sys #only needed to determine Python version number
import os

print 'Python version ' + sys.version
print 'Pandas version ' + pd.__version__



# The inital set of baby names and bith rates
names = ['Bob','Jessica','Mary','John','Mel']
births = [968, 155, 77, 578, 973]


BabyDataSet = zip(names,births)
print BabyDataSet

df = pd.DataFrame(data = BabyDataSet, columns=['Names', 'Births'])
print df

df.to_csv('births1880.csv',index=False,header=False)
df = pd.read_csv('births1880.csv')
df = pd.read_csv('births1880.csv', header=None)
df = pd.read_csv('births1880.csv', names=['Names','Births'])
print df.dtypes


Sorted = df.sort(['Births'], ascending=False)
Sorted.head(1)

# Present data
# Create graph
df['Births'].plot()

# Maximum value in the data set
MaxValue = df['Births'].max()

# Name associated with the maximum value
MaxName = df['Names'][df['Births'] == df['Births'].max()].values

# Text to display on graph
Text = str(MaxValue) + " - " + MaxName

# Add text to graph
plt.annotate(Text, xy=(1, MaxValue), xytext=(8, 0), 
                 xycoords=('axes fraction', 'data'), textcoords='offset points')

print "The most popular name"
df[df['Births'] == df['Births'].max()]
#Sorted.head(1) can also be used
os.remove('births1880.csv')
plt.show()








