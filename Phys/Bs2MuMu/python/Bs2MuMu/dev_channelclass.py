from math import *

import smartpyROOT
from ROOT import *
import random
import os

from SomeUtils import GLBasic
from SomeUtils.numericFunctionClass import *
import cPickle


print "Loading channelclas ... "
___f = file(os.environ["SOMEUTILSROOT"] + "/operators/toGauss_2008","r")
erfm1 = cPickle.load(___f)
___f.close()

class channelData(list):

    def __init__(self,thing=None,shape=None,event=0,typ="R",name2 = "T", labels =[]):
        """
       
        """
        if isinstance(thing, str): # thing is a string --> Initialize #from file
            if typ == "R":                          
                t,f=smartpyROOT.getTuple(thing,typ,name2)
                newthing=smartpyROOT.fromRootToListDic(t,labels)
                channelData.__init__(self,newthing,shape,event)
            elif typ == "ASCII":
                dc = smartpyROOT.getASCII(thing)
                newthing = smartpyROOT.dicToList(dc)
                channelData.__init__(self,newthing,shape,event)
            
                
            else:
                print "Sorry, Unknown type of file"

        else:
            list.__init__(self,thing)
            
            if len(thing): self.agrupated = isinstance(thing[0],list)
            else: self.agrupated = 0
            self.shape=shape
            if shape=="vector":
                self.vectorS()
            if event and not self.agrupated:
                self.agrupateInEvents()
            
    def vectorS(self):
        for i in range(len(self)):
            self[i]=smartpyROOT.vectorShape(self[i])
        self.shape="vector"


    def agrupateInEvents(self):
        if self.agrupated: return
        
        channelData.__init__(self,smartpyROOT.agrupateInEvents(self))
        self.agrupated=bool(1)
        
    def desagrupate(self):
        if self.agrupated:
            channelData.__init__(self,smartpyROOT.desagrupate(self))
        self.agrupated=bool(0)

    def changeKey(self,old,new):
        if not (old in self.getKeys()): return "key not found"
        n = self.agrupated
        self.desagrupate()
        channelData.__init__(self,smartpyROOT.changeKey(old,new,self))
        if n:
            self.agrupateInEvents()

    def takeKey(self,ki):
        """(list)
        """
        ag = 0
        if self.agrupated:
            ag = 1
            self.desagrupate()
        out=[]
        for thing in self:
            out.append(thing[ki])
        if ag:
            self.agrupateInEvents()
        return out
    def takeKeys(self,keys):
        """(list)
        """
        if not isinstance(keys,list):
            print "warning, argument is not a list. Trying to return one column"
            return self.takeKey(keys)
        out ={}
        for ki in keys:
            out[ki] = self.takeKey(ki)
        return out
    def save(self,name,typ = "R", keytypes = {}):
        smartpyROOT.saveInTuple(self,name,typ, keytypes)
        return "Done, I think"

    def addVariable(self,name,inputList,function):
         """addVariable(new_variable_name,[var1,var2,...],function)
        """
         smartpyROOT.rAddkey(name,self,inputList,function)

    def getKeys(self):

        if self.agrupated: return self[0][0].keys()
        else: return self[0].keys()

    def kill(self,key):

        if not (key in self.getKeys()): return "key not found"

        n = self.agrupated
        self.desagrupate()
        
        for thing in self:
            thing.__delitem__(key)
        if n:
            self.agrupateInEvents()
       
    def ViewCorrelationPlot_U(self,ki1,ki2):
        k1 = self.takeKey(ki1)
        k2 = self.takeKey(ki2)
        #k1I = GLBasic.GLBasic(k1)
        #k2I = GLBasic.UniFunc(k2)
        #self.addVariable(ki1+"UFV",[ki1],k1I)
        #self.addVariable(ki2+"UFV",[ki2],k2I)
        self.CumulativeShape([ki1,ki2])
        #siz = 1.*len(self)
        #siz = sqrt(siz)
        #siz = siz/3.
        #siz = int(round(siz))
        #h = TH2F(ki1+"Cumulative",ki2+"Cumulative",siz,0.,1.,siz,0.,1.)
        #n = self.agrupated
        ##rangeN = range(len(k1I))
        #if n:
         #   self.desagrupate()
        #for entry in self:
        #    h.Fill(entry[ki1+"UFV"],entry[ki2+"UFV"])
        #self.kill(ki1+"_Cmlt")
        #self.kill(ki2+"_Cmlt")
        n = self.agrupated
        if n:
            self.agrupateInEvents()
        #c = TCanvas()
        #h.GetXaxis().SetTitle(ki1+"Cumulative")
        #h.GetYaxis().SetTitle(ki2+"Cumulative")
        #h.Draw("BOX")
        return self.ViewCorrelationPlot(ki1+"_Cmlt",ki2+"_Cmlt")
    def ViewCorrelationPlot(self,ki1,ki2):
        k1 = self.takeKey(ki1)
        k2 = self.takeKey(ki2)
       
        siz = 1.*len(self)
        siz = sqrt(siz)
        siz = siz/3.
        siz = int(round(siz))
        
        h = TH2F(ki1,ki2,siz,min(k1),max(k1),siz,min(k2),max(k2))
        n = self.agrupated
        if n:
            self.desagrupate()
        for thing in self:
            h.Fill(thing[ki1],thing[ki2])
       
        if n:
            self.agrupateInEvents()
        c = TCanvas()
        h.GetXaxis().SetTitle(ki1)
        h.GetYaxis().SetTitle(ki2)
        h.Draw("BOX")
        return c,h
    
    def UFVcoMatrix(self,ki1,ki2,destroy = 1):
        n = self.agrupated
        if n:
            self.desagrupate()
        self.CumulativeShape([ki1,ki2])
        s=[]
        s.append([0.,0.])
        s.append([0.,0.])
        for thing in self:
            dx = thing[ki1+"_Cmlt"]-0.5
            dy = thing[ki2+"_Cmlt"]-0.5
            s[0][0]+=dx*dx
            s[0][1]+=dx*dy
            s[1][0]+=dy*dx
            s[1][1]+=dy*dy
        if destroy:
            self.kill(ki1+"_Cmlt")
            self.kill(ki2+"_Cmlt")


        if n:
            self.agrupateInEvents()
        return s
        
    def UFVCoRatioQ(self,x,y):
        n = self.agrupated
        if n:
            self.desagrupate()
        self.CumulativeShape([x,y])
        for thing in self:
            thing["aux001"]=abs(thing[x+"_Cmlt"]-0.5)
            thing["aux002"]=abs(thing[y+"_Cmlt"]-0.5)
        M = self.UFVcoMatrix("aux001","aux002")
        self.kill(x+"_U")
        self.kill(y+"_U")
        
        if n:
            self.agrupateInEvents()
        return (M[0][1]+M[1][0])*(1./(M[0][0]+M[1][1]))


    def CumulativeShape(self,list):
        if list == "all":
            uf = self.CumulativeShape(self.getKeys())
            return uf
        n = self.agrupated
        if n:
            self.desagrupate()
        ufs = {}
        for key in list:
            ufs[key] = GLBasic.UniFunc(self.takeKey(key))
        nnn = len(self)
        for ki in list:
            self.addVariable(ki + "_Cmlt",[ki],ufs[ki])

        if n:
            self.agrupateInEvents()
        return ufs
    def GaussianShape(self,list, quil = 1):
        if list == "all": list = self.getKeys()
        n = self.agrupated
        if n:
            self.desagrupate()
        self.CumulativeShape(list)
        if n:
            self.agrupateInEvnets()
        out = {}
        if quil:
            for key in list:
                self.addVariable(key + "_Gauss",[key+ "_Cmlt"],erfm1.UseOver)
                self.kill(key + "_Cmlt")
                out[key] = NF(self.takeKey(key),self.takeKey(key+"_Gauss"))
        else:
            for key in list:
                self.addVariable(key + "_Gauss",[key+"_Cmlt"],erfm1.UseOver)
                out[key] = NF(self.takeKey(key),self.takeKey(key+"_Gauss"))
        return out

   
    def histogram(self,var,min = None,max = None, bins = 100,w = 1.):
        hhh = self.takeKey(var)
        
        if min == None:
            hhh.sort()
            min = hhh[0]
        if max == None:
            hhh.sort()
            hhh.reverse()
            max = hhh[0]
        h = TH1F(var,var,bins,min*1.,max*1.)
        for entry in hhh:
            h.Fill(entry,w)
        return h
    
    def plota(self,listvars):
        h = []
        for var in listvars:
            h.append(self.histogram(var))
        n = len(listvars)
        sqn = int(sqrt(n))
        sqn2 = n*(1./sqn)
        if sqn2 != int(sqn2): sqn2 = int(sqn2)+1
        c = TCanvas()
        c.Divide(sqn,int(sqn2))
        for i in range(n):
            c.cd(i+1)
            h[i].Draw("hist")
        return c, h
        
    def subSample(self,num = None,rdn =1,ini =0):
        nN = not self.agrupated
        if nN:
            self.agrupateInEvents()
        nEvs = len(self)
        if not num:
            num = 0.1*nEvs
            num = int(num)
        #ini = 0
        if rdn: ini = (nEvs - (num+1))*random.random()
        
        ini = int(ini)
        end = ini + num
        out = []
        for i in range(ini,end):
            out.append(self[i])
        out = channelData(out)

        if nN:
            self.desagrupate()
            out.desagrupate()
        return out

    def compare(self,other,key,min = None, max = None, bins = 100):
       ##  aux1 = self
