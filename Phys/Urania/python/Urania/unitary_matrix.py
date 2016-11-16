from scipy import *
from numpy import *
from sympy import Matrix
from sympy.physics.quantum import Dagger

def haar_measure(n):
	"""A Random matrix distributed with Haar measure
	http://arxiv.org/pdf/math-ph/0609050.pdf"""
	z = (randn(n,n)+ 1j*randn(n,n))/sqrt(2.0)
	q,r = linalg.qr(z)
	d = diagonal(r)
	ph = d/absolute(d)
	q = multiply(q,ph,q)
	return Matrix(q)
	

					








