from GLBasic import *
from dataManage import *

alpha = 2

class NewKarlen:
    def __init__(self,signal, noise, keys):
         sL,bL =[],[]
         for ki in keys:
             sL.append(GetKey(signal,ki))
             bL.append(GetKey(noise,ki))
         self.Operator = GaussDiscriminantOperator(sL,bL)
         self.keys = keys
         self.Ns = len(signal)
         self.Nb = len(noise)
         #self.x = len(keys)*[0.]
    def __call__(self,entry, prefix = None):
        q = str(entry.__class__)
        if q.find("channelData") != -1: return self.ApplyOverChannel(entry, prefix)
        N = len(self.keys)
        x =[]
        for i in range(N):
            x.append(entry[self.keys[i]])
        return self.Operator(x)
    def ApplyOverChannel(self,sample,prefix):
        for entry in sample:
            y = self(entry)
            for ki in y.keys():
                entry[prefix + ki + "."] = y[ki]

        
          
  
        
## class IsoGL:
##     def __init__(self, sig, bkg, keys, isos = ['mu1iso5', 'mu2iso5']):
##         sig.desagrupate()
##         bkg.desagrupate()
##         NS = len(sig)
##         NB = len(bkg)
        
##         sig.addVariable("maxIso",isos,max)
##         bkg.addVariable("maxIso",isos,max)
##         sig.addVariable("minIso",isos,min)
##         bkg.addVariable("minIso",isos,min)
        
##         allIso = Cut("maxIso<1")
##         oneIso = trigger()
##         oneIso.addCut("maxIso>0")  # iso1>0 || iso2 >0
##         oneIso.addCut("minIso<1")  # iso1 ==0 || iso2 == 0
##         noIso = Cut("minIso>0")    # iso1>0 && iso2>0
##         self.keys = keys
##         self.isos = isos
        

##         sigs, bkgs, self.GLs, self.Ns, self.Nb, self.Ps, self.Pb= {},{},{},{},{}, {},{}
##         sigs[0] = allIso(sig)
##         sigs[1] = oneIso(sig)
##         sigs[2] = noIso(sig)
        
##         bkgs[0] = allIso(bkg)
##         bkgs[1] = oneIso(bkg)
##         bkgs[2] = noIso(bkg)
        
##         for i in sigs.keys():
##             sigs[i].desagrupate()
##             bkgs[i].desagrupate()
##             self.Ns[i] = len(sigs[i])
##             self.Nb[i] = len(bkgs[i])
##             self.Ps[i] = self.Ns[i]*1./NS
##             self.Pb[i] = self.Nb[i]*1./NB
            
##             self.Nb[i] = len(bkgs[i])
##             self.GLs[i] = NewKarlen(sigs[i],bkgs[i],keys)
##         sig.desagrupate()
##         bkg.desagrupate()
##         N = len(self.keys)
##         deltaList = []
##         print "Final chi2 adding isolation samples"
##         for entry in sig:
##             iso1 = entry[isos[0]]
##             iso2 = entry[isos[1]]
            
##             maxiso = max(iso1,iso2)
##             miniso = min(iso1,iso2)

##             if (iso1 ==0) and (iso2 ==0): k = 0
##             elif (iso1==0) or (iso2==0) : k=1
##             else : k = 2
            
##             x =[]
##             for i in range(N):
##                 x.append(entry[self.keys[i]])
##             out1 = self.GLs[k].Operator(x)
##             chi2s = -alpha*log(self.Ps[k]) + out1["chi2s"]
##             chi2b = -alpha*log(self.Pb[k]) + out1["chi2b"]
##             delta = chi2b-chi2s

##             if delta == 0.0: print "weird event"
##             deltaList.append(delta)
##         self.usb = UniFunc(deltaList)
    
            
            
        
##     def __call__(self,entry, prefix = None):
##         q = str(entry.__class__)
##         if q.find("channelData") != -1: return self.ApplyOverChannel(entry, prefix)
##         N = len(self.keys)
##         iso1 = entry[self.isos[0]]
##         iso2 = entry[self.isos[1]]

##         maxiso = max(iso1,iso2)
##         miniso = min(iso1,iso2)
        
##         if (iso1 ==0) and (iso2 ==0): k = 0
##         elif (iso1==0) or (iso2==0) : k=1
##         else : k = 2
        
##         x =[]
##         for i in range(N):
##             x.append(entry[self.keys[i]])
##         out1 = self.GLs[k].Operator(x)
##         out = {}
##         for key in out1.keys():
##             out["m"+key] = out1[key]
##         out["chi2s"] = -alpha*log(self.Ps[k]) + out1["chi2s"]
##         out["chi2b"] = -alpha*log(self.Pb[k]) + out1["chi2b"]
##         out["delta"] = out["chi2b"] - out["chi2s"]
##         out["sb"] = self.usb(out["delta"])
##         return out
    
