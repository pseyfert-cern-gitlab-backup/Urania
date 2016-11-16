#############################
# Credits                   #
# Author: Siim Tolk         #
# Date: Autumn 2014         #
# Mail: siim.tolk@cern.ch   #
#############################

# This is a container class for a variable and it's uncertainty.
# It makes propagating uncertainties through simple products and
# divisions easier

# NB! Variable are assumed to be uncorrelated!

from math import *

class valAndErr():
    def __init__(self,value, uncertainty, N=0):
        self._val = float(value)

        #In case the error is Poissonian:
        if uncertainty == 'P':
        if value<0. :
            print '  NB! VALUE SMALLER THAN ZERO!'
            self._err = 0.
        elif value is 0 : self._err = 0.
        else: self._err = sqrt(float(value))
        else: self._err = float(uncertainty)

        #The N is the value of 'all' events in case of efficiency
        self._N = float(N)

        #print 'New valAndErr object created: (', self.getVal(), ',',self.getErr(), ',', self.getN(), ')'

    def info(self):
        print self._val , ' +- ', self._err
        return ''


    # Return the a new valAndErr object of the addition
    def plus(self, b): return valAndErr( self.getVal() + b.getVal() ,
        sqrt( pow(b.getErr(),2 ) + pow(self.getErr(),2)))

    # Return the a new valAndErr object of the subtraction
    def minus(self, b): return valAndErr( self.getVal() - b.getVal() ,
        sqrt( pow(b.getErr(),2 ) + pow(self.getErr(),2)))

    # Return the a new valAndErr object of the product self*err
    #def times(self, b, isEff = 0):
    def times(self, b, isEff = 0):
        #if (isEff):
        #	N = self.getN() * b.getN()
        #	eff = self.getVal() * b.getVal()
        #	return valAndErr( eff, sqrt( ( eff*(1-eff) ) / N), N )

        #else:
        return valAndErr( self.getVal() * b.getVal() , sqrt( pow(b.getVal() * self.getErr(),2 ) + pow(self.getVal()*b.getErr(),2)))


    def sqrt(self): return valAndErr( sqrt(self.getVal()), self.getErr() / sqrt(2*self.getVal()), sqrt(self.getN()) )


    # Return the a new valAndErr object of the division self*err
    def over(self, b, isEff = 0):
        if (isEff):
            print '>>Calculate efficiency.. '
            N = b.getVal()
            print '   The N = ', N
            eff = self.getVal() / b.getVal()
            print '   The eff = ', eff
            if eff > 1.0:
            print 'EFFICIENCY OVER 1!!! -> Switching to normal errors..'
            return valAndErr( self.getVal() / b.getVal() , sqrt( pow( self.getErr(),2 ) + pow( self.getVal()*b.getErr() / b.getVal() , 2)) / b.getVal() )

        err_binom = sqrt(  (eff*(1-eff))  / N )

        print '   The err_binom = ', err_binom

        return valAndErr( eff, err_binom, N )

        else:
            return valAndErr( self.getVal() / b.getVal() , sqrt( pow( self.getErr(),2 ) + pow( self.getVal()*b.getErr() / b.getVal() , 2)) / b.getVal() )


    #Getters
    def getVal(self): return self._val
    def getErr(self): return self._err
    def getN(self): return self._N


