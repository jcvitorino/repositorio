#! /usr/bin/env python


import svm
import numpy

p = svm.Params()
#p.setPoly(2)

ds = svm.Dataset()

r = numpy.random.random((10,2))
s = numpy.random.random((15,2))
r[:,0] -= 0.8
ds.addMatrix(r,['neg']*10)
ds.addMatrix(s,['pos']*15)

m = svm.solvePair(p,ds,'neg','pos')

print 'Negative:',m.multiClassify(r)
print 'Positive:',m.multiClassify(s)

print 'loo:', svm.looPair(p,ds.getTrainData('neg','pos'))[0]
