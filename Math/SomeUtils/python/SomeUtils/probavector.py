#from math import *

class vector(list):
    
    def __init__(self,x,y,z):
        list.__init__(self,[x,y,z])


    def __add__(self,v2):        

        return vector(self[0]+v2[0],self[1]+v2[1],self[2]+v2[2])

    def __sub__(self,v2):

        return vector(self[0]-v2[0],self[1]-v2[1],self[2]-v2[2])

    
    def __mul__(self,n):

        #if isinstance(n,vector):
            #return sqrt(self[0]*n[0]+self[1]*n[1]+self[2]*n[2])

    
        return vector(n*self[0],n*self[1],n*self[2])

    
    __rmul__=__mul__
    
    def __div__(self,n):
        a = 1./n
        return self*a

    __rdiv__=__div__
    
    def __neg__(self):

        return self*(-1)
    
   
