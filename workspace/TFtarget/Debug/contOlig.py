#! /usr/bin/env python
import numpy
import pylab
def hamming_distance(s1, s2):
    assert len(s1) == len(s2)
    return sum(ch1 != ch2 for ch1, ch2 in zip(s1, s2))

f1 = open('HEXDIFF.txt')
f2  = open('OLIG')
i = 0
li1 = []
li2 = []

for l1 in f1:
    l1 = l1.replace('\n','')
    li1.append(l1)
    for l2 in f2:
        l2 = l2.replace('\n','')
        li2.append(l2)
y = 1
y = []
for l1 in li1:
    x = 1
    for l2 in li2:
        x = x + 1
        if hamming_distance(l1,l2) == 0:
            print l1
            print x
            y.append(x)
print "----------------"

#entrada = pylab.arange(1,141,1)

#print len(entrada)
print len(y)

#pylab.plot(entrada,y)
#pylab.xlabel('HeDiff')
#pylab.ylabel('Mark')
#pylab.title('Func')
#pylab.grid(True)
#pylab.show()