##     def ApplyOverChannel(self,sample,prefix):
##         for entry in sample:
##             y = self(entry)
##             for ki in y.keys():
##                 entry[prefix + ki + "."] = y[ki]

            
    
        

        
        
        
## class IsoGL_noC:
##     def __init__(self, sig, bkg, keys, isos = ['mu1iso5', 'mu2iso5']):
##         sig.desagrupate()
##         bkg.desagrupate()
##         NS = len(sig)
##         NB = len(bkg)
        
##         sig.addVariable("maxIso",isos,max)
##         bkg.addVariable("maxIso",isos,max)
##         sig.addVariable("minIso",isos,min)
##         bkg.addVariable("minIso",isos,min)
        
##         allIso = Cut("maxIso<1")
##         oneIso = trigger()
##         oneIso.addCut("maxIso>0")  ### iso1>0 || iso2 >0
##         oneIso.addCut("minIso<1")  ### iso1 ==0 || iso2 == 0
##         noIso = Cut("minIso>0")    ### iso1>0 && iso2>0
##         self.keys = keys
##         self.isos = isos
##         self.GL = NewKarlen(sig,bkg,keys)

##         sigs, bkgs, self.Ns, self.Nb, self.Ps, self.Pb= {},{},{},{},{}, {}
##         sigs[0] = allIso(sig)
##         sigs[1] = oneIso(sig)
##         sigs[2] = noIso(sig)
        
##         bkgs[0] = allIso(bkg)
##         bkgs[1] = oneIso(bkg)
##         bkgs[2] = noIso(bkg)
        
##         for i in sigs.keys():
##             sigs[i].desagrupate()
##             bkgs[i].desagrupate()
##             self.Ns[i] = len(sigs[i])
##             self.Nb[i] = len(bkgs[i])
##             self.Ps[i] = self.Ns[i]*1./NS
##             self.Pb[i] = self.Nb[i]*1./NB
            
##             self.Nb[i] = len(bkgs[i])
            
##         sig.desagrupate()
##         bkg.desagrupate()
##         N = len(self.keys)
##         deltaList = []
##         print "Final chi2 adding isolation samples"
##         for entry in sig:
##             iso1 = entry[isos[0]]
##             iso2 = entry[isos[1]]
            
##             maxiso = max(iso1,iso2)
##             miniso = min(iso1,iso2)

##             if (iso1 ==0) and (iso2 ==0): k = 0
##             elif (iso1==0) or (iso2==0) : k=1
##             else : k = 2
            
##             x =[]
##             for i in range(N):
##                 x.append(entry[self.keys[i]])
##             out1 = self.GL.Operator(x)
##             chi2s = -alpha*log(self.Ps[k]) + out1["chi2s"]
##             chi2b = -alpha*log(self.Pb[k]) + out1["chi2b"]
##             delta = chi2b-chi2s

##             #if delta == 0.0: print "weird event"
##             deltaList.append(delta)
##         self.usb = UniFunc(deltaList)
    
            
            
        
##     def __call__(self,entry, prefix = None):
##         q = str(entry.__class__)
##         if q.find("channelData") != -1: return self.ApplyOverChannel(entry, prefix)
##         N = len(self.keys)
##         iso1 = entry[self.isos[0]]
##         iso2 = entry[self.isos[1]]

##         maxiso = max(iso1,iso2)
##         miniso = min(iso1,iso2)
        
##         if (iso1 ==0) and (iso2 ==0): k = 0
##         elif (iso1==0) or (iso2==0) : k=1
##         else : k = 2
        
##         x =[]
##         for i in range(N):
##             x.append(entry[self.keys[i]])
##         out1 = self.GL.Operator(x)
##         out = {}
##         for key in out1.keys():
##             out["m"+key] = out1[key]
##         out["chi2s"] = -alpha*log(self.Ps[k]) + out1["chi2s"]
##         out["chi2b"] = -alpha*log(self.Pb[k]) + out1["chi2b"]
##         out["delta"] = out["chi2b"] - out["chi2s"]
##         out["sb"] = self.usb(out["delta"])
##         return out
    
##     def ApplyOverChannel(self,sample,prefix):
##         for entry in sample:
##             y = self(entry)
##             for ki in y.keys():
##                 entry[prefix + ki + "."] = y[ki]

            
    
        

        
        
## class IsoGL2:
##     def __init__(self, sig, bkg, keys, isos = ['mu1iso5', 'mu2iso5']):
##         sig.desagrupate()
##         bkg.desagrupate()
##         NS = len(sig)
##         NB = len(bkg)
        
