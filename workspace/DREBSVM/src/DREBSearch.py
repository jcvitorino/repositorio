#! /usr/bin/env python
file = open('input')
labels = []
for line in file:
    list_tmp = line.split(';')
    labels.append(list_tmp[0])
    del list_tmp[0]
    	
    
