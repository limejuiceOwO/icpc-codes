#!/usr/bin/python2
from random import *

n=10
print "1 0"
print n
for i in range(2,11):
	print "%d %d" % (i,randint(1,i-1))