##         sig.addVariable("maxIso",isos,max)
##         bkg.addVariable("maxIso",isos,max)
##         sig.addVariable("minIso",isos,min)
##         bkg.addVariable("minIso",isos,min)
        
##         allIso = Cut("maxIso<1")
##         oneIso = trigger()
##         oneIso.addCut("maxIso>0")  ### iso1>0 || iso2 >0
##         oneIso.addCut("minIso<1")  ### iso1 ==0 || iso2 == 0
##         noIso = Cut("minIso>0")    ### iso1>0 && iso2>0
##         self.keys = keys
##         self.isos = isos
##         self.isov = {0:[], 1:["maxIso"], 2:isos}

##         sigs, bkgs, self.GLs, self.Ns, self.Nb, self.Ps, self.Pb= {},{},{},{},{}, {},{}
##         sigs[0] = allIso(sig)
##         sigs[1] = oneIso(sig)
##         sigs[2] = noIso(sig)
        
##         bkgs[0] = allIso(bkg)
##         bkgs[1] = oneIso(bkg)
##         bkgs[2] = noIso(bkg)
        
##         for i in sigs.keys():
##             sigs[i].desagrupate()
##             bkgs[i].desagrupate()
##             self.Ns[i] = len(sigs[i])
##             self.Nb[i] = len(bkgs[i])
##             self.Ps[i] = self.Ns[i]*1./NS
##             self.Pb[i] = self.Nb[i]*1./NB
            
##             self.Nb[i] = len(bkgs[i])
##             self.GLs[i] = NewKarlen(sigs[i],bkgs[i],keys + self.isov[i])
##         sig.desagrupate()
##         bkg.desagrupate()
##         N = len(self.keys)
##         deltaList = []
##         print "Final chi2 adding isolation samples"
##         for entry in sig:
##             iso1 = entry[isos[0]]
##             iso2 = entry[isos[1]]
            
##             maxiso = max(iso1,iso2)
##             miniso = min(iso1,iso2)

##             if (iso1 ==0) and (iso2 ==0): k = 0
##             elif (iso1==0) or (iso2==0) : k=1
##             else : k = 2
            
##             x =[]
##             for i in range(N):
##                 x.append(entry[self.keys[i]])
##             for isov in self.isov[k]:
##                 x.append(entry[isov])
##             out1 = self.GLs[k].Operator(x)
##             chi2s = -alpha*log(self.Ps[k]) + out1["chi2s"]
##             chi2b = -alpha*log(self.Pb[k]) + out1["chi2b"]
##             delta = chi2b-chi2s

##             #if delta == 0.0: print "weird event"
##             deltaList.append(delta)
##         self.usb = UniFunc(deltaList)
    
            
            
        
##     def __call__(self,entry, prefix = None):
##         q = str(entry.__class__)
##         if q.find("channelData") != -1: return self.ApplyOverChannel(entry, prefix)
##         N = len(self.keys)
##         iso1 = entry[self.isos[0]]
##         iso2 = entry[self.isos[1]]

##         maxiso = max(iso1,iso2)
##         miniso = min(iso1,iso2)
##         entry["maxIso"] = maxiso
        
##         if (iso1 ==0) and (iso2 ==0): k = 0
##         elif (iso1==0) or (iso2==0) : k=1
##         else : k = 2
        
##         x =[]
##         for i in range(N):
##             x.append(entry[self.keys[i]])
##         for isov in self.isov[k]:
##             x.append(entry[isov])
##         out1 = self.GLs[k].Operator(x)
##         if "s" + str(len(self.keys+self.isos)-1) not in out1.keys():
##             out1["s"+ str(len(self.keys+self.isos)-1)] = 0
##             out1["b"+ str(len(self.keys+self.isos)-1)] = 0
##         if "s" + str(len(self.keys+self.isos)-2) not in out1.keys():
##             out1["s"+ str(len(self.keys+self.isos)-2)] = 0
##             out1["b"+ str(len(self.keys+self.isos)-2)] = 0
            
##         out = {}
##         for key in out1.keys():
##             out["m"+key] = out1[key]
##         out["chi2s"] = -alpha*log(self.Ps[k]) + out1["chi2s"]
##         out["chi2b"] = -alpha*log(self.Pb[k]) + out1["chi2b"]
##         out["delta"] = out["chi2b"] - out["chi2s"]
##         out["sb"] = self.usb(out["delta"])
##         return out
    
##     def ApplyOverChannel(self,sample,prefix):
##         for entry in sample:
##             y = self(entry)
##             for ki in y.keys():
##                 entry[prefix + ki + "."] = y[ki]

            
    
