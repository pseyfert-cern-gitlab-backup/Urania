# @author jessica prisciandaro (jessica.prisciandaro@cern.ch)
# @date 19.10.2016  

import matplotlib.pyplot as plt
import pandas
from argparse import ArgumentParser
import numpy
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.ensemble import GradientBoostingRegressor, AdaBoostClassifier, ExtraTreesClassifier
from sklearn.tree import DecisionTreeClassifier
from xgboost.sklearn import XGBClassifier
from sklearn.cross_validation import train_test_split, LeaveOneOut
from sklearn.metrics import roc_auc_score, matthews_corrcoef, classification_report
from sklearn.pipeline import make_pipeline
#from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.cross_validation import cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
import root_numpy
import scikit_Function
import ROOT
from pdb import set_trace
from sklearn.neighbors import KNeighborsClassifier
from scikit_BDT_utils import *

############# CATEGORY (TosTos1Tos/TosTos2Tos) #############
category = 'TosTos1Tos'
############################################################


path = 'root://eoslhcb.cern.ch//eos/lhcb/user/m/mramospe/KS0mumu/BDT/Proxies/'
#ifile = 'Ks0mumu_Data2012_MuPtCutOff2500_Proxy_' + category + '.root'
#ifile = 'Ks0mumu_Data2012_MuPtCutOff2500_Proxy_' + category + '.root'
ifile = 'Ks0mumu_Data2012_MuPtCutOff2500_Proxy_' + category + '_CloseSB.root'

from scikit_BDT_vars import BDTVARS
bdtvars = BDTVARS + ['KS0_M', 'eventNumber', 'runNumber']
dataSig = pandas.DataFrame(root_numpy.root2array(path + ifile, 'MCsignal', branches = bdtvars))
dataBkg = pandas.DataFrame(root_numpy.root2array(path + ifile, 'Background', branches = bdtvars))

#dataSig = pandas.DataFrame(root_numpy.root2array('/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/SignalMC_BDTTraining.root','MCsignal'))
#dataBkg = pandas.DataFrame(root_numpy.root2array('/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/Bkg_BDTTraining.root','Background'))

dataSig['Target'] = 1
dataBkg['Target'] = 0

weights = ROOT.TFile.Open("/afs/cern.ch/user/j/jpriscia/cmtuser/Urania_v4r0/Phys/Ks2MuMu/python/Ks2MuMu/BDT/weights.root")
hWeights = weights.Get('hData')

# let's take and apply weights
@numpy.vectorize
def get_weight(ptval):
    return hWeights.GetBinContent(hWeights.FindFixBin(3,ptval))

dataSig['Weight'] = get_weight(dataSig.KS0_PT)
dataBkg ['Weight'] = 1

dataNoCut = dataSig.append(dataBkg, ignore_index=True)

#split data according evt number for k folding 

data=[]
for i in xrange(10):
    print '--- Building data set:', i 
    data.append(dataNoCut[(dataNoCut.eventNumber)%10 ==i])

#variables im going to use in the BDT
features = list(set(dataNoCut.columns) - {'Target','runNumber','eventNumber','KS0_M','KS0_TAU','Weight'})
print '--- Variables used for training:', features

# List of stuff (BDT, BDT decision).. i want to concatenate them later
bdtlist = []
probaVal = []
probaTrain = []
decision = []
decisionTrain_Sig = []
decisionTest_Sig = []
decisionTrain_Bkg = []
decisionTest_Bkg = []
target = []


