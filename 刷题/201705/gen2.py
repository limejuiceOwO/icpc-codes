#!/bin/python
from random import *

N=50000
M=50000
P=200

#n=randint(1,N)
n=50000
#m=randint(1,M)
m=50000
p=randint(2,P)
c=randint(1,p-1)
#p=8
#c=2

print "%d %d %d %d" % (n,m,p,c)
for i in range(0,n):
	print randint(0,p-1)
for i in range(0,m):
	l=randint(1,n)
	r=randint(1,n)
	#l=1
	#r=1
	if(l>r):
		t=l
		l=r
		r=t
	print "%d %d %d" % (randint(0,1),l,r)
