#! /usr/bin/env python
import numpy as np
import math

import numpy
import cv

import svm

from cvarray import *
from prog_bar import ProgBar

file = open('input.csv')
labels = []
samples = np.zeros((3000,141))
i = 0
for line in file:
    list_tmp = line.split(';')
    labels.append(list_tmp[0])
    del list_tmp[0]
    for j in xrange(len(list_tmp)):
	samples[i,j] = list_tmp[j]
    i = i + 1

p = svm.Params()
#p.setPoly(2)

ds = svm.Dataset()
ds.addMatrix(samples,labels)
# Create the parameters set - use the standard model selection set...
ps = svm.ParamsSet(True)



# Train a model, print out basic info...
p = ProgBar()
mm = svm.MultiModel(ps,ds,callback=p.callback)
del p

guess = mm.multiClassify(samples)
print 'Success rate =',len(filter(lambda x:x==True,map(lambda a,b:a==b, guess,labels))) / float(samples.shape[0])

print 'models ='
for params in mm.paramsList():
  print params


#print labels
