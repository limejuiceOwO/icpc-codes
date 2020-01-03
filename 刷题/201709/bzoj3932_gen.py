#!/usr/bin/python2
from random import *

n=randint(1,1000)
m=randint(1,1000)
print "%d %d" % (m,n)
for i in range(0,m):
	s=randint(1,n)
	e=randint(1,n)
	p=randint(1,1000000)
	if(s>e):
		t=e
		e=s
		s=t
	print "%d %d %d" % (s,e,p)

li=range(1,n+1)
shuffle(li)
for i in range(0,n):
	k=randint(1,m+10)
	print "%d %d" % (li[i],k)