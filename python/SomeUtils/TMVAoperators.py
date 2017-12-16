from ROOT import *
import cPickle
from SomeUtils.NewKarlen import *
#gROOT.ProcessLine(".x $SOMEUTILSROOT/src/vdouble.C")#++")


class TMVAoperator:
    def __init__(self, filename, methodname, variables):
        gROOT.LoadMacro(filename + "++" )
        self.variables = variables
        self.b = std.vector(std.string)()
        for var in variables:
            self.b.push_back(var)
        self.op =globals()["Read" + methodname](self.b) 
        self.stdvector = std.vector(Double)(len(variables))#vdouble(len(variables))
        print methodname, " from ", filename, " initialized successfully"
        
    def GetMvaValue(self,input):
        if isinstance(input,dict):  #### if the input is a dictionary
            x0 = []
            for var in self.variables:
                x0.append(input[var])
            return self.GetMvaValue(x0)
        if isinstance(input, TTree): #### if the input is a TTree
            x0 = []
            for var in self.variables:
                x0.append(getattr(input, var))
            return self.GetMvaValue(x0)
        #print len(input)
        for i in range(len(input)): #### if the input is a list of numbers
            self.stdvector[i] = input[i]
         #   print input[i],self.stdvector.V[i] , i
        a = self.op.GetMvaValue(self.stdvector) ### Don't forget the .V !!!!!
        return a
    def __call__(self,input):
        return self.GetMvaValue(input)


def DoCummulative(ttree, op):
     l = []
     for i in range(ttree.GetEntries()):
         ttree.GetEntry(i)
         l.append(op(ttree))
     uf = UniFunc(l)
     return uf

class TMVAoperatorFlat:
    def __init__(self, filename, methodname, variables, flatfile):
        self.tmva = TMVAoperator( filename, methodname, variables)
        self.ufv = cPickle.load(file(flatfile))
    def __call__(self,input):
        return self.ufv(self.tmva(input))
        

### Some examples:


#yury = TMVAoperator("Y9.C","BDTD",["Blife_ps", "lessIPSmu", "isoSum", "Bpt", "CDF_iso_CDF", "minpt", "Cosnk", "DOCA", "Bip_r" ])
                   

#yury = MVAoperator("./weights/TMVAClassification_BDTD.class.C","BDTD",
     #              ["var12","var3","var4","var11","var8","var9","var14","var16","var15"])


## yury = TMVAoperator(os.environ["BS2MUMUROOT"] + "/src/pseudoYury.C","BDTD", ["Bip","DOCA","lessIPSmu", "Blife_ps","Bpt", "isoSum","minpt", "Cosnk", "CDF_iso"])

## other = TMVAoperator(os.environ["BS2MUMUROOT"] + "/src/bBDTG.C","BDTGG",["Bip","DOCA","lessIPSmu", "Blife_ps","Bpt","minpt","mu1iso5","mu2iso5"])

## other2 = TMVAoperator(os.environ["BS2MUMUROOT"] + "/src/aBDTG.C","BDTG",["Bip","DOCA","lessIPSmu", "Blife_ps","Bpt","minpt","otherB_boost_angle","mu1iso5","mu2iso5"])

## ## ## f_yury_test = TFile("/afs/cern.ch/user/s/scheglov/public/var_response_data_strip12_31.root")
## ## ## signal_test = f_yury_test.Get("TreeS")
## ## ## bkg_test = f_yury_test.Get("TreeB")


## from Bs2MuMu.smartpyROOT import *
## from Bs2MuMu.triggerclass import *
## signal_train, f1      = getTuple("~/vol5/NTuples/Bsmumu_trainb")
## bkg_train, f3      = getTuple("~/vol5/NTuples/dimuonMCmc10d_Bsb")
## signal_test, f2      = getTuple("~/vol5/NTuples/Bsmumu_testb")
## bkg_test, f4      = getTuple("~/vol5/NTuples/dimuonMCmc10u_Bsb")
## s = channelData(fromRootToListDic(signal_test))
## b = channelData(fromRootToListDic(bkg_test))

## s2 = channelData(fromRootToListDic(signal_train))
## b2 = channelData(fromRootToListDic(bkg_train))

## for entry in s:
##     entry["BDT"] = yury.GetMvaValue(entry)
##     entry["aBDT"] = other.GetMvaValue(entry)
##     entry["bBDT"] = other2.GetMvaValue(entry)
## for entry in b:
##     entry["BDT"] = yury.GetMvaValue(entry)
##     entry["aBDT"] = other.GetMvaValue(entry)
##     entry["bBDT"] = other2.GetMvaValue(entry)


## ## for entry in s2:
## ##     entry["BDT"] = yury.GetMvaValue(entry)
## ##     entry["aBDT"] = other.GetMvaValue(entry)
## ## for entry in b2:
## ##     entry["BDT"] = yury.GetMvaValue(entry)
## ##     entry["aBDT"] = other.GetMvaValue(entry)
## ## s.compare(b,"BDT")


## u1 = DoCummulative(signal_test, yury)
## u2 = DoCummulative(signal_test, other)
## u3 = DoCummulative(signal_test, other2)

## for entry in s:
##     entry["BDTFlat"] = u1(entry["BDT"])
##     entry["aBDTFlat"] = u2(entry["aBDT"])
##     entry["bBDTFlat"] = u3(entry["bBDT"])

## for entry in b:
##     #entry["BDTFlat"] = u(entry["BDT"])
##     entry["BDTFlat"] = u1(entry["BDT"])
##     entry["aBDTFlat"] = u2(entry["aBDT"])
##     entry["bBDTFlat"] = u3(entry["bBDT"])


## #gl = NewKarlen(s2,b2, ["Bip","DOCA","lessIPSmu", "Blife_ps","Bpt","minpt", "otherB_boost_angle","mu1iso5","mu2iso5"])
## #gl(b,"GLY")

