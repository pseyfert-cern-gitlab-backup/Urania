import root_numpy
import pandas
import numpy
from hep_ml import reweight

varsOfInterest = [
#'nSPD', #will not use it for training the MVA for selection
#'nVelo', #will not use it for training the MVA
'mu1iso5+mu2iso5',
#'TMath::Log10(mu1pt)', 'TMath::Log10(mu2pt)',
'TMath::Log10(Bpt)',
'mu1_track_Chi2DoF', 'mu2_track_Chi2DoF',
'TMath::Log10(Bip)',
#'TMath::Log10(mu1ip)', 'TMath::Log10(mu2ip)',
'lessIPSmu',
'TMath::Log10(Blife_ps)',
'mu1ptot', 'mu2ptot',
'DOCA', #good agreement already
#'C_angle',  #very good agreement already
]

varsToMatch = [
'nSPD',
'nVelo',
#'mu1iso5', 'mu2iso5',
#'TMath::Log10(mu1pt)', 'TMath::Log10(mu2pt)',
'mu1_track_Chi2DoF', 'mu2_track_Chi2DoF',
'TMath::Log10(Bip)',
'TMath::Log10(mu1ip)', 'TMath::Log10(mu2ip)',
#'lessIPSmu',
#'TMath::Log10(Blife_ps)',
#'mu1ptot', 'mu2ptot',
#'DOCA', #good agreement already
#'C_angle',  #very good agreement already
]



import os, glob
import ROOT
from ROOT import TChain

#FIXME summing over 2011 and 2012
MCfiles = ['./TESTtuples/Upsilon_1S_MC_2011.root','./TESTtuples/Upsilon_1S_MC_2012.root']
MCTree = TChain("A1/A1")
print "importing MC tuples"
for rootfile in MCfiles:
    print rootfile
    MCTree.Add(rootfile)
print "done"
original = root_numpy.tree2rec(MCTree, branches=varsOfInterest)
originalTrain = root_numpy.tree2rec(MCTree, branches=varsToMatch)

DataTree = TChain("A1")
datadir = "./TESTtuples/DATAsPlot/"
os.chdir(datadir)
print "importing all root files in ", datadir, " :"
for rootfile in glob.glob("*.root"):
    print rootfile
    DataTree.Add(rootfile)
print "done"
cut = '!(evtNum%10)'
target      = root_numpy.tree2rec(DataTree,branches=varsOfInterest,selection=cut)
targetTrain = root_numpy.tree2rec(DataTree,branches=varsToMatch,selection=cut)

print "imported original with ", len(original), "entries"
print "imported target with ", len(target), "entries"

original = pandas.DataFrame(original)
target = pandas.DataFrame(target)

sWeights      = root_numpy.tree2rec(DataTree,branches='sW_Y1',selection=cut)
#sWeights = root_numpy.root2array('./TESTtuples/Data_3invfb_prescale1_momrange3.954_3.966.root', treename='A1', branches='sW_Y1')
if len(sWeights)==len(target):
    print "sWeights are loaded correctly"

original_weights = numpy.ones(len(original))


from hep_ml.metrics_utils import ks_2samp_weighted

def getKStest(new_original_weights, new_sWeights, columns):
        for id, column in enumerate(columns, 1):
            print 'KS = ', ks_2samp_weighted(original[column], target[column], weights1=new_original_weights, weights2=new_sWeights), ' over ', column

print "KS test before reweighting:"
getKStest(original_weights, sWeights, varsOfInterest)


### #FIXME for some reasons the normal bin-based reweighting does not work....not relly necessary actually
# bins reweighter test
#bins_reweighter = reweight.BinsReweighter(n_bins=20, n_neighs=1.)
#bins_reweighter.fit(original, target)

#bins_weights = bins_reweighter.predict_weights(original)
#print "with classical bins reweight:"
#getKStest(bins_weights)



print "training GB reweighter on :", varsToMatch
GBreweighterPars = { 'n_estimators': 50, 'learning_rate': 0.1, 'max_depth': 3, 'min_samples_leaf': 1000, 'subsample': 0.6}
print "using the following GB parameters:"
for parname, parval in GBreweighterPars.items():
    print parname, " = ", parval
reweighter = reweight.GBReweighter(n_estimators=GBreweighterPars['n_estimators'], learning_rate=GBreweighterPars['learning_rate'], max_depth=GBreweighterPars['max_depth'], min_samples_leaf=GBreweighterPars['min_samples_leaf'], gb_args={'subsample': GBreweighterPars['subsample']})
reweighter.fit(originalTrain, targetTrain, target_weight=sWeights)
gb_weights = reweighter.predict_weights(originalTrain)

print "KS test after GB reweighter:"
getKStest(gb_weights, sWeights, varsOfInterest)


# test with ROC AUC
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.cross_validation import train_test_split
from sklearn.metrics import roc_auc_score

data = numpy.concatenate([original, target])
labels = numpy.array([0] * len(original) + [1] * len(target))

weights = {}
weights['original'] = original_weights
#weights['bins'] = bins_weights
weights['gb_weights'] = gb_weights

print "test quality with ROC AUC on all variables of interest (not the ones used for training the GB):"
print "If ROC AUC = 0.5 on test, distibutions are equal, if ROC AUC = 1.0, they are ideally separable."

orig_rocauc = 0
for name, new_weights in weights.items():
        W = numpy.concatenate([new_weights / new_weights.sum() * len(target), [1] * len(target)])
        Xtr, Xts, Ytr, Yts, Wtr, Wts = train_test_split(data, labels, W, random_state=42, train_size=0.51)
        clf = GradientBoostingClassifier(subsample=0.3, n_estimators=30).fit(Xtr, Ytr, sample_weight=Wtr)
        ROCAUC = roc_auc_score(Yts, clf.predict_proba(Xts)[:, 1], sample_weight=Wts)
        print name, ROCAUC
        if name=='original':
            orig_rocauc= ROCAUC
        else:
            print "agreement is better by ", (orig_rocauc - ROCAUC)/(orig_rocauc-0.5)*100., "%"





"""
# add gb_Weights to new MC tuple
from ROOT import *
fMC = TFile(MCFileName)
tMC = fMC.Get("A1/A1")
f = TFile("TESTtuples/Upsilons_MC_2011_gb_reweight.root","recreate")
t = tMC.CopyTree('')
gROOT.ProcessLine(\
            "struct MyStruct{\
            Float_t sWFloat;\
            };")
from ROOT import MyStruct
sWValue = MyStruct()
sWBranch = t.Branch("gb_weight", AddressOf(sWValue, 'sWFloat'), "gb_weight/F")
for i in range(t.GetEntries()):
    sWValue.sWFloat = gb_weights[i]
    sWBranch.Fill()
t.Write("",TObject.kOverwrite)
f.Close()
"""
