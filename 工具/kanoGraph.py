def gray(n):
	for x in range(0,2 ** n):
		bitseq = [0] * n;
		decompose = [(x & (1 << j)) >> j for j in range(n - 1,-1,-1)]
		bitseq[0] = decompose[0]
		for i in range(1,n):
			bitseq[i] = decompose[i] ^ decompose[i - 1]
		yield bitseq

def r(x):
	# Acts as !X
	return x ^ 1

def kanoGraph(n,f,irrelevant=None):
	''' Prints the n-bit Karnaugh map of boolean function f.
		Prints 'x' when irrelevant(a,b,c...) returns true.
		For example:
			>> kanoGraph(4,lambda a,b,c,d:r(a | b) & (a | b | c) & (r(a) | c) & (b | c | d),lambda a,b,c,d:b == c)
			prints out a 4-bit map of function !(A+B)(A+B+C)(!A + C)(B+C+D),with values showed as 'x' when B = C,like:
				x 0 0 x
				x 0 0 x
				1 x x 0
				1 x x 0
	'''
	ln = n // 2
	col = n - ln
	for s1 in gray(ln):
		for s2 in gray(col):
			kwargs = {}
			for i,v in enumerate(s2 + s1):
				kwargs[chr(ord('a') + i)] = v
			if(not (irrelevant and irrelevant(**kwargs))):
				print(int(f(**kwargs)),end = ' ')
			else:
				print('x',end = ' ')
		print()

def kanoGraph2(n,l):
	''' Prints the n-bit Karnaugh map of a value list l of length 2^n.
	'''
	ln = n // 2
	col = n - ln
	for s1 in gray(ln):
		for s2 in gray(col):
			p = 0
			for i,b in enumerate(s2 + s1):
				p += b * (1 << (n - i - 1))
			print(l[p],end = ' ')
		print()