##         aux2 = other
##         N1 = len(aux1)
##         N2 = len(aux2)
##         wd = N1*1./N2
        
        h1 = self.histogram(key,min,max,bins)
        h2 = other.histogram(key,min,max,bins)#,w=wd)

        aux1,aux2 = [], []

        ## for i in range(h1.GetNbinsX()):
##             aux1.append(h1.GetBinContent(i+1))
        
##         for i in range(h2.GetNbinsX()):
##             aux2.append(h2.GetBinContent(i+1))
        
##         aux1.sort()
##         aux2.sort()

        h1.SetLineColor(kRed)
        h2.SetLineStyle(9)
        c = TCanvas()
       
        h1.DrawNormalized()
        h2.DrawNormalized("same")

       # if nN:
        #    self.desagrupate()
        #if nN2:
         #   other.desagrupate()
        return c,h1,h2
    
    def suck(self,list):
        print "Sucking list ...."
        N = self.agrupated
        if N: self.desagrupate()
        if len(list) != len(self):
            print "Impossible, diferent lenghts"
            return
        keis = self.getKeys()
        for i  in range(len(list)):
            entry = list[i]
            for ki in entry:
                if ki not in keis:
                    self[i][ki] = entry[ki]
                else:
                    print "Problem with key ",ki
        if N:
            self.agrupatInEvens()
    def RMS(self,key):
        datos = self.takeKey(key)
        return smartpyROOT.rms(datos)
    def checkForDuplicates(self):
        evt = self.takeKey("evt")
        evt.sort()
        l = []
        for x in evt:
            l.append({"evt":x})
        l = channelData(l)
        print "Candidates:" , len(l)
        l.agrupateInEvents()
        print "Events:", len(l)
        
        
        
        
                    
