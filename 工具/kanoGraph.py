class Wrapper:
	def __init__(self,s):
		self.s = s
	def __getattr__(self,attr):
		return self.s[attr[0].encode("ascii")[0] - b'a'[0]]

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

def kanoGraph(n,f):
	''' Prints the n-bit Karnaugh map of boolean function f.
		For example:
			>> kanoGraph(4,lambda s:(s.a | s.b) & (s.a | s.b | s.c) & (r(s.a) | s.c) & (s.b | s.c | s.d))
			prints out a 4-bit map of function (A+B)(A+B+C)(!A + C)(B+C+D)
	'''
	ln = n // 2
	col = n - ln
	for s1 in gray(ln):
		for s2 in gray(col):
			s = s2 + s1
			print(int(f(Wrapper(s))),end = ' ')
		print()
