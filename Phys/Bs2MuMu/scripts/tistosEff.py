from math import *
from valAndErr import valAndErr

#This class hold the TISTOS trigger efficiency formula and treats the
#uncertainties in a correct uncorrelated way

#NB! Return valAndErr objects!

class tistosEff():

	def __init__(self, n_tistos, n_tos, n_tis = -1, n_trig = -1): # Can also be used just for tis or tos efficiency.

		#Efficiencies
		self.eff = valAndErr(0,0)

		#Set the global variables
		self.n_trig = n_trig
		self.n_tis = n_tis
		self.n_tos = n_tos
		self.n_tistos = n_tistos

		#Defined the uncorrelated variables
		self.a = self.n_trig - self.n_tis - self.n_tos + self.n_tistos
		self.b = n_tos - n_tistos
		self.c = n_tis - n_tistos
		self.d = n_tistos

		print ' #---------------------------------------#'
		print '  New effAndErr object created: '
		print '  	n_trig 		= ', 	n_trig
		print '  	n_tis 		= ' ,	n_tis
		print '  	n_tos 		= ', 	n_tos
		print '  	n_tistos 	= ', 	n_tistos
		print ' #---------------------------------------#'


	def getTisEff(self): #return a valAndErr object
		eff = self.n_tistos / self.n_tos
		print '   The eff = ', eff
		err_binom = sqrt(  (eff*(1-eff))  / self.n_trig )
		print '   The err_binom = ', err_binom
		return valAndErr(eff,err_binom)

	def getTosEff(self):
		eff = self.n_tistos / self.n_tis
		err_binom = sqrt(  (eff*(1-eff))  / self.n_trig )
		return valAndErr(eff,err_binom)

	def getEff(self):
		a = float(self.a)
		b = float(self.b)
		c = float(self.c)
		d = float(self.d)
                eff = 0.
                errEff = 0.
                if c > 0: #Act normally..
                        eff = ( d*(a+b+c+d)) / ( (b+d)*(c+d) )
                        #Error calculation
                        #sigma^2 = (de/da)^2 * a + (de/db)^2 * b + ...
                        deda = d / ((b+d)*(c+d))
                        dedb = d * (a+c) / ((b+d)**2 * (c+d))
                        dedc = - d * (a+b) / ((b+d) * (c+d)**2)
                        dedd = ( a * (b*c - d**2) + b*c* (b+c+2*d)) / ((b+d)**2 * (c+d)**2)
                        errEff = sqrt( a*(deda**2)  + b*(dedb**2) + c*(dedc**2) + d*(dedd**2) )

                else: # use simplified eff = nTRIG / nTOS  (tistos=tis cancelles out)
                        #This does not work either...
                        # Define eff= x / x-y
                        x = a+b+d
                        y = a

                        eff =  (a+b+d) / float(b+d)
                        effEff = sqrt (x*y*(x+y)) / (x-y)**2

                return valAndErr(eff,errEff)


	def getNsel(self):
		#This is for the combination of the efficiencies in phace space bins
		b = float(self.b)
		c = float(self.c)
		d = float(self.d)

		val  = (b+d)*(c+d) / d
		dNdb = c/d - 1.
		dNdd = 1. - b*c/d**2.
		dNdc = b/d + 1.
		err  = sqrt( c*dNdc**2 + b*dNdb**2 + d*dNdd**2 )

		return valAndErr(val,err)