class channelGroup(dict):
    """(channelNamesList,sufix ...)
    """
    def __init__(self,channelList=None,sufix=None,shape="vector",event=1,typ="R"):
        dict.__init__(self)
        if "append" in dir(channelList):
            
            for channel in channelList:
                self[channel]=channelData(channel+sufix,shape,event,typ)
        else:
            for channel in channelList.keys():
                self[channel]=channelData(channelList[channel],shape,event)
        self.Isufix=sufix
        self.shape=shape
        self.agrupated=bool(event)
        self.check()
        
    def vectorS(self):
        self.shape="vector"
        for key in self.keys():
            self[key].vectorS()
            
    def agrupateInEvents(self):
        if ch.agrupated:
            return
        for key in self.keys():
            self[key].agrupateInEvents()
        self.agrupated=bool(1)

            
    def desagrupate(self):
        self.agrupated=bool(0)
        for key in self.keys():
            self[key].desagrupate()
            
    def addChannel(self,channelName,sfx=None,tp="R"):
        """addChannel(channelName,sufix,type = 'R') , comes from tuple
        """
        if not sfx: sfx=self.Isufix
        self[channelName]=channelData(channelName+sfx,self.shape,self.agrupated,tp)

    def check(self):
        error=0
        for key in self.keys():
            if self.agrupated != self[key].agrupated:
                error =1 #Some channels are agrupated in events, but not all
                print "Incoherent event structure. Remaking it"
        if error:
            for key in self.keys():
                if not self[key].agrupated: self[key].agrupateInEvents()
        error = 0
        for key in self.keys():
            if self.shape != self[key].shape:
                error =1
                print "Incoherent shapes. Remaking it"
        if error:
            for key in self.keys():
                self[key].vectorS()
    def changeKey(self,old,new):
        for key in self.keys():
            self[key].changeKey(old,new)

    def addVariable(self,name,inputList,function):
        """addVariable(new_variable_name,[var1,var2,...],function)
        """
        for key in self.keys():
            self[key].addVariable(name,inputList,function)

    def takeChannel(self,channelName):
        pass
    
    def show(self):
        if self.agrupated:
            for key in ch.keys():
                print key,"  ",len(ch[key]),"  events"
        else:
            self.agrupateInEvents()
            self.show()
            self.desagrupate()
            
   
