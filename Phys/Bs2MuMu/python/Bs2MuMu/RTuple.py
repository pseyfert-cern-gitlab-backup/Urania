import os

from ROOT import *
from array import array

ARRAYSIZE = 200

class RTuple:

   def __init__(self,name,labels):
      self._file = TFile(name+".root","recreate")
      self._tree = TTree("T","example")
      for label in labels:
         i0 = label.find("/")
         i1 = label.find("[")
         i = i0
         if (i1 >0): i = i1
         xlabel = label[:i]
         typ = label[i0+1:]
         typ = typ.lower()
         n = 1
         if (i1>0): n = ARRAYSIZE
         a = array(typ,n*[0])
         setattr(self,xlabel,a)
         self._tree.Branch(xlabel,a,label)

   def fillItem(self,name,values):
      a = getattr(self,name)
      if (isinstance(values,list) or
          isinstance(values,tuple)):
         n =  min(len(values),ARRAYSIZE)
         for i in range(n):
            a[i] = values[i]
      else:
         a[0]= values

   def fill(self):
      self._tree.Fill()

   def close(self):
      self._file.Write()
      self._file.Close()

class RTree:
   def __init__(self,name):
      self.tree = TTree(name,name)
      
   def column(self,label,number):
      if label not in dir(self):
         a = array('f',[0.])
         setattr(self,label,a)
         self.tree.Branch(label,a,label+"/F")
      a = getattr(self,label)
      a[0] = number
      
   def write(self):
      self.tree.Fill()
   
class ToyNTupSvc:

   def __init__(self,name):

      self._file = TFile(name+".root","recreate")
      self.trans = {}
      #self.algs
      
   def GetTree(self,name):
      #i = 0
      #name0 = name
      #while 1:
         
         #if name not in self.trans.keys(): break
         #i+=1
         #name = name0+"_"+str(i)
         
      if name not in self.trans.keys():self.trans[name] = RTree(name)
      return self.trans[name]

   def end(self):
      for tuple in self.trans.keys():
         self.trans[tuple].tree.Write()
      self._file.Close()

      


####################################

def Viewer(char):
   char=char+".root"
   f=TFile(char,"r")
   t=f.Get("T")
   t.StartViewer()
   
def test():
   labels = ("i/I","n/I","x[n]/F")
   tup = RTuple("testing",labels)
   for i in range(10):
      tup.fillItem("i",i)
      tup.fillItem("n",i+1)
      tup.fillItem("x",range(i+1))
      tup.fill()
   tup.close()
