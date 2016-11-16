# @author jessica prisciandaro (jessica.prisciandaro@cern.ch)                                                                                                                  
# @date 19.10.2016  


import matplotlib.pyplot as plt
import pandas
from argparse import ArgumentParser
import numpy
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.ensemble import GradientBoostingRegressor, AdaBoostClassifier, ExtraTreesClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.cross_validation import train_test_split
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


############# CATEGORY (TosTos1Tos/TosTos2Tos) #############
category = 'TosTos2Tos'
############################################################


path = 'root://eoslhcb.cern.ch//eos/lhcb/user/m/mramospe/KS0mumu/BDT/Proxies/'
#ifile = 'Ks0mumu_Data2012_MuPtCutOff2500_Proxy_' + category + '.root'
ifile = 'Ks0mumu_Data2012_MuPtCutOff2500_Proxy_' + category + '.root'

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

@numpy.vectorize
def get_weight(ptval):
    return hWeights.GetBinContent(hWeights.FindFixBin(3,ptval))
#get_weight = numpy.vectorize(get_weight)

dataSig['Weight'] = get_weight(dataSig.KS0_PT)
dataBkg ['Weight'] = 1
#dataBkg_cut = dataBkg[data.KS0_M > YYY and data. KS0_M< XXX] 
#data = numpy.concatenate((dataSig, dataBkg),0)

data = dataSig.append(dataBkg, ignore_index=True)
features = list(set(data.columns) - {'Target','runNumber','eventNumber','KS0_M','KS0_TAU','Weight'})

training_data, validation_data = train_test_split(data, random_state=11, train_size=0.7)

from sklearn.neighbors import KNeighborsClassifier
#bdt = AdaBoostClassifier(learning_rate=0.25, n_estimators=1000, random_state=13,
#                         min_samples_leaf=100, max_depth=4)

print 'make the BDT'
bdt=AdaBoostClassifier(algorithm='SAMME',
                       base_estimator=DecisionTreeClassifier(criterion='gini',
                                                             max_depth=4, max_features=None, max_leaf_nodes=None,
                                                             min_samples_leaf=0.01, #100.0
                                                             min_samples_split=2, random_state=None, splitter='best'),
                       learning_rate=0.25, n_estimators=1000, random_state=None)



bdt.fit(training_data[features],training_data.Target,(training_data.Weight).as_matrix())

print 'finish the BDT'
#probaVal = bdt.predict_proba(validation_data[features])[:, 1]
#probaTrain = bdt.predict_proba(training_data[features])[:, 1]
#set_trace()

probaVal = bdt.predict(validation_data[features])
probaTrain = bdt.predict(training_data[features])
decision = bdt.decision_function(validation_data[features])
##########################################
############PERFORMANCE###################  
######################################### 

print classification_report(validation_data.Target,probaVal,target_names=["background", "signal"])
print "Area under ROC curve: %.4f"%(roc_auc_score(validation_data.Target,
                                                  decision))

print "Area under ROC curve: %.4f"%(roc_auc_score(validation_data.Target,
                                                  bdt.predict_proba(validation_data[features])[:,1]))
#print roc_auc_score(validation_data.Target, probaVal)                                                                                                                           
#print roc_auc_score(training_data.Target, probaTrain)  


##########################################
############ROC CURVE  PLOT##############
#########################################

from sklearn.metrics import roc_curve, auc

# Compute ROC curve and area under the curve

fpr, tpr, thresholds = roc_curve(validation_data.Target, decision)
bkgrej = []
for bkg in fpr:
    bkgrej.append( 1. - bkg )
roc_auc = auc(fpr, tpr)

plt.plot(tpr, bkgrej, lw=1, label='ROC (area = %0.2f)'%(roc_auc))

plt.plot([0, 1], [1, 0], '--', color=(0.6, 0.6, 0.6), label='Luck')
plt.xlim([-0.05, 1.05])
plt.ylim([-0.05, 1.05])
plt.xlabel('Signal efficiency')
plt.ylabel('Background rejection')
plt.title('Receiver operating characteristic')
plt.legend(loc="lower right")
plt.grid()
plt.show()




#######################################
###########OVERTRAINING################
######################################


scikit_Function.compare_train_test(bdt,training_data[features], training_data.Target, validation_data[features], validation_data.Target)