# do BDT in the k-folding loop
for i in range(len(data)):
    #set_trace()
    train= pandas.concat(data[:i]+data[i+1:],ignore_index=True)
    test = data[i]

    #we might try something better here
    #_bdt=AdaBoostClassifier(algorithm='SAMME',
    #                            base_estimator=DecisionTreeClassifier(criterion='gini',
    #                                                              max_depth=6, max_features=None, max_leaf_nodes=None,
    #                                                              min_samples_leaf=0.01, #100.0
    #                                                              min_samples_split=2, random_state=None, splitter='best'),
    #                        learning_rate=0.05, n_estimators=1000, random_state=None)
    

    #_bdt= GradientBoostingClassifier(
    #    learning_rate=0.02, n_estimators=500, subsample=0.66, random_state=13,
    #    min_samples_leaf=0.2, max_depth=4, max_features=8,verbose=1
    #    )
    #let's do the training with weights

    if category == 'TosTos1Tos':
        _bdt = XGBClassifier(max_depth=4, learning_rate=0.02, n_estimators=2000, silent=True, objective='binary:logistic', nthread=-1, gamma=0, min_child_weight=1, max_delta_step=0, subsample=0.66, colsample_bytree=1, colsample_bylevel=1, reg_alpha=0.4, reg_lambda=1.4, scale_pos_weight=1, base_score=0.5, seed=0, missing=None)
    else:
        _bdt = XGBClassifier(max_depth=4, learning_rate=0.02, n_estimators=800, silent=True, objective='binary:logistic', nthread=-1, gamma=0, min_child_weight=1, max_delta_step=0, subsample=0.66, colsample_bytree=1, colsample_bylevel=1, reg_alpha=0.2, reg_lambda=1.2, scale_pos_weight=1, base_score=0.5, seed=0, missing=None)
        
    print '--- Processing fold:', i
    _bdt.fit(train[features],train.Target,(train.Weight).as_matrix())

    bdtlist.append(_bdt)

    print '--- Calculating BDT values for training and test samples'

    # predict gives binary decision, decision_function gives decision in [-1, 1]
    probaVal.append(_bdt.predict(test[features]))
    probaTrain.append(_bdt.predict(train[features]))
    decision.append(_bdt.predict_proba(test[features])[:,1]) #decision_function

    #print _bdt.evals_result(test[features])
    #decisionTrain_Sig.append(_bdt.decision_function((train[features])[train.Target>0.5]))
    #decisionTrain_Bkg.append(_bdt.decision_function((train[features])[train.Target<0.5]))
    #decisionTest_Sig.append(_bdt.decision_function((test[features])[test.Target>0.5]))
    #decisionTest_Bkg.append(_bdt.decision_function((test[features])[test.Target<0.5]))

    decisionTrain_Sig.append(_bdt.predict_proba((train[features])[train.Target>0.5])[:,1])
    decisionTrain_Bkg.append(_bdt.predict_proba((train[features])[train.Target<0.5])[:,1])
    decisionTest_Sig.append(_bdt.predict_proba((test[features])[test.Target>0.5])[:,1])
    decisionTest_Bkg.append(_bdt.predict_proba((test[features])[test.Target<0.5])[:,1])

    target.append(test.Target) 
    print '--- BDT finished'

##########################################
########### PERFORMANCE ##################  
##########################################

print '--- Studying performance of the BDT output'

targetAll   =  pandas.concat(target,ignore_index=True)
decisionAll = numpy.concatenate(decision)
probaValAll = numpy.concatenate(probaVal)

decisionTrainSigAll = numpy.concatenate(decisionTrain_Sig)
decisionTrainBkgAll = numpy.concatenate(decisionTrain_Bkg)
decisionTestSigAll  = numpy.concatenate(decisionTest_Sig)
decisionTestBkgAll  = numpy.concatenate(decisionTest_Bkg)

print classification_report(targetAll,probaValAll,target_names=["background", "signal"])
print "Area under ROC curve: %.4f"%(roc_auc_score(targetAll, decisionAll))


##########################################
############ROC CURVE  PLOT##############
#########################################

from sklearn.metrics import roc_curve, auc

# Compute ROC curve and area under the curve
'''
fpr, tpr, thresholds = roc_curve(targetAll, decisionAll)
roc_auc = auc(fpr, tpr)

plt.plot(fpr, tpr, lw=1, label='ROC (area = %0.2f)'%(roc_auc))
plt.plot([0, 1], [0, 1], '--', color=(0.6, 0.6, 0.6), label='Luck')
plt.xlim([-0.05, 1.05])
plt.ylim([-0.05, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver operating characteristic')
plt.legend(loc="lower right")
plt.grid()
plt.show()

for i, j in zip(fpr, tpr): print i, j
'''
# My method
makeROC(targetAll, decisionAll)
plt.grid()

overtrainDist(decisionTrainSigAll,
              decisionTrainBkgAll,
              decisionTestSigAll,
              decisionTestBkgAll )
plt.grid()
plt.show()
#bkgrej = []
#for bkg in fpr:
#    bkgrej.append( 1. - bkg )
#plt.plot(tpr, bkgrej, lw=1, label='ROC (area = %0.2f)'%(roc_auc))
#plt.plot([0, 1], [1, 0], '--', color=(0.6, 0.6, 0.6), label='Luck')
#plt.xlabel('False Positive Rate')
#plt.ylabel('True Positive Rate')
#plt.xlabel('Signal efficiency')
#plt.ylabel('Background rejection')
#plt.legend(loc="lower right")
#plt.grid()
#plt.show()

#######################################
########## OVERTRAINING ###############
#######################################

scikit_Function.compare_train_test_dec(decisionTrainSigAll,
                                       decisionTrainBkgAll,
                                       decisionTestSigAll,
                                       decisionTestBkgAll)
plt.show()

###################################
########## SAVE OUTPUT ############
###################################
print '--- Saving output data'
from sklearn.externals import joblib
joblib.dump([bdtlist,
             targetAll,
             decisionAll,
             decisionTrainSigAll,
             decisionTrainBkgAll,
             decisionTestSigAll,
             decisionTestBkgAll],
            'saveOutput_' + category + '.pkl',
            compress=True)
