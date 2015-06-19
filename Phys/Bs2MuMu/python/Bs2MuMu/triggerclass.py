from dev_channelclass import *
from ROOT import TGraph


class Cut:
    """(variableName, Cut Value, Mode : "SM" = Survives if variable > Cut Value
                                                                            "Sm" = survives if minor)
        """
    def __init__(self,string):
        #print "Remember: UseOver method returns data, then please use it as  dummy = Cut.UseOver(input)"
        #print "because in other case python will print all the output data in screen"
        logOpPOS = max(string.find("<"),string.find(">"))
        string.replace(" ","")
        self.Var=string[0:logOpPOS]

        if string[logOpPOS+1]=="=":
            self.logOp = string[logOpPOS:logOpPOS + 2]
            logOpPOS += 1

        else: self.logOp = string[logOpPOS]
        
        self.value=float(string[logOpPOS+1:])
        self.estrinj = string

    def UseOver(self,ch,name = "--Noname--"):
        """ UseOver( ch= channel or dictionary with channels)
            WARNING : Returns a dictionary of channels, then,
            if anything is in the left part of the equality, the complet objet will be printed
            in screen !!
        """
        if isinstance(ch,channelData):
            nN = not ch.agrupated
            
            if nN:
                ch.agrupateInEvents()
            out = []
            logOp = self.logOp
            if logOp == "<":
                for event in ch:
                    ev = []
                    for entry in event:
                        if entry[self.Var] < self.value : ev.append(entry)
                    if ev!= [] : out.append(ev)
            if logOp == ">":
                for event in ch:
                    ev = []
                    for entry in event:
                        if entry[self.Var] > self.value : ev.append(entry)
                    if ev != []: out.append(ev)
                    
            if logOp == "<=":
                ev = []
                for event in ch:
                    for entry in event:
                        if entry[self.Var] <= self.value : ev.append(entry)
                    if ev != [] : out.append(ev)
            if logOp == ">=":
                for event in ch:
                    ev = []
                    for entry in event:
                        if entry[self.Var] >= self.value : ev.append(entry)
                    if ev != [] : out.append(ev)
            #survives = (len(out) != 0)
            
            out = channelData(out)
            
            out.agrupateInEvents()
            ch.agrupateInEvents()
            if len(ch):
                print "Efficiency cut " +self.estrinj +" on channel " + name +": ", len(out)*(100./len(ch))," %"
            else: print "Cut " + self.estrinj + " unnecesary for chanel " + name
            if nN:
                out.desagrupate()
                ch.desagrupate()
        if isinstance(ch,channelGroup):
            out = {}
            for channel in ch.keys():
                out[channel] = self.UseOver(ch[channel],name = channel)
                
                    
       
        return out
    def __call__(self, ch):
        return self.UseOver(ch)
    
    def show(self):
        print self.estrinj
class selection:
    """(variableName, Number of things to be selected, Mode : "SM" = Survives if variable > Cut Value
                                                                            "Sm" = survives if minor)
        """
    def __init__(self,variable="ptV",number=1,mode="SM"):
        
        self.Var=variable
        self.Number=number
        self.mode=mode

    def UseOver(self,ch):
        """ UseOver( ch= channel or dictionary with channels)
            WARNING : Returns a dictionary of channels, then,
            if anything is in the left part of the equality, the complet objet will be printed
            in screen !!
        """
         
        if  not "keys" in dir(ch):
             ch2=triggermanager2r4.selectionStep(ch,self.Var,self.Number,self.mode)
        else:
            ch2={}
            for cl in ch.keys():
                ch2[cl] =triggermanager2r4.selectionStep(ch[channel],self.Var,self.Number,self.mode)
        return ch2
    def __call__(self, ch):
        return self.UseOver(ch)
    def show(self):
        print  "Uses variable " + self.Var
        print  "Catch  " + str(self.Number) + " objects"
        if self.mode=="SM" : aux01= "greatest"
        if self.mode=="Sm" : aux01= "smallest"
        print  "With " +self.Var +" "+aux01
        
