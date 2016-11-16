from sklearn.externals import joblib
import root_numpy
import numpy
import pandas
from scikit_BDT_vars import BDTVARS
import ROOT as rt

# Path to the eos folder
#eospath = 'root://eoslhcb.cern.ch//eos/lhcb/user/m/mramospe/KS0mumu/RootFiles/'
eospath = '~/work/'
# Type and subpath to the ROOT files
fpath = {
    'DT': eospath + 'Ks0mumu_Data2012_Splitted_MuPtCutOff2500.root',
    'MC': eospath + 'Ks0mumu_MC2012_Splitted_MuPtCutOff2500.root'
    }

''' First iterate over the data types '''
def applyBDT( tp ):
    try:
        ifname = fpath[tp]
    except:
        print 'ERROR: Unknown input data type:', tp
        return
    print '--- Working with data type:', tp
    ifile  = rt.TFile( ifname )
    ofname = '~/work/' + ifname.split('/')[-1].replace('.root', '_MVA.root')
    ofile  = rt.TFile( ofname, 'NEW' )
    print '--- Cloning input tree...'
    otree = ifile.Get('MinBias').CloneTree(-1)
    otree.SetNameTitle('DecayTree', 'DecayTree')
    print '--- Building pandas DataFrame object...'
    otree.AutoSave()
    ofile.Close()
    ifile.Close()
    data = pandas.DataFrame(root_numpy.root2array(ifname, 'MinBias', branches = BDTVARS + ['eventNumber']))
    print '--- Clone of the input tree saved'
    
    ''' Loop over the trigger categories '''
    print '--- Calculating BDT values'
    for cat in ('TosTos1Tos', 'TosTos2Tos'):
        print '--- Working with category:', cat
        saveset = joblib.load('saveOutput_' + cat + '.pkl')
        bdtlist = saveset[0]

        ''' The iteration is made on the rows of the DataFrame object '''
        bdtvarssorted = ['KS0_SmallestDeltaChi2OneTrack', 'MinMu_IPCHI2_OWNPV', 'KS0_LV0', 'KS0_ENDVERTEX_CHI2', 'KS0_ENDVERTEX_X', 'KS0_ENDVERTEX_Y', 'KS0_ENDVERTEX_Z', 'KS0_IPCHI2_OWNPV', 'KS0_PT', 'KS0_DOCA']
        # We must change the other code to organize the order of the input variables
        rawbdtvalues = [bdt.predict_proba(data[bdtvarssorted])[:,1] for bdt in bdtlist]
        bdtvalues    = [rawbdtvalues[int(evtn%10)][i]
                        for i, evtn in enumerate(data['eventNumber'])]
        # Maybe there is a more elegant way to do it, but I did not succeded doing it.
        # Always got problems with the format of the strings

        ''' Old school tree making ;) '''
        
        print '--- Re-opening output file in UPDATE mode'
        ofile   = rt.TFile(ofname, 'UPDATE')
        otree   = ofile.Get('DecayTree')
        bdtval  = numpy.array([0.])
        bdtname = 'BDT' + cat
        branch  = otree.Branch(bdtname, bdtval, bdtname + '/D')
        
        for ievt, bdt in enumerate(bdtvalues):
            bdtval[0] = bdt
            branch.Fill()
            if ievt % 100000 == 0:
                print '--- Auto-saving output tree; nevts =', ievt
                otree.AutoSave()
        otree.AutoSave()
        ofile.Close()

applyBDT('MC')

print '--- Finished!'
