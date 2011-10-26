#! /usr/bin/env python
import numpy as np
import math

import numpy
import pyroc
import svm

from prog_bar import ProgBar

def FalseNegative(guess,label):
    if guess == '-1' and label == '1':
        return True
    else:
        return False

def FalsePositive(guess,label):
    if guess == '1' and label == '-1':
        return True
    else:
        return False

def TruePositive(guess,label):
    if guess == '1' and label == '1':
        return True
    else:
        return False
    
def TrueNegative(guess,label):
    if guess == '-1' and label =='-1':
        return True
    else:
        return False

file = open('../seqs/saidaMarkov_606.csv')
labels = []
samples = np.zeros((228,213))
i = 0
for line in file:
    list_tmp = line.split(';')
    labels.append(list_tmp[0])
    del list_tmp[0]
    for j in xrange(len(list_tmp)):
	samples[i,j] = list_tmp[j]
    i = i + 1

pt = svm.Params()
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
 
TP = len(filter(lambda x:x==True, map(TruePositive,guess,labels)))
TN = len(filter(lambda x:x==True, map(TrueNegative,guess,labels)))
FP = len(filter(lambda x:x==True, map(FalsePositive,guess,labels)))
FN = len(filter(lambda x:x==True, map(FalseNegative,guess,labels)))
print "Confusion Matrix\n\n"

print "\t Actual class"
print "\t+(1)\t-(-1)"
print "+(1)\t%i\t%i\t Predicted" % (TP,FP)
print "-(-1)\t%i\t%i\t class" % (FN,TN)

ACC = (TP + TN)/ float(samples.shape[0])
SENS = float(TP)/ float((TP + FN)) 
SPEC = float(TN)/float((TN + FP))
EFF = (SENS + SPEC) / 2
PPV = float(TP) / float((TP + FP))
NPV = float(TN) / float((TN + FN)) 
PHI =  float(( (TP*TN) - (FP*FN))) / float(math.sqrt( (TP+FP) * (TP +FN) * (TN+FP) * (TN +FN)))

print "\n\n\nAccuracy %f" % (ACC)
print "Sensitivity %f" % (SENS)
print "Specificity %f" % (SPEC)
print "Efficiency %f" % (EFF)
print "Positive Predictive Value %f" % (PPV)
print "Negative Predictive Value %f" % (NPV)
print "Phi Coefficient %f" % (PHI)


print 'models ='
for params in mm.paramsList():
  print params

#print labels
