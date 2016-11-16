#from ROOT import *
#from os import *

def cnvTCK(x) :
    if type(x) == str and x[0:2] == '0x' : return '0x%08x'%int(x,16)
    return '0x%08x'%int(x)


def triggerCategory(rawTCK):
    tck = cnvTCK(rawTCK)
    if (tck=='0x0013001f') or (tck=='0x0017001f') or (tck=='0x0019001f'):
        #strp9, ~2.2pb-1
        return 1
    if (tck=='0x00190024'):
        #strp9, 1pb-1
        return 2
    if (tck=='0x001d0030') or (tck=='0x001e0030'):
        #strp10, 2.2pb-1
        return 3
    if (tck=='0x001f0029') or (tck=='0x0025002a')\
           or (tck=='0x002a002a') or (tck=='0x002b002a')\
           or (tck=='0x002e002a'):
        #strp10, 19.1pb-1
        return 4

    if (tck=='0x0024002c') or (tck=='0x0025002c') or\
           (tck=='0x002a002c') or (tck=='0x002e002c'):
        #strp11, 12.7pb-1
        return 5
    print "WARNING, TCK not in list, mini data or bug?, setting category 6"
    return 6
    
    
def getTISEff(tree,tosList, tisList, cuts):
    #eTis = eTIS&eTOS/eTOS
    tosArg=cuts+'&&'
    tisArg=cuts+'&&'
    for name in tisList:
        tisArg=tisArg+name+"Tis>0 ||"
    tisArg=tisArg+'0' #stupid thing to remove last or
    nTis=tree.GetEntries(tisArg)

    for name in tosList:
        tosArg=tosArg+name+"Tos>0 ||"
    tosArg=tosArg+'0' #stupid thing to remove last or
    nTos=tree.GetEntries(tosArg)


    print "tis:",nTis," nTos: ",nTos


L0MuTis = "(L0MuonTis || L0DiMuonTis)"
Hlt1MuTis = '(Hlt1DiMuonIPCL0SegTis||Hlt1TrackMuonTis||Hlt1SingleMuonIPCL0Tis||Hlt1DiMuonIPC2L0Tis||Hlt1DiMuonNoIPL0DiTis||Hlt1DiMuon4BsMuMuTis||Hlt1SingleMuon4BsMuMuTis||Hlt1DiMuonIPCL0DiTis||Hlt1DiMuonNoIPL0SegTis||Hlt1DiMuonNoIP2L0Tis||Hlt1SingleMuonNoIPL0Tis)'

MuTis = "("+ L0MuTis + " && " + Hlt1MuTis + ")"

L0MuDecision = "(L0MuonDecision || L0DiMuonDecision)"
Hlt1MuDecision = '(Hlt1DiMuonIPCL0SegDecision||Hlt1TrackMuonDecision||Hlt1SingleMuonIPCL0Decision||Hlt1DiMuonIPC2L0Decision||Hlt1DiMuonNoIPL0DiDecision||Hlt1DiMuon4BsMuMuDecision||Hlt1SingleMuon4BsMuMuDecision||Hlt1DiMuonIPCL0DiDecision||Hlt1DiMuonNoIPL0SegDecision||Hlt1DiMuonNoIP2L0Decision||Hlt1SingleMuonNoIPL0Decision)'

MuDecision = "("+ L0MuDecision + " && " + Hlt1MuDecision + ")"


L0MuTos = "(L0MuonTos || L0DiMuonTos)"
Hlt1MuTos = '(Hlt1DiMuonIPCL0SegTos||Hlt1TrackMuonTos||Hlt1SingleMuonIPCL0Tos||Hlt1DiMuonIPC2L0Tos||Hlt1DiMuonNoIPL0DiTos||Hlt1DiMuon4BsMuMuTos||Hlt1SingleMuon4BsMuMuTos||Hlt1DiMuonIPCL0DiTos||Hlt1DiMuonNoIPL0SegTos||Hlt1DiMuonNoIP2L0Tos||Hlt1SingleMuonNoIPL0Tos)'

MuTos = "("+ L0MuTos + " && " + Hlt1MuTos + ")"