class trigger(dict):
    """(number of steps --not cuts !! --, 1 by default. Steps are used for selecting)
    """
    def __init__(self,n=1):
            
        dict.__init__(self)
        self.steps=n
        self.stepList=[]
        self.selections={}
        for i in range(n):
            key = "step"+str(i+1)    
            self[key]=[]
            self.stepList.append(key)
            self.selections[key]=0
    def __mul__(self,t2):

        out=trigger(self.steps+t2.steps)
        for key in self.stepList:           
           out[key]=self[key]
           out.stepList.append(key)
           
        for i in range(self.steps,t2.steps):
           key = "step"+str(i+1)
           key2="step" +str(i-self.steps+1)
           out.stepList.append(key)
           out[key]=t2[key]
        
        return out

    def addCut(self,cut,stp=1):
        """addSelection(cut,step=1)
        """
        key = "step"+str(stp)
        if isinstance( cut, str ): cut = Cut(cut) 
        self[key].append(cut)

    def addSelection(sef,sel,stp=1):
        """addSelection(selection,step=1)
        """
        key = "step"+str(stp)
        if not self.selections[key]: self.selections[key]=[sel]
        else: self.selections[key].append(sel)
        
    def UseOver(self,ch):
        """ UseOver( ch= channel or dictionary with channels)
            WARNING : Returns a dictionary of channels, then,
            if anything is in the left part of the equality, the complet objet will be printed
            in screen !!
        """
        ch2=ch
        #ch.agrupateInEvents()
        ch2.agrupateInEvents()
        for key in self.stepList:
            if self.selections[key]:
                ch2=selections[key].UseOver(ch2)
            for cut in self[key]:
                ch2=cut.UseOver(ch2)
        nn=None
        if not ('keys' in dir(ch2)):
            nn = 1
            ch2={"--Noname--":ch2}
            
        for channel in ch2.keys():
            if "keys" in ch: pass
             #   initial=len(ch[channel])    
            else:
                ch.agrupateInEvents()
                initial=len(ch)
            initial=float(initial)
            ch2[channel].agrupateInEvents()
            ef=100.*len(ch2[channel])/initial
            print  "Trigger Efficiency on channel " + channel + str(ef)
        if nn : ch2=ch2["--Noname--"] 
        return ch2

    def __call__(self, ch):
        return self.UseOver(ch)
    def show(self):
        for key in self.stepList:
             if self.selections[key]:
                 self.selections[key].show()
             for cut in self[key]:
                cut.show()
class powerLoop:
    def __init__(self, key):
        self.key = key
    def __call__( self, sig, bkg, start = True, end = True, steps = 100 ):
        m, rms = sig.RMS(self.key)
        m2, rms = bkg.RMS(self.key)
        eq = "<"
        if m > m2: eq = ">"
        k = sig.takeKey( self. key )
        k.sort()
        if start == True: start = k[0]
        if end == True: end = k[-1]
        pas = (end - start) * 1./steps
        g = TGraph()
        iNs = 100./len(sig)
        iNb = 100./len(bkg)
        for i in range(steps):
            ct = Cut( self.key + eq + str(start + pas * i ))
            du1 = ct(sig)
            du2 = ct(bkg)
            g.SetPoint(i, 100 - len(du2)*iNb, len(du1) * iNs)
        g.GetXaxis().SetTitle("Rejection")
        g.GetYaxis().SetTitle("Efficiency")
        return g    
        
        
def evtDiag(ch1,ch2):
    """Fraction of events from ch1 found in ch2"""
    #N = 0
    ch1.agrupateInEvents()
    ch2.agrupateInEvents()
    Nok = 0
    #oResto = 0
    for event in ch1:
        evtNum = event[0]["evtNum"]
        runNum = event[0]["runNum"]
        for uoeo in ch2:
            xevt = uoeo[0]["evtNum"]
            xrun = uoeo[0]["runNum"]
            if xevt == evtNum and xrun == runNum:
                Nok += 1
                break
    return Nok*1./len(ch1)

def power(s,b, var, m, M, steps = 100, sg = ">"):
    p = (M-m)*1./(steps-1)
    s.desagrupate()
    b.desagrupate()
    Ns = len(s)
    Nb = len(b)
    Nsi = 1./Ns
    Nbi = 1./Nb
    g = TGraph()
    for i in range(steps):
        ct = m+p*i
        cut = Cut(var + sg + str(ct))
        s1 = cut(s)
        b1 = cut(b)
        s1.desagrupate()
        b1.desagrupate()
        eff = len(s1)*Nsi
        ret = len(b1)*Nbi
        g.SetPoint(i, 1-ret, eff)
    return g
    
