from ROOT import *

from SomeMassModels.sidebands import *  # needs SetuPErasmus
gSystem.Load("libRooFit")
gROOT.ProcessLine(".x lhcbstyle.C")
gROOT.ProcessLine(".L RooPowerLaw.cxx++")

from datetime import date
from array import array
import cPickle

from histoTex import *#GetLimit_1fb import nb_digit, nb_digit_PDG, get_significant_digit

datestamp = date.today().strftime('%Y%m%d')

def addict( dic1, dic2 ):
    if not isinstance(dic1,dict)*isinstance(dic2,dict) :
        print 'adding non-dict impossible'
    return dict(dic1.items() + dic2.items()) 



def GetSystModels(Info, relevant_keys = ['r_495', 'r_double', 'r_lin'], translation_dic = None, base_model='r_495'):
    from math import factorial
    import itertools
    if translation_dic == None:
        translation_dic ={
             'r_exp':   ['N_bkg_exp_Blinded','N_bkg_exp_Blinded_err','N_bkg_exp_Blinded_errHi','N_bkg_exp_Blinded_errLo']
            ,'r_495':   ['N_bkg_exp_Blinded','N_bkg_exp_Blinded_err','N_bkg_exp_Blinded_errHi','N_bkg_exp_Blinded_errLo']
            ,'r_double':['N_bkg_doublexp_Blinded','N_bkg_doublexp_Blinded_err','N_bkg_doublexp_Blinded_errHi','N_bkg_doublexp_Blinded_errLo']
            ,'r_lin':   ['N_bkg_lin_Blinded','N_bkg_lin_Blinded_err','N_bkg_lin_Blinded_errHi','N_bkg_lin_Blinded_errLo']
            ,'r_right': ['N_bkg_exp_Blinded','N_bkg_exp_Blinded_err','N_bkg_exp_Blinded_errHi','N_bkg_exp_Blinded_errLo']}
    if base_model not in relevant_keys:
        return 'base_model not in relevant_keys'
    for r_k in relevant_keys:
        if r_k not in Info[Info.keys()[0]].keys():
            print 'removing ',r_k,'from relevant_keys since it was not fitted'
            relevant_keys.pop(relevant_keys.index(r_k))
    print '---  Getting systematics considering models : ', relevant_keys
    l_base_model_error = []
    dic = {}
    for r_k in relevant_keys:
        dic[r_k] = []
        keys_sorted = Info.keys()
        keys_sorted.sort()
        for k in keys_sorted:
            if k in ['bin7','bin8','bin78']:
                continue
            print 'r_k, k,', r_k, k 
            dic[r_k].append( Info[k][r_k][translation_dic[r_k][0]] )
            if r_k == base_model :
                l_base_model_error.append( Info[k][r_k][translation_dic[r_k][1]] )
            
    diffs = []
    all_combinations = False
    if all_combinations:
        #nb_comb = factorial(len(relevant_keys))*0.5/factorial(len(relevant_keys)-2)
        #print 'comb', nb_comb    
        for (key1,key2) in itertools.combinations(relevant_keys, 2):
            diffs.append( map(lambda i,j: abs(i-j),dic[key1],dic[key2]) )
    else:
        for r_k in relevant_keys:
            if r_k == base_model: continue
            diffs.append( map(lambda i,j: abs(i-j),dic[r_k],dic[base_model]) )
            
    if len(diffs)>1:
        max_diffs = []
        for bin in range(len(dic[relevant_keys[0]])):
            max_bin = -1.
            for comb in range(len(diffs)-1):
                max_bin = max( diffs[comb][bin], diffs[comb+1][bin]  )
            max_diffs.append( max_bin )
    else:
        max_diffs  = diffs[0]

    print l_base_model_error
    import code; code.interact(local=locals())  
    print 'maximal difference (absolute)  =',  max_diffs
    max_rel = map(lambda i,j:i/j,max_diffs,dic[base_model])
    print 'maximal difference relative to model', base_model,'=',  max_rel
    print 'maximal difference relative to model in [%]', base_model,'=',  map(lambda x:x*100.,max_rel)
    print 'compared to ', base_model,' uncertainties in [%]=',  map(lambda x,y:x/y*100.,l_base_model_error,dic[base_model])
         
    return max_rel

#crap = GetSystModels(Info)


#import code; code.interact(local=locals())
    
#for r_k in relevant_keys:
        
    #map(lambda i,j: i-j,fd,fa)    

##     # the sys error, enters as the sys error of the ratio, 
##     # then as relative in the number (140711)
##     d = [DTis1,DTis2,DTis3,DTis4,DTis5,DTis6,DTis7,DTis8]
##     j = [JTis1,JTis2,JTis3,JTis4,JTis5,JTis6,JTis7,JTis8]
##     a = [ATis1,ATis2,ATis3,ATis4,ATis5,ATis6,ATis7,ATis8]
##     print 'Diego TIS \t ',d
##     print 'Justine TIS \t ',j
##     print 'Alessio TIS \t',a
##     fd = map(lambda i: i/DTisTot,d)
##     fj = map(lambda i: i/JTisTot,j)
##     fa = map(lambda i: i/ATisTot,a)
##     print 'Diego pdf \t',fd
##     print 'Justine pdf \t',fj
##     print 'Alessio pdf \t',fa
##     dfda = map(lambda i,j: i-j,fd,fa)
##     dfja = map(lambda i,j: i-j,fj,fa)
##     ss = map(lambda i,j:max(abs(i),abs(j)),dfda,dfja)
##     print ' sys: delta of maximum diff fraction \t ',map(val,ss)
##     ss = map(lambda i,j:i/j,ss,fa)
##     print ' sys: delta of maximum diff fraction (%) \t',map(val,ss)
##     return ss


    

def PrintNSidebands(Info, lower_sb, upper_sb, bins=['bin1', 'bin2', 'bin3', 'bin4', 'bin5', 'bin6', 'bin7', 'bin8'], file=None):
    
    print '\nLow:', lower_sb
    print 'Up:', upper_sb
    print '\n{0:9s} {1:11s} {2:11s} {3:11s}'.format( '', 'Nb in Low', 'Nb in Up', 'N in both')
    for bin in bins:
        print '{0:9s} {1:11s} {2:11s} {3:11s}'.format( bin, str(Info[bin]['tree'].GetEntries(lower_sb)), str(Info[bin]['tree'].GetEntries(upper_sb)), str(Info[bin]['tree'].GetEntries(lower_sb)+Info[bin]['tree'].GetEntries(upper_sb)))
    print '\n'
    
    if file:
        lines = ''
        lines += '\n'
        lines += '\n## Low: '+str( lower_sb )
        lines += '\n## Up : '+str( upper_sb )
        lines += '\n'
        lines += '\n## {0:9s} {1:11s} {2:11s} {3:11s}'.format( '', 'Nb in Low', 'Nb in Up', 'N in both')
        for bin in bins:
                    lines += '\n## {0:9s} {1:11s} {2:11s} {3:11s}'.format( bin, str(Info[bin]['tree'].GetEntries(lower_sb)), str(Info[bin]['tree'].GetEntries(upper_sb)), str(Info[bin]['tree'].GetEntries(lower_sb)+Info[bin]['tree'].GetEntries(upper_sb)))

        lines += '\n\n'
        file.writelines(lines)
        file.flush()
        
    #import code; code.interact(local=locals())


def get_graph( h, t , lines=None ):
    """ lines = [ bs-60, bs+60, b0-60, b0+60]
    """
    range__ = [sb_Low, sb_Hi]#[bsmass_pdg-600, bsmass_pdg+600]
    for i in range(t.GetEntries()):
        t.GetEntry(i)
        h.Fill(getattr(t, BMASS))
    #h.SetMinimum(0)
    #h.GetXaxis().SetTitle('M_{#mu#mu} (MeV/c^{2})')
    #h.GetYaxis().SetTitle('Events/('+str(h.GetBinWidth(0))+' MeV/c^{2})')
    nb = h.GetNbinsX()
    x, y, exl, eyl, exh, eyh = [], [], [], [], [], []
    fc = TFeldmanCousins(0.68)
    for i in range(nb):
        x.append( h.GetBinCenter (i+1) )
        y.append( h.GetBinContent(i+1) )
        exl.append( h.GetBinWidth(i+1)*0.5 )
        exh.append( h.GetBinWidth(i+1)*0.5 )
        if h.GetBinContent(i+1) < 20.:
            eyl.append( abs( h.GetBinContent(i+1) - fc.CalculateLowerLimit(h.GetBinContent(i+1), 0) ) )
            eyh.append( abs( h.GetBinContent(i+1) - fc.CalculateUpperLimit(h.GetBinContent(i+1), 0) ) )
        else:
            eyl.append( sqrt(h.GetBinContent(i+1) ) )
            eyh.append( sqrt(h.GetBinContent(i+1) ) )
        #print eyl[-1], y[-1], eyh[-1]
    g = TGraphAsymmErrors( nb , array( 'd',  x), array( 'd', y ), array( 'd', exl), array( 'd', exh ), array( 'd',  eyl), array( 'd', eyh ) )
    g.SetMinimum(0)
    g.GetXaxis().SetRangeUser(range__[0], range__[1] )
    g.GetXaxis().SetTitle('m_{#mu#mu} (MeV/c^{2})')
    g.GetXaxis().SetTitleSize(0.053)
    g.GetXaxis().SetLabelSize(0.053)
    g.GetXaxis().SetNdivisions(510)
    binW = int(h.GetBinWidth(0)*100)/1/100.
    binW = int(h.GetBinWidth(0))/1
    g.GetYaxis().SetTitle('Candidates per '+str(binW)+' MeV/c^{2}')
    g.GetYaxis().SetTitleSize(0.053)
    g.GetYaxis().SetLabelSize(0.053)
    g.GetXaxis().SetLabelOffset(0.01)
    g.GetYaxis().SetLabelOffset(0.01)
    
    if lines != None:
        min_ = g.GetYaxis().GetXmin()
        max_ = g.GetYaxis().GetXmax()
        l_Bs_d = TLine( lines[0], min_, lines[0], max_ )
        l_Bs_u = TLine( lines[1], min_, lines[1], max_ )
        l_Bs_d.SetLineWidth(4) ; l_Bs_d.SetLineColor(807) ; l_Bs_d.SetLineStyle(2)
        l_Bs_u.SetLineWidth(4) ; l_Bs_u.SetLineColor(807) ; l_Bs_u.SetLineStyle(2)
        return h, g, [l_Bs_d, l_Bs_u]
    else:
        return h, g

def plot_exp(canvas, h, k, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    range__ = [4800.,6000.]#[bsmass_pdg-600, bsmass_pdg+600]
    fexp   = TF1( 'fun_exp', '[0]*TMath::Exp([1]*x)' , range__[0], range__[1] )
    fexp.SetParameters(h.GetBinWidth(0) * k * Nsb / ( exp(k*SB2) - exp(k*SB1) + exp(k*SB4) - exp(k*SB3) ), k )
    fexp.SetLineColor(color);fexp.SetLineWidth(4)
    #import code; code.interact(local=locals())  
    fexp.SetRange(SB1,SB2);fexp.SetLineStyle(1);fexp.DrawCopy('SAME')
    fexp.SetRange(SB3,SB4);fexp.SetLineStyle(1);fexp.DrawCopy('SAME')
    gStyle.SetLineStyleString(33,"[30 30]")
    fexp.SetRange(range__[0], range__[1] );fexp.SetLineStyle(7);fexp.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_exp_new(canvas, h, k, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    range__ = [4800.,6000.]#[bsmass_pdg-600, bsmass_pdg+600]
    fexp   = TF1( 'fun_exp', '[0]*TMath::Exp([1]*x)', range__[0], range__[1] )
    fexp.SetParameters(h.GetBinWidth(0) * k * Nsb / ( exp(k*SB2) - exp(k*SB1) + exp(k*SB4) - exp(k*SB3) ), k )
    fexp.SetLineColor(color);fexp.SetLineWidth(4)    
    fexp.SetRange(SB1,SB2);fexp.SetLineStyle(1);fexp.DrawCopy('SAME')
    fexp.SetRange(SB3,SB4);fexp.SetLineStyle(1);fexp.DrawCopy('SAME')
    fexp.SetRange(range__[0], range__[1] );fexp.SetLineStyle(2);fexp.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_lin(canvas, h, c, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    range__ = [4800.,6000.]#[bsmass_pdg-600, bsmass_pdg+600]
    flin = TF1( 'fun_lin', '([0]+[1]*x)*[2]' , range__[0], range__[1] )
    #flin = TF1( 'fun_lin', '[0]+[1]*x' , bsmass_pdg-600, 6000 )
    flin.SetParameters( Nsb-c*0.5*(SB2*SB2+SB4*SB4-SB1*SB1-SB3*SB3)/(SB2+SB4-SB1-SB3), c , 1./h.GetBinWidth(0) )
    #flin.SetParameters( Nsb-c*0.5*(SB2*SB2+SB4*SB4-SB1*SB1-SB3*SB3)/(SB2+SB4-SB1-SB3), c )
    flin.SetLineColor(color);flin.SetLineWidth(4)
    flin.SetRange(SB1,SB2);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(SB3,SB4);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(range__[0], range__[1] );flin.SetLineStyle(2);flin.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_lin_Giacomo(canvas, h, c, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    range__ = [4800.,6000.]#[bsmass_pdg-600, bsmass_pdg+600]
    flin = TF1( 'fun_lin', '([0]+[1]*x)*[2]' , range__[0], range__[1] )
    #flin = TF1( 'fun_lin', '[0]+[1]*x' , bsmass_pdg-600, 6000 )
    flin.SetParameters( (1-c*0.5*(SB4*SB4-SB1*SB1))/(SB4-SB1), c , Nsb*h.GetBinWidth(0) )
    #flin.SetParameters( Nsb-c*0.5*(SB2*SB2+SB4*SB4-SB1*SB1-SB3*SB3)/(SB2+SB4-SB1-SB3), c )
    flin.SetLineColor(color);flin.SetLineWidth(4)
    flin.SetRange(SB1,SB2);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(SB3,SB4);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(range__[0], range__[1] );flin.SetLineStyle(2);flin.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_root(canvas, h, SB1, SB2, SB3, SB4, color):
    range__ = [4800.,6000.]#[bsmass_pdg-600, bsmass_pdg+600]
    canvas.cd()
    
    h1 = TH1F()
    h.Copy(h1)
    
    for i in range(h1.GetNbinsX()):
        if h1.GetBinCenter(i+1)>SB2 and h1.GetBinCenter(i+1)<SB3:
            h1.SetBinError(i+1, h1.GetBinError(i+1)*1000. )
    
    f_lin_root = TF1( 'fun_lin', '[0]+[1]*x' , SB1, SB4 )
    h1.Fit(f_lin_root, 'N')
    f_lin_root.SetLineColor(color);f_lin_root.SetLineWidth(4)
    f_lin_root.SetRange(SB1,b0mass-60);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(bsmass+60,range__[1]);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(range__[0], range__[1]);f_lin_root.SetLineStyle(2);f_lin_root.DrawCopy('SAME')
    
    h1.Delete()
    canvas.Update()
    return canvas

def plot_root_(canvas, h, SB1, SB2, SB3, SB4, color):
    range__ = [4800.,6000.]#[bsmass_pdg-600, bsmass_pdg+600]
    canvas.cd()
    
    h1 = TH1F()
    h.Copy(h1)
    
    for i in range(h1.GetNbinsX()):
        if h1.GetBinCenter(i+1)>SB2 and h1.GetBinCenter(i+1)<SB3:
            h1.SetBinError(i+1, h1.GetBinError(i+1)*1000. )
            
    def fline(x, par):
        if x[0] > SB2 and x[0] < SB3: 
           TF1.RejectPoint()
           return 0
        return par[0] + par[1]*x[0]
    
    
    fline = TF1( 'fun_lin', fline , SB1, SB4 )
    h1.Fit(f_lin_root, 'N')
    f_lin_root.SetLineColor(color);f_lin_root.SetLineWidth(4)
    f_lin_root.SetRange(range__[0],b0mass-60);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(bsmass+60,range__[1]);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(range__[0], range__[1]);f_lin_root.SetLineStyle(2);f_lin_root.DrawCopy('SAME')
    
    h1.Delete()
    canvas.Update()
    return canvas



def do_lhcb_label(x1,y1,x2,y2, prelim=False):
    l = TPaveText()
    l.SetTextSize(0.07)
    if prelim:
        l.AddText("#splitline{LHCb}{Preliminary}")
    else:
        l.AddText("LHCb")
    l.SetX1NDC(x1)
    l.SetY1NDC(y1)
    l.SetX2NDC(x2)
    l.SetY2NDC(y2)
    l.SetFillColor(0)
    l.SetFillStyle(0)
    l.SetBorderSize(0)
    return l

def save_this(frame, name, pave=None):
    c1 = TCanvas('c1', 'c1', -700, 500)
    c1.cd()
    frame.Draw()
    if pave :
        pave.Draw()
    c1.SaveAs(name+'.png')
    c1.SaveAs(name+'.pdf')
    c1.SaveAs(name+'.eps')
    c1.SaveAs(name+'.root')
    c1.Delete()

Nb_CPU = 2 #

fit_to_perform = { 'expo'     : True  #False #
                  ,'expoRight': False #True  #
                  ,'expo495'  : False #True  # 
                  ,'lin'      : False #True  #
                  ,'double'   : False #True  #
                   }

##C this flags drives the drawing of the plots
plot_detail = { 'expo'     : True  #False #
               ,'expoRight': True  #False #
               ,'expo495'  : False #True  # 
               ,'lin'      : False #True  #
               ,'double'   : True  #False #
                }

for k in plot_detail.keys():
    plot_detail[k] = plot_detail[k]*fit_to_perform[k]

color = { 'expo'     : 3
         ,'expoRight': 6
         ,'expo495'  : 4
         ,'lin'      : 2
         ,'double'   : 9
                   }

##C position of the labels
lblPos = [ [0.64523, 0.717742, 0.783161, 0.97379]#[0.166667, 0.181452, 0.382184, 0.26]
          ,[0.64523, 0.717742, 0.783161, 0.97379]  ]

##C loading of the ntuple

useTIS =  true # false # true #
useTOS = not useTIS
useCached =  false # true # false #

if useTIS and not useCached:
    
    fA = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ksmumu1fbA_TIS.root')
    #fA = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ks2mmm1fbA.root')
    #fA = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ksmumu1fbA.root')
    fB = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ksmumu1fbB_TIS.root')
    #fB = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ks2mmm1fbB.root')
    #fB = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ksmumu1fbB.root')
    tA = fA.Get('T')
    tB = fB.Get('T')       

elif not useCached: #TOS
    fA = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ksmumu1fbA_TOS.root')
    fB = TFile('/afs/cern.ch/user/d/diegoms/vol5/ks/ksmumu1fbB_TOS.root')
    tA = fA.Get('T')  
    tB = fB.Get('T')       

f_out = open('log_'+useTOS*'TOS'+useTIS*'TIS', 'w')

#import code; code.interact(local=locals())

if useTIS:
    discriminantA = 'BDTDA'
    discriminantB = 'BDTDB'
else: #TOS
    discriminantA = 'BDTDTOSA'
    discriminantB = 'BDTDTOSB'
    
#BPT     = 'B_s0_PT'
BLIFE    = 'Blife_ps_r'
BMASS    = 'Bmass'
BDTS     = 'B_s0_BDTS'
MU1P     = 'mu1ptot'
MU2P     = 'mu2ptot'
#MU1PT   = 'muminus_PT'
#MU2PT   = 'muplus_PT'
Ismuon1 = 'mu1ismu'
Ismuon2 = 'mu2ismu'
    
#MU1DLLK = 'muminus_PIDK'
#MU2DLLK = 'muplus_PIDK'
#MU1DLLmu= 'muminus_PIDmu'
#MU2DLLmu= 'muplus_PIDmu'

typical_bkg_number = 200

##C mean of the mass for Ks

Ksmass = 498.
Ksmass_pdg = 497.614

blind_region_low  = 492.
blind_region_high = 504.
sb_Low = 470.
sb_Hi  = 600.

mass_binning = [492., 494.4, 496.8, 499.2, 501.6, 504.]
mass_binning = [492., 504.]

if useTIS:
    epsTIS = cPickle.load(file("eps_TIS"))
    BDT_binning = map( epsTIS, map(lambda x:0.9-x*0.1, range(-1, 10)))
    print BDT_binning
    #BDT_binning = [0.20000000000000001, 0.20859741837509493, 0.21745288658172093, 0.22673475508163946, 0.23687390900649954, 0.24800563493660696, 0.26045642540620384, 0.27493038674033149, 0.292637537993921, 0.3182677685950413, 1.1899999999999999]
else:
    epsTOS = cPickle.load(file("eps_TOS"))
    BDT_binning = map( epsTOS, map(lambda x:0.9-x*0.1, range(-1, 10)))
    print BDT_binning
    #BDT_binning = [0.20000000000000001, 0.20859741837509493, 0.21745288658172093, 0.22673475508163946, 0.23687390900649954, 0.24800563493660696, 0.26045642540620384, 0.27493038674033149, 0.292637537993921, 0.3182677685950413, 1.1899999999999999]
    

nb_mass_bin = len(mass_binning)-1
nb_BDT_bin = len(BDT_binning)-1

##C definition of some of the parameters

#linear model
def create_linear_model(variable, signal_region, c_lin=RooRealVar("c", "c", 0., -10., 10.), N_bkg=RooRealVar( 'N_{bkg}_lin', 'Number of Bkg linear fit',  0.5*typical_bkg_number , 0, typical_bkg_number) ):
    """
    """
    lin = RooPolynomial("lin", "linear pdf", variable, RooArgList( c_lin ) )
    #import code; code.interact(local=locals())
    extended_lin  = RooExtendPdf('e_lin', 'extended lin pdf', lin , N_Bkg, signal_region )
    #import code; code.interact(local=locals())
    return [extended_lin, c_lin, N_Bkg]

def load_linear_model(variable, signal_region, c_lin_dic ):
    """
    c_lin_dic = {'val':Val, 'AsymErrorLo':AsymErrorLo, 'AsymErrorHi':AsymErrorHi, 'Error':Error}
    """

    c_lin=RooRealVar("c", "c", 0., -10., 10.)
    c_lin.setVal         = c_lin_dic['val']
    c_lin.setError       = c_lin_dic['Error']
    c_lin.setAsymErrorLo = c_lin_dic['AsymErrorLo']
    c_lin.setAsymErrorHi = c_lin_dic['AsymErrorHi']
    
    lin = RooPolynomial("lin", "linear pdf", variable, RooArgList( c_lin ) )    
    return lin

def Fitter( tree, var, cuts='', bkgf = exp_bkg, left = blind_region_low, right = blind_region_high,  Mmin =sb_Low, Mmax =sb_Hi, left2 =blind_region_low, right2 = blind_region_high, shorTime = False, fit_in_init = 0):
    """modification of default behaviour from Diego's class """
    return sidebandsFiter( tree, var, cuts=cuts, shorTime=shorTime, bkgf=bkgf, left=left, right=right, fit_in_init=fit_in_init,  Mmin=Mmin, Mmax=Mmax, left2=left2, right2=right2)

c_lin = RooRealVar("c", "c", 0., -10., 10.)
N_Bkg_lin  = RooRealVar( 'N_{bkg}_lin', 'Number of Bkg linear fit',  0.5*typical_bkg_number , 0, typical_bkg_number)

#c_lin_CDF = RooRealVar("c_CDF", "c_CDF", 0., -10., 10.)
#N_Bkg_lin_CDF  = RooRealVar( 'N_{bkg}_lin_CDF', 'Number of Bkg linear fit CDF',  0.5*t.GetEntries() , 0, t.GetEntries())



indx       = RooRealVar("k", "k", -1.e-04, -1., 0.001)
indx_modSB = RooRealVar("k_modSB", "k_modSB", -1.e-04, -1., 0.1)
indx_right = RooRealVar("k_right", "k_right", -1.e-04, -1., 0.1)
N_Bkg  = RooRealVar( 'N_{bkg}', 'Number of Bkg',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_modSB  = RooRealVar( 'N_{bkg}_modSB', 'Number of Bkg_modSB',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_right  = RooRealVar( 'N_{bkg}_right', 'Number of Bkg_right',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_1  = RooRealVar('N_{bkg}_1', 'Number of Bkg_1',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_2  = RooRealVar('N_{bkg}_2', 'Number of Bkg_2',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_3  = RooRealVar('N_{bkg}_3', 'Number of Bkg_3',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_4  = RooRealVar('N_{bkg}_4', 'Number of Bkg_4',  0.5*typical_bkg_number , 0, typical_bkg_number)
N_Bkg_5  = RooRealVar('N_{bkg}_5', 'Number of Bkg_5',  0.5*typical_bkg_number , 0, typical_bkg_number)

mu1ismu = RooRealVar(Ismuon1, Ismuon1, 0, 1)
mu2ismu = RooRealVar(Ismuon2, Ismuon2, 0, 1)


cbs_mean = RooRealVar('cbs_mean', 'M', 463., 455. , 470.)
cbs_sigma= RooRealVar('cbs_resol', 'sigmaM', 3., 1., 10.)
cbs_alpha= RooRealVar('cbs_alpha', 'alpha', -2., -5., -0.2)
cbs_n    = RooRealVar('cbs_n', 'n', 1., 0.5, 60.)


## double exponential
indx1 = RooRealVar("k1", "k1", -5.e-03, -1., 0.)
indx2 = RooRealVar("k2", "k2", -7.e-09, -1., 0.)
N_1  = RooRealVar( 'N_{bkg}1', 'Number of Bkg 1',   25 , 0, typical_bkg_number)
N_2  = RooRealVar( 'N_{bkg}2', 'Number of Bkg 2',   2 , 0, typical_bkg_number)
N_Bkg_doublexp  = RooRealVar('N_{bkg}', 'Number of Bkg',  0.5*typical_bkg_number , 0, typical_bkg_number)

## double exponential Diego
indx1_ = RooRealVar   ("indx1_", "indx1_", -1e-04, -1., 0.)
delta_ = RooRealVar   ("delta_", "delta_", -1e-04, -1., 0.)
indx2_ = RooFormulaVar("indx2_","indx2_", "indx1_ + delta_" ,RooArgList(indx1_, delta_) )


def double_expo():
    indx1_ = RooRealVar   ("indx1_", "indx1_", -1e-04, -1., 0.)
    delta_ = RooRealVar   ("delta_", "delta_", -1e-04, -1., 0.)
    indx2_ = RooFormulaVar("indx2_","indx2_", "indx1_ + delta_" ,RooArgList(indx1_, delta_) )

    return


mass     = RooRealVar(BMASS, 'm_{#mu#mu}', sb_Low, sb_Hi, 'MeV/c^{2}')

mass.setRange("lsb", sb_Low, blind_region_low )
mass.setRange("usb", blind_region_high, sb_Hi)
mass.setRange("Kswin", mass_binning[0], mass_binning[-1])
for mass_i in range(len(mass_binning)-1):
    mass.setRange("Ksmass_"+str(mass_i+1), mass_binning[mass_i], mass_binning[mass_i+1])

lsb_cut    = BMASS+'>'+str(sb_Low)+' && '+BMASS+'<'+str(blind_region_low)
usb_cut    = BMASS+'>'+str(blind_region_high)+' && '+BMASS+'<'+str(sb_Hi)
Kswin_cut  = BMASS+'>'+str(blind_region_low) +' && '+BMASS+'<'+str(blind_region_high)
blinded_cut= BMASS+'>'+str(blind_region_low) +' && '+BMASS+'<'+str(blind_region_high)


##C futher cuts, giampi_cut:= fiducial cuts
##C              ultra_blind was to get a blind sample from Diego's partially blind one
fiducial_cut = True; fiducial_cut_str=''
if fiducial_cut:
    from fiducial import armenteros, fiducial, fiducialtos
    #armenteros = "(((4*AP_pt^2/1115.683^2 + (AP_alpha-0.69169)^2) > 4.7*100.7^2/(1115.683^2) || (4*AP_pt^2/1115.683^2 + (AP_alpha-0.69169)^2) < 3.5*100.7^2/(1115.683^2)) && ((4*AP_pt^2/1115.683^2 + (AP_alpha+0.69169)^2) > 4.7*100.7^2/(1115.683^2) || (4*AP_pt^2/1115.683^2 + (AP_alpha+0.69169)^2) < 3.5*100.7^2/(1115.683^2)))"

    if useTIS:
        fiducial_cut_str =  fiducial #"mu1ip>0.5 && mu2ip>0.5 && Blife_ps_r <130 && mu1ptot < 1e05 && mu2ptot < 1e05 && Vchi2 < 25 &&" + armenteros
    else:
        fiducial_cut_str =  fiducialtos
        
PID_cut = True; PID_cutr_str =''
if PID_cut:
    from fiducial import dll
    PID_cut_str = ' && '+dll #' && PIDmu1>-4. && PIDmu2>-4.'

TOSTrigger = useTOS; TOSTrigger_str =''
if TOSTrigger:
    from fiducial import xtos
    TOSTrigger_str = ' && '+xtos #' && Hlt1Tos && Hlt2Tos && L0Tos'

TISTrigger = useTIS; TISTrigger_str =''
if TISTrigger:
    from fiducial import tis
    TISTrigger_str = ' && '+tis #' && Hlt1Tis && Hlt2Tis && L0Tis'


even_odd = 0 #all  #-1 #odd  #1 #even  #0 #all  #1 #even  #-1 #odd
if even_odd == 0 :
    evenodd_str = ''
elif even_odd > 0 : 
    evenodd_str = '  &&  evtNum%2 == 1'
elif even_odd < 0 :
    evenodd_str = '  &&  evtNum%2 == 0'

#fout = TFile('/localscratch/mbettler/Root_crap.root', "RECREATE")
fout = TFile('/tmp/Root_crap.root', "RECREATE")
fout.cd()

LHCb_preliminary = True
redefine = False

if not useCached:
    Info = {
  'Abin1' :{'bin':'1', 'bdt_lbl_str':'BDT 1A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantA }
 ,'Abin2' :{'bin':'2', 'bdt_lbl_str':'BDT 2A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantA }
 ,'Abin3' :{'bin':'3', 'bdt_lbl_str':'BDT 3A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantA }
 ,'Abin4' :{'bin':'4', 'bdt_lbl_str':'BDT 4A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantA }
 ,'Abin5' :{'bin':'5', 'bdt_lbl_str':'BDT 5A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantA }
 ,'Abin6' :{'bin':'6', 'bdt_lbl_str':'BDT 6A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantA }
 ,'Abin7' :{'bin':'7', 'bdt_lbl_str':'BDT 7A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantA }  
 ,'Abin8' :{'bin':'8', 'bdt_lbl_str':'BDT 8A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantA }
 ,'Abin9' :{'bin':'9', 'bdt_lbl_str':'BDT 9A '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantA }  
 ,'Abin10':{'bin':'10','bdt_lbl_str':'BDT 10A '+useTOS*'TOS'+useTIS*'TIS','bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantA }
 ,'Bbin1' :{'bin':'1', 'bdt_lbl_str':'BDT 1B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantB }
 ,'Bbin2' :{'bin':'2', 'bdt_lbl_str':'BDT 2B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantB }
 ,'Bbin3' :{'bin':'3', 'bdt_lbl_str':'BDT 3B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantB }
 ,'Bbin4' :{'bin':'4', 'bdt_lbl_str':'BDT 4B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':40,'bdt': discriminantB }
 ,'Bbin5' :{'bin':'5', 'bdt_lbl_str':'BDT 5B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantB }
 ,'Bbin6' :{'bin':'6', 'bdt_lbl_str':'BDT 6B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantB }
 ,'Bbin7' :{'bin':'7', 'bdt_lbl_str':'BDT 7B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantB }  
 ,'Bbin8' :{'bin':'8', 'bdt_lbl_str':'BDT 8B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantB }
 ,'Bbin9' :{'bin':'9', 'bdt_lbl_str':'BDT 9B '+useTOS*'TOS'+useTIS*'TIS', 'bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantB }  
 ,'Bbin10':{'bin':'10','bdt_lbl_str':'BDT 10B '+useTOS*'TOS'+useTIS*'TIS','bdt_lbl_pos':lblPos[0],'NBin_plot':30,'bdt': discriminantB }
    }



    for k in Info.keys():
        l = TPaveText()
        l.SetTextSize(0.06)
        if LHCb_preliminary:
            l.AddText('#splitline{'+Info[k]['bdt_lbl_str']+'}{#splitline{LHCb}{Preliminary}}')
        else:
            l.AddText('#splitline{'+Info[k]['bdt_lbl_str']+'}{LHCb}')
        l.SetX1NDC(Info[k]['bdt_lbl_pos'][0])
        l.SetY1NDC(Info[k]['bdt_lbl_pos'][1])
        l.SetX2NDC(Info[k]['bdt_lbl_pos'][2])
        l.SetY2NDC(Info[k]['bdt_lbl_pos'][3])
        l.SetFillColor(0)
        l.SetFillStyle(0)
        l.SetBorderSize(0)
        Info[k]['bdt_label'] = l.Clone()

    for i in  range(nb_BDT_bin):
        print 'cut : ', Info['Abin'+str(i+1)]['bdt']+'>='+str(BDT_binning[i])+' && '+Info['Abin'+str(i+1)]['bdt']+'<'+str(BDT_binning[i+1])+' && '+Ismuon1+'==1 && '+Ismuon2+'==1 && '+fiducial_cut_str+TOSTrigger_str+TISTrigger_str+PID_cut_str
        Info['Abin'+str(i+1)]['tree'] = tA.CopyTree( Info['Abin'+str(i+1)]['bdt']+'>='+str(BDT_binning[i])+' && '+Info['Abin'+str(i+1)]['bdt']+'<'+str(BDT_binning[i+1])+' && '+Ismuon1+'==1 && '+Ismuon2+'==1 && '+fiducial_cut_str+TOSTrigger_str+TISTrigger_str+PID_cut_str)
        Info['Bbin'+str(i+1)]['tree'] = tB.CopyTree( Info['Bbin'+str(i+1)]['bdt']+'>='+str(BDT_binning[i])+' && '+Info['Bbin'+str(i+1)]['bdt']+'<'+str(BDT_binning[i+1])+' && '+Ismuon1+'==1 && '+Ismuon2+'==1 && '+fiducial_cut_str+TOSTrigger_str+TISTrigger_str+PID_cut_str)

    datas= []
    for i in  range(nb_BDT_bin):
        Info['Abin'+str(i+1)]['dataset'] = RooDataSet("dataA"+str(i+1),"dataA"+str(i+1), Info['Abin'+str(i+1)]['tree'], RooArgSet(mass)) 
        Info['Bbin'+str(i+1)]['dataset'] = RooDataSet("dataB"+str(i+1),"dataB"+str(i+1), Info['Bbin'+str(i+1)]['tree'], RooArgSet(mass))

else:
    file_name = '/tmp/mbettler/Info_'+'TIS'*useTIS+'TOS'*useTOS+'_saved_20120417'
    f_in = open( file_name, 'r')
    Info = cPickle.load(f_in)

#file_name = '/tmp/mbettler/Info_'+'TIS'*useTIS+'TOS'*useTOS+'_saved_20120417'
#f_in = open( file_name, 'w')
#cPickle.dump(Info, f_in )
#f_in.close()

PrintNSidebands(Info, lsb_cut, usb_cut, bins=['Abin1','Abin2','Abin3','Abin4','Abin5','Abin6','Abin7','Abin8','Abin9','Abin10'
                                             ,'Bbin1','Bbin2','Bbin3','Bbin4','Bbin5','Bbin6','Bbin7','Bbin8','Bbin9','Bbin10'], file = f_out)

import code; code.interact(local=locals())

##C definition of the pdf and extended pdfs
##C 
##C


##model pipi
mean  =RooRealVar("mean", "mean", 460., 440, 480.)
ind   =RooRealVar("ind",  "ind" , 11.0,1.,50.)
#peakbg=RooGenericPdf ('poln',"1/(abs("+BMASS+"-mean)^ind)",RooArgList(mass, ind, mean))
peakbg=RooPowerLaw('poln','poln', mass, mean, ind)

polbkg          =RooPolynomial("polbkg", "polbkg pdf", mass, RooArgList( c_lin ) )
epdf_bkg_lin_bs =RooExtendPdf('epdf_bkg_lin', 'extended bkg pdf_lin', polbkg , N_Bkg_lin, 'Kswin' )


expbkg      =RooExponential("expbkg", " exp background pdf", mass, indx)
epdf_bkg_bs =RooExtendPdf(  'epdf_bkg', 'extended bkg pdf', expbkg , N_Bkg, 'Kswin' )


expbkg_rightSB      =RooExponential("expbkg_right", " exp background pdf_right", mass, indx_right )
epdf_bkg_bs_rightSB =RooExtendPdf('epdf_bkg_rightSB','extended bkg pdf_rightSB', expbkg_rightSB, N_Bkg_right, 'bswin' )


expbkg1 = RooExponential("expbkg1", " exp background pdf1", mass, indx1)
expbkg2 = RooExponential("expbkg2", " exp background pdf2", mass, indx2)

#RooAddPdf sum("sum","g1+g2+a",RooArgList(gauss1,gauss2,argus),RooArgList(g1frac,g2frac)) ;
exp_sum    = RooAddPdf('exp_sum', 'exp_sum', RooArgList(expbkg1,expbkg2), RooArgList(N_1,N_2))
exp_sum_bs = RooExtendPdf(  'exp_sum_bs', 'extended pdf double bs', exp_sum, N_Bkg_doublexp, 'Kswin' )

cbs      = RooCBShape('cbs', 'cbs', mass, cbs_mean, cbs_sigma, cbs_alpha, cbs_n)

#Double Diego
bkg1 = RooExponential("bkg 1 of double", "Exponential background pdf 1 of double", mass, indx1_)
bkg2 = RooExponential("bkg 2 of double", "Exponential background pdf 2 of double", mass, indx2_)
f1   = RooRealVar("f1","f1",0.5, 0., 1.)
exp_double_Diego = RooAddPdf("bkg_double_Diego", "background pdf_double_Diego", bkg1, bkg2, f1)
exp_Diego_bs     = RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego', exp_double_Diego, N_Bkg_doublexp, 'Kswin' )

f_cbs    = RooRealVar("f_cbs"   ,"f_cbs"   ,0.1, 0., .2)
f_expo   = RooRealVar("f_expo"  ,"f_expo"  ,0.1, 0., .2)
f_lin    = RooRealVar("f_lin"   ,"f_lin"   ,0.1, 0., .2)
f_right  = RooRealVar("f_right" ,"f_right" ,0.1, 0., .2)
f_double = RooRealVar("f_double","f_double",0.1, 0., .2)

sum_expo  =RooAddPdf( 'peak_expo',  'peak_expo',   expbkg,           peakbg, f_expo  )
sum_lin   =RooAddPdf( 'peak_lin',   'peak_lin',    polbkg,           peakbg, f_lin   )
sum_right =RooAddPdf( 'peak_right', 'peak_right',  expbkg_rightSB,   peakbg, f_right )
sum_double=RooAddPdf( 'peak_double','peak_double', exp_double_Diego, peakbg, f_double)
sum_cbs   =RooAddPdf( 'peak_cbs'   ,'peak_cbs',    cbs,              peakbg, f_cbs   )

e_sum_expo=RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego',sum_expo, N_Bkg, 'Kswin' )
e_sum_expo_1=RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego',sum_expo, N_Bkg_1, 'Ksmass_1' )
e_sum_expo_2=RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego',sum_expo, N_Bkg_2, 'Ksmass_2' )
e_sum_expo_3=RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego',sum_expo, N_Bkg_3, 'Ksmass_3' )
e_sum_expo_4=RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego',sum_expo, N_Bkg_4, 'Ksmass_4' )
e_sum_expo_5=RooExtendPdf(  'exp_sum_bs_Diego', 'extended pdf double bs Diego',sum_expo, N_Bkg_5, 'Ksmass_5' )


#e_sum_cbs   =RooAddPdf( 'peak_cbs'   ,'peak_cbs',    cbs,              peakbg, f_cbs   )


def reset_values_pol_exp():
    f_expo.setVal( 0.1 )
    indx  .setVal( -1.e-04 )
    mean  .setVal( 448. )
    ind   .setVal( 11.0 )
    return
def reset_N_bkg():
    N_Bkg  .setVal( 0.5*typical_bkg_number  )
    N_Bkg_1.setVal( 0.5*typical_bkg_number  )
    N_Bkg_2.setVal( 0.5*typical_bkg_number  )
    N_Bkg_3.setVal( 0.5*typical_bkg_number  )
    N_Bkg_4.setVal( 0.5*typical_bkg_number  )
    N_Bkg_5.setVal( 0.5*typical_bkg_number  )   
    return

def reset_values_cbs_exp():
    f_cbs    .setVal( 0.1 )
    indx     .setVal( -1.e-04 )
    cbs_mean .setVal( 463.)
    cbs_sigma.setVal( 3. )
    cbs_alpha.setVal( -2.)
    cbs_n    .setVal( 1. )
    return

def sum_expo_D (fiter):
    fiter.mean_bkg  =RooRealVar("mean", "mean", 448., -1., 600.)
    fiter.ind_bkg   =RooRealVar("ind",  "ind" , 11.0,1.,50.)
    fiter.indx  = RooRealVar("k", "k", -1.e-04, -1., 0.1)
    fiter.f_expo= RooRealVar("f_expo"  ,"f_expo"  ,0.5, 0., 1.)
    
    fiter.peakbg=RooGenericPdf ('poln',"1/(abs("+BMASS+"-mean)^ind)",RooArgList(fiter.mass, fiter.ind_bkg, fiter.mean_bkg))
    fiter.expbkg=RooExponential("expbkg", " exp background pdf", fiter.mass, fiter.indx)
    
    fiter.bkg  =RooAddPdf( 'peak_expo',  'peak_expo',  peakbg, expbkg,           f_expo  )
    
    return 1


##C these list will contains the relevant informations from the fits to follow
for k in Info.keys():
    Info[k]['r_exp']     = {'SB':'lsb,usb',            'SB_s':lsb_cut+' || '+usb_cut}            
    Info[k]['r_lin']     = {'SB':'lsb,usb',            'SB_s':lsb_cut+' || '+usb_cut}    
#    Info[k]['r_495']     = {'SB':'lsb49005000,usb',    'SB_s':lsb_cut_4900_5000+' || '+usb_cut}    
    Info[k]['r_right']   = {'SB':'usb',                'SB_s':usb_cut}                
#    Info[k]['r_double']  = {'SB':'lsb_BIG5000,usb_BIG','SB_s':lsb_BIG_cut_5000+' || '+usb_BIG_cut}
    Info[k]['r_exp_D']   = {}#'SB':Info[k]['r_exp']   ['SB']}
    Info[k]['r_lin_D']   = {}#'SB':Info[k]['r_lin']   ['SB']}
    Info[k]['r_right_D'] = {}#'SB':Info[k]['r_right'] ['SB']} 
#    Info[k]['r_double_D']= {}#'SB':Info[k]['r_double']['SB']}

############## first bin
##C fitting the first bin.
##C the fit is done twice for every models, the first time computing the
##C expected number of event in the Bs window, and the second the exp. number of
##C event in the Bd. The parameter of the fit (k or c) or kept constant for the
##C second fit.
##C This is done in turn for:
##C      epdf_bkg_600_bs{bd} : exponential model
##C      epdf_bkg_lin_600_bs{bd} : linear model
##C      epdf_bkg_600_bs_modSB   : exponential model with modified laeft Sidebands
##C      epdf_bkg_600_bs_rightSB : exponential model with only right Sideband

def Get_mass_bins( model, mass, nb_mass_bin, tree, dic, fit_res=None):
    
    integral = model.createIntegral( RooArgSet(mass), RooFit.Range(dic['SB']))
    integral_SB = integral.getVal()
    integral.Delete()
    nb_SB = float( tree.GetEntries( dic['SB_s'] ) )
    result = []
    error = []
    for mass_i in range(nb_mass_bin):
        integral = model.createIntegral( RooArgSet(mass), RooFit.Range('Ksmass_'+str(mass_i+1)))
        result.append( integral.getVal() )
        #import code; code.interact(local=locals())
        if fit_res != None:
            error.append ( integral.getPropagatedError(fit_res) )
            print '>>>>>>>>>>>>>>>>>>>>>>>>>', integral.getPropagatedError(fit_res)
        integral.Delete()
        
    result = map(lambda x: x*nb_SB/integral_SB, result)
    
    if fit_res != None:
        error  = map(lambda x: x*nb_SB/integral_SB, error )
        return result, error
    else:
        return result


Diego = False
#loop on the bins
keys_sorted = Info.keys()
keys_sorted.sort()
for k in keys_sorted:
    #if k in ['Abin1', 'Abin2', 'Abin3', 'Abin4', 'Abin5', 'Abin6', 'Abin7', 'Abin8', 'Abin9', 'Abin10', 'Bbin1'] : continue
    
    if fit_to_perform['expo']:
        if Diego:
            pdf_D = Fitter(Info[k]['tree'], BMASS, bkgf = sum_expo_D, Mmin =sb_Low, left = blind_region_low, fit_in_init=True)
            expectation_m_bins = Get_mass_bins( sum_expo, mass, nb_mass_bin, Info[k]['tree'], Info[k]['r_exp'])
            Info[k]['r_exp_D'] = addict( Info[k]['r_exp_D'],
               {'k'        : pdf_D.indx.getVal()
                , 'k_err'  : pdf_D.indx.getError()
                , 'k_errHi': pdf_D.indx.getAsymErrorHi()
                , 'k_errLo': pdf_D.indx.getAsymErrorLo()
                , 'in_m_bins'     : expectation_m_bins
                })
            f_out.write('##---Diego-- '+k+' '+str(expectation_m_bins)+'\n')
            f_out.flush()
        
        print '\n'*40+'bin  ', k
        print 'fitting on ',Info[k]['r_exp']['SB'], '\n'*20
        indx.setConstant(False)
        reset_values_pol_exp()
        
        res =  sum_expo.fitTo( Info[k]['dataset'], RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
        expectation_m_bins, error_m_bins = Get_mass_bins( sum_expo, mass, nb_mass_bin, Info[k]['tree'], Info[k]['r_exp'], res)
        print 'peakbg', Get_mass_bins( peakbg, mass, nb_mass_bin, Info[k]['tree'], Info[k]['r_exp'], res)
        print 'expbkg', Get_mass_bins( expbkg, mass, nb_mass_bin, Info[k]['tree'], Info[k]['r_exp'], res)
        print k+' = '+str(expectation_m_bins)+' +/- '+str(error_m_bins)+'  ## sum : '+str(sum(expectation_m_bins))+'\n'
        
        #import code; code.interact(local=locals())
        reset_N_bkg()
        res =  e_sum_expo.fitTo( Info[k]['dataset'], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
        Get_mass_bins( e_sum_expo, mass, nb_mass_bin, Info[k]['tree'], Info[k]['r_exp'])
##         res =  e_sum_expo_1.fitTo( Info[k]['dataset'], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
##         res =  e_sum_expo_2.fitTo( Info[k]['dataset'], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
##         res =  e_sum_expo_3.fitTo( Info[k]['dataset'], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
##         res =  e_sum_expo_4.fitTo( Info[k]['dataset'], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
##         res =  e_sum_expo_5.fitTo( Info[k]['dataset'], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_exp']['SB']))
##         print 'XXX', k,  N_Bkg_1.getVal(), N_Bkg_2.getVal(), N_Bkg_3.getVal(), N_Bkg_4.getVal(), N_Bkg_5.getVal(), N_Bkg.getVal(), 'sum', N_Bkg_1.getVal()+N_Bkg_2.getVal()+N_Bkg_3.getVal()+N_Bkg_4.getVal()+N_Bkg_5.getVal()

##        expectation_m_bins = [N_Bkg_1.getVal(), N_Bkg_2.getVal(), N_Bkg_3.getVal(), N_Bkg_4.getVal(), N_Bkg_5.getVal()]
        f_out.write(k+' = '+str(expectation_m_bins)+' +/- '+str(error_m_bins)+'  ## sum : '+str(sum(expectation_m_bins))+'\n')
        f_out.flush()
        

        
        Info[k]['r_exp'] = addict(Info[k]['r_exp'],
               {'Fit_Res':res
                , 'f_expo'      : f_expo.getVal()
                , 'f_expo_err'  : f_expo.getError()
                , 'f_expo_errHi': f_expo.getAsymErrorHi()
                , 'f_expo_errLo': f_expo.getAsymErrorLo()
                , 'ind'       : ind.getVal()
                , 'ind_err'   : ind.getError()
                , 'ind_errHi' : ind.getAsymErrorHi()
                , 'ind_errLo' : ind.getAsymErrorLo()
                , 'mean'      : mean.getVal()
                , 'mean_err'  : mean.getError()
                , 'mean_errHi': mean.getAsymErrorHi()
                , 'mean_errLo': mean.getAsymErrorLo()
                , 'k'      : indx.getVal()
                , 'k_err'  : indx.getError()
                , 'k_errHi': indx.getAsymErrorHi()
                , 'k_errLo': indx.getAsymErrorLo()
                , 'in_m_bins'     : expectation_m_bins
                , 'in_m_bins_err' : error_m_bins
                } )
        
        
        
    if fit_to_perform['lin']:
        #pdf_D = Fitter(Info[k]['tree'], BMASS, bkgf = lin_bkg, fit_in_init=True)
        #Info[k]['r_lin_D'] = addict( Info[k]['r_lin_D'],
        #       {'N_bkg_lin_Blinded' : pdf_D.nbkg.getVal(), 'N_bkg_lin_Blinded_err' : pdf_D.nbkg.getError(), 'N_bkg_lin_Blinded_errHi' : pdf_D.nbkg.getAsymErrorHi(), 'N_bkg_lin_Blinded_errLo' : pdf_D.nbkg.getAsymErrorLo(), 'c' : pdf_D.indx.getVal(), 'c_err' : pdf_D.indx.getError(), 'c_errHi' : pdf_D.indx.getAsymErrorHi(), 'c_errLo' : pdf_D.indx.getAsymErrorLo()})

        c_lin.setConstant(False)
        res =  sum_lin.fitTo( Info[k]['dataset'], RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_lin']['SB']))
        c_lin.setConstant()
        Info[k]['r_lin'] = addict(Info[k]['r_lin'],
               {'Fit_Res':res
                , 'f_expo'      : f_expo.getVal()
                , 'f_expo_err'  : f_expo.getError()
                , 'f_expo_errHi': f_expo.getAsymErrorHi()
                , 'f_expo_errLo': f_expo.getAsymErrorLo()
                , 'ind'       : ind.getVal()
                , 'ind_err'   : ind.getError()
                , 'ind_errHi' : ind.getAsymErrorHi()
                , 'ind_errLo' : ind.getAsymErrorLo()
                , 'mean'      : mean.getVal()
                , 'mean_err'  : mean.getError()
                , 'mean_errHi': mean.getAsymErrorHi()
                , 'mean_errLo': mean.getAsymErrorLo()
                , 'c'       : c_lin.getVal()
                , 'c_err'   : c_lin.getError()
                , 'c_errHi' : c_lin.getAsymErrorHi()
                , 'c_errLo' : c_lin.getAsymErrorLo()
                , 'in_m_bins'     : expectation_m_bins
                , 'in_m_bins_err' : error_m_bins
                } )

    if fit_to_perform['expoRight']:  
        #pdf_D = Fitter(Info[k]['tree'], BMASS, bkgf = exp_bkg, fit_in_init=False)
        #pdf_D.fitOneSB(sb = "right_SB")
        #Info[k]['r_right_D'] = addict( Info[k]['r_right_D'],
        #       {'N_bkg_exp_Blinded':pdf_D.nbkg.getVal(), 'N_bkg_exp_Blinded_err': pdf_D.nbkg.getError(),'N_bkg_exp_Blinded_errHi':pdf_D.nbkg.getAsymErrorHi(),'N_bkg_exp_Blinded_errLo':pdf_D.nbkg.getAsymErrorLo(), 'k': pdf_D.indx.getVal(), 'k_err':pdf_D.indx.getError(), 'k_errHi':pdf_D.indx.getAsymErrorHi(), 'k_errLo':pdf_D.indx.getAsymErrorLo()})

        indx_right.setConstant(False)
        res =  sum_right.fitTo( Info[k]['dataset'], RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False)  , RF.Range(Info[k]['r_right']['SB']))
        indx_right.setConstant()
        Info[k]['r_right'] = addict(Info[k]['r_right'],
                                    
               {'Fit_Res':res
                , 'f_expo'      : f_expo.getVal()
                , 'f_expo_err'  : f_expo.getError()
                , 'f_expo_errHi': f_expo.getAsymErrorHi()
                , 'f_expo_errLo': f_expo.getAsymErrorLo()
                , 'ind'       : ind.getVal()
                , 'ind_err'   : ind.getError()
                , 'ind_errHi' : ind.getAsymErrorHi()
                , 'ind_errLo' : ind.getAsymErrorLo()
                , 'mean'      : mean.getVal()
                , 'mean_err'  : mean.getError()
                , 'mean_errHi': mean.getAsymErrorHi()
                , 'mean_errLo': mean.getAsymErrorLo()
                , 'k'      : indx_right.getVal()
                , 'k_err'  : indx_right.getError()
                , 'k_errHi': indx_right.getAsymErrorHi()
                , 'k_errLo': indx_right.getAsymErrorLo()
                , 'in_m_bins'     : expectation_m_bins
                , 'in_m_bins_err' : error_m_bins
                })

    if fit_to_perform['double']: 
        #pdf_D = Fitter(Info[k]['tree'], BMASS, bkgf = double_exp_bkg, Mmin=sb_Low, Mmax=sb_Hi, fit_in_init=True)
        #Info[k]['r_double_D'] = addict( Info[k]['r_double_D'],
        #       {'indx1_':pdf_D.indx1.getVal(), 'indx1__err':pdf_D.indx1.getError(), 'indx1__errLo':pdf_D.indx1.getAsymErrorLo(), 'indx1__errHi':pdf_D.indx1.getAsymErrorHi(), 'delta_':delta_.getVal(), 'delta__err':delta_.getError(), 'delta__errLo':delta_.getAsymErrorLo(), 'delta__errHi':delta_.getAsymErrorHi(), 'N_bkg_doublexp_Blinded': pdf_D.nbkg.getVal(), 'N_bkg_doublexp_Blinded_err': pdf_D.nbkg.getError(), 'N_bkg_doublexp_Blinded_errLo': pdf_D.nbkg.getAsymErrorLo(), 'N_bkg_doublexp_Blinded_errHi': pdf_D.nbkg.getAsymErrorHi()})
        
        indx1_.setConstant(False); delta_.setConstant(False)
        res =  sum_double.fitTo( Info[k]['dataset'], RF.Minos(True), RF.Strategy(1), RF.NumCPU(Nb_CPU), RF.Save(True),  RF.Verbose(False), RF.Range(Info[k]['r_double']['SB']))
        Info[k]['r_double'] = addict(Info[k]['r_double'],
               {'Fit_Res':res, 'indx1_':indx1_.getVal(), 'indx1__err':indx1_.getError(), 'indx1__errLo':indx1_.getAsymErrorLo(), 'indx1__errHi':indx1_.getAsymErrorHi(), 'delta_':delta_.getVal(), 'delta__err':delta_.getError(), 'delta__errLo':delta_.getAsymErrorLo(), 'delta__errHi':delta_.getAsymErrorHi(), 'N_bkg_doublexp_Bs': N_Bkg_doublexp.getVal(), 'N_bkg_doublexp_err_Bs': N_Bkg_doublexp.getError(), 'N_bkg_doublexp_Bs_errLo': N_Bkg_doublexp.getAsymErrorLo(), 'N_bkg_doublexp_Bs_errHi': N_Bkg_doublexp.getAsymErrorHi()} )
        indx1_.setConstant(); delta_.setConstant()
    
    
##     t_= Info[k]['tree']
##     bins = 30
##     h = TH1F("Bin"+Info[k]['bin'],"Bin"+Info[k]['bin'],Info[k]['NBin_plot'], 4800., 6000.)#bsmass_pdg-600, bsmass_pdg+600)#, 6000)
##     h, g, ls = get_graph( h, t_, lines= [Ksmass-6, Ksmass+6] )

##     can = TCanvas('d_'+Info[k]['bin'], 'd_'+Info[k]['bin'], 800,600)
##     can.SetTickx()
##     can.SetTicky()
##     g.GetYaxis().SetTitleOffset(1.2)
##     g.GetXaxis().SetTitleOffset(1.2)
##     g.Draw('AP')
##     ls[0].Draw()
##     ls[1].Draw()

##     if plot_detail['expo495']:
##         can = plot_exp(can, h, Info[k]['r_495']['k'], t_.GetEntries(Info[k]['r_495']['SB_s']), sb_Low, blind_region_low, blind_region_high, sb_Hi, color['expo495'])
##         #import code; code.interact(local=locals())
##     if plot_detail['expo']:
##         can = plot_exp(can, h, Info[k]['r_exp']['k'], t_.GetEntries(Info[k]['r_exp']['SB_s']), sb_Low, blind_region_low, blind_region_high, sb_Hi, color['expo'])
##     if plot_detail['expoRight']:
##         can = plot_exp(can, h, Info[k]['r_right']['k'], t_.GetEntries(Info[k]['r_right']['SB_s']), 0, 0, blind_region_high, sb_Hi, color['expoRight'])
##     if plot_detail['lin']:
##         can = plot_root(can, h, sb_Low, blind_region_low, blind_region_high, sb_Hi, color['lin'])


##     Info[k]['bdt_label'].Draw()

##     can.SaveAs(Info[k]['bdt']+'_Root_'+Info[k]['bin']+'_600_'+datestamp+'.png')
##     can.SaveAs(Info[k]['bdt']+'_Root_'+Info[k]['bin']+'_600_'+datestamp+'.pdf')
##     can.SaveAs(Info[k]['bdt']+'_Root_'+Info[k]['bin']+'_600_'+datestamp+'.eps')
##     can.SaveAs(Info[k]['bdt']+'_Root_'+Info[k]['bin']+'_600_'+datestamp+'.root')

##     h.Delete()


    ###
    c = TCanvas('c_'+Info[k]['bin'], 'c_'+Info[k]['bin'], -700, 500)
    c.cd()

    frame = mass.frame(RF.Range(sb_Low, sb_Low))
    Info[k]['dataset'].plotOn(frame, RF.Name('data_object'), RF.Binning(100))#, RF.CutRange('lsb,usb'), RF.Binning(20))

    if plot_detail['expo']:
        sum_expo.plotOn(frame,RF.LineColor(1))#, RF.Range(Info[k]['r_exp']['SB']),RF.NormRange(Info[k]['r_exp']['SB']))
        #peakbg.plotOn(  frame,RF.LineColor(7)            )#, RF.Range(Info[k]['r_exp']['SB']),RF.NormRange(Info[k]['r_exp']['SB']))
        #expbkg.plotOn(  frame,RF.LineColor(6)            )#, RF.Range(Info[k]['r_exp']['SB']),RF.NormRange(Info[k]['r_exp']['SB']))

    if plot_detail['lin']:
        epdf_bkg_lin_bs.plotOn(frame, RF.Range(Info[k]['r_lin']['SB']),RF.NormRange(Info[k]['r_lin']['SB']),RF.LineColor(color['lin']))
        epdf_bkg_lin_bs.plotOn(frame, RF.Range(sb_Low, sb_Low), RF.NormRange(Info[k]['r_lin']['SB']),RF.LineStyle(kDashed),RF.LineColor(color['lin']))


    if plot_detail['expoRight']:
        epdf_bkg_bs_rightSB.plotOn(frame, RF.Range(Info[k]['r_right']['SB']),RF.NormRange(Info[k]['r_right']['SB']),RF.LineColor(color['expoRight']))
        epdf_bkg_bs_rightSB.plotOn(frame, RF.Range(sb_Low, sb_Low), RF.NormRange(Info[k]['r_right']['SB']),RF.LineStyle(kDashed),RF.LineColor(color['expoRight']))


    if plot_detail['double']:
        exp_Diego_bs.plotOn(frame, RF.Range('lsb,usb'), RF.NormRange(Info[k]['r_double']['SB']), RF.LineColor(color['double']))
        #exp_Diego_bs.plotOn(frame, RF.Range('lsb_BIG,usb_BIG'), RF.NormRange('lsb_BIG,usb_BIG'), RF.LineColor(9),RF.LineStyle(kDashed))


    frame.Draw()

    lines = None #[Ksmass-6, Ksmass+6]
    if lines != None:
        d = frame.findObject('data_object')
        min_ = d.GetYaxis().GetXmin()
        max_ = d.GetYaxis().GetXmax()
        print min_, max_
        max_ *= .95
        l_Bs_d = TLine( lines[0], 0, lines[0], max_ )
        l_Bs_u = TLine( lines[1], 0, lines[1], max_ )
        l_Bs_d.SetLineWidth(4) ; l_Bs_d.SetLineColor(807) ; l_Bs_d.SetLineStyle(2)
        l_Bs_u.SetLineWidth(4) ; l_Bs_u.SetLineColor(807) ; l_Bs_u.SetLineStyle(2)
        l_Bs_d.Draw('SAME')
        l_Bs_u.Draw()


    Info[k]['bdt_label'].Draw()

    c.SaveAs(Info[k]['bdt']+'_'+Info[k]['bin']+'_600_'+datestamp+'.png' )
    c.SaveAs(Info[k]['bdt']+'_'+Info[k]['bin']+'_600_'+datestamp+'.pdf' )
    c.SaveAs(Info[k]['bdt']+'_'+Info[k]['bin']+'_600_'+datestamp+'.eps' )
    c.SaveAs(Info[k]['bdt']+'_'+Info[k]['bin']+'_600_'+datestamp+'.root')


f_out.close()
#print results






print 'going to tabaling.....'

import code; code.interact(local=locals())


def GSD(value, err_pos, err_neg, err_sym, method='2digit'):
    
    #test that the asym error are not nan nor null
    print value, err_pos, err_neg, err_sym
    if err_pos not in ['nan', 'NaN', 'Nan', 0.0] and  err_neg not in ['nan', 'NaN', 'Nan', 0.0]:
        return get_significant_digit(value, err_pos, err_neg, method)
    elif err_sym not in ['nan', 'NaN', 'Nan']:
        return get_significant_digit(value, err_sym, err_sym, method)
    else:
        print 'Trouble with the uncertainties of ', val, '+/-', err_sym, '+', err_pos,'-',err_neg
        return None


withObserved=False#True#
D_495       = False#True#False#
D_double    = False#True#False#
BsB0_yields = False#True

print '\n\n\n\n'
table = '\n\n'
table += '%% Produced by Marco\'s '+__file__+' script on '+datestamp+'.\n'
table += '%\\begin{sidewaystable}[t]\n'
table += '\\begin{table}[t]\n'
table += '\\tabcaption{XX}\n'
table += '\\label{tab:XX}\n'
table += '\\centering\n'
table += '\\resizebox{18cm}{!}{\n'
table += '\\begin{tabular}{|c|'
if fit_to_perform['expo495'  ]:
    table += 'cccc|'
if fit_to_perform['expo495'  ]*D_495:
    table += 'cc|'
if fit_to_perform['double'   ]:
    if BsB0_yields:
        table += 'ccc|'
    else:
        table += 'c|'
if fit_to_perform['double'   ]*D_double:
    table += 'c|'
if fit_to_perform['expo'     ]:
    if BsB0_yields:
        table += 'cccc|'
    else:
        table += 'cc|'
if fit_to_perform['lin'      ]:
    if BsB0_yields:
        table += 'cccc|'
    else:
        table += 'cc|'
if fit_to_perform['expoRight']:
    if BsB0_yields:
        table += 'cccc|'
    else:
        table += 'cc|'
if withObserved:
    table += 'c|}\n'
else:
    table += '}\n'
table += '\\hline\n'

table += ' '
if fit_to_perform['expo495'  ]:
    table += '& \\multicolumn{4}{c|}{expo, 4.9-5, right} '
if fit_to_perform['expo495'  ]*D_495:
    table += '& \\multicolumn{2}{c|}{expo, 4.9-5, right, D} '
if fit_to_perform['double'   ]:
    table += '& \\multicolumn{'+str(1+BsB0_yields*2)+'}{c|}{double expo, 1200} '
if fit_to_perform['double'   ]*D_double:
    table += '& double expo, 1200, D '
if fit_to_perform['expo'     ]:
    table += '&  \\multicolumn{'+str(2+BsB0_yields*2)+'}{c|}{exponential}  '
if fit_to_perform['lin'      ]:
    table += '& \\multicolumn{'+str(2+BsB0_yields*2)+'}{c|}{linear} '
if fit_to_perform['expoRight']:
    table += '& \\multicolumn{'+str(2+BsB0_yields*2)+'}{c|}{expo, right} '
if withObserved:
    table += '& \\\\\n'
else:
    table += '\\\\\n'
    
table += 'Bin '
if fit_to_perform['expo495'  ]:
    table += '& $k \ [10^{-4}]$ & $B_s$& $B_0$ & blind '
if fit_to_perform['expo495'  ]*D_495:
    table += '& $k \ [10^{-4}]$ & blind '
if fit_to_perform['double'   ]:
    if BsB0_yields:
        table += '& $B_s$& $B_0$& blind '
    else:
        table += '& blind '
if fit_to_perform['double'   ]*D_double:
    table += '& blind '
if fit_to_perform['expo'     ]:
    table += '& $f$ & $k \ [10^{-4}]$ & mean & ind & expectation '
if fit_to_perform['lin'      ]:
    if BsB0_yields:
        table += '& $c \ [10^{-4}]$ & $B_s$& $B_0$ & blind '
    else:
        table += '& $c \ [10^{-4}]$ & blind '
if fit_to_perform['expoRight']:
    if BsB0_yields:
        table += '& $k \ [10^{-4}]$ & $B_s$& $B_0$ & blind '
    else:
        table += '& $k \ [10^{-4}]$ & blind '
if withObserved:
    table += '& Observed \\\\\n'
else:
    table += '\\\\\n'
table += '\hline\n'

#for i in range(len(datas)):
keys_sorted = Info.keys()
keys_sorted.sort()
for k in keys_sorted:

    
    table+='%(bin)s '%{'bin':Info[k]['bin'].replace('_','\_')}
    
    if fit_to_perform['expo495']:
        tuple1 = GSD( Info[k]['r_495']['k']*1e4, Info[k]['r_495']['k_errHi']*1e4, Info[k]['r_495']['k_errLo']*1e4, Info[k]['r_495']['k_err']*1e4)
        tuple2 = GSD( Info[k]['r_495']['N_bkg_exp_Bs'],Info[k]['r_495']['N_bkg_exp_Bs_errHi'],Info[k]['r_495']['N_bkg_exp_Bs_errLo'] )
        tuple3 = GSD( Info[k]['r_495']['N_bkg_exp_B0'],Info[k]['r_495']['N_bkg_exp_B0_errHi'],Info[k]['r_495']['N_bkg_exp_B0_errLo'] )
        tuple4 = GSD( Info[k]['r_495']['N_bkg_exp_Blinded'],Info[k]['r_495']['N_bkg_exp_Blinded_errHi'],Info[k]['r_495']['N_bkg_exp_Blinded_errLo'] )            
        table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ '\
            %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
               ,tuple2[3], tuple2[0], tuple2[3], tuple2[1], tuple2[3], tuple2[2]
               ,tuple3[3], tuple3[0], tuple3[3], tuple3[1], tuple3[3], tuple3[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])

    
    if fit_to_perform['expo495']*D_495 :
        if k in ['bin7_78', 'bin8_78']:
            table+=' & --- & --- '
        else:
            tuple1 = GSD( Info[k]['r_495_D']['k']*1e4, Info[k]['r_495_D']['k_errHi']*1e4, Info[k]['r_495_D']['k_errLo']*1e4 )
            tuple4 = GSD( Info[k]['r_495_D']['N_bkg_exp_Blinded'],Info[k]['r_495_D']['N_bkg_exp_Blinded_errHi'],Info[k]['r_495_D']['N_bkg_exp_Blinded_errLo'] )            
            table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ '\
                    %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
                       ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])

    if fit_to_perform['double']:
        tuple2 = GSD( Info[k]['r_double']['N_bkg_doublexp_Bs'],Info[k]['r_double']['N_bkg_doublexp_Bs_errHi'],Info[k]['r_double']['N_bkg_doublexp_Bs_errLo'] )
        tuple3 = GSD( Info[k]['r_double']['N_bkg_doublexp_B0'],Info[k]['r_double']['N_bkg_doublexp_B0_errHi'],Info[k]['r_double']['N_bkg_doublexp_B0_errLo'] ) 
        tuple4 = GSD( Info[k]['r_double']['N_bkg_doublexp_Blinded'],Info[k]['r_double']['N_bkg_doublexp_Blinded_errHi'],Info[k]['r_double']['N_bkg_doublexp_Blinded_errLo'] )
        
        if BsB0_yields:
            table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$& $%.*f^{+%.*f}_{%.*f}$ '\
            %(  tuple2[3], tuple2[0], tuple2[3], tuple2[1], tuple2[3], tuple2[2]
               ,tuple3[3], tuple3[0], tuple3[3], tuple3[1], tuple3[3], tuple3[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
        else:
            table+=' & $%.*f^{+%.*f}_{%.*f}$ '\
            %(  tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
            

    if fit_to_perform['double']*D_double:
        if k in ['bin7_78', 'bin8_78']:
            table+=' & --- '
        else:
            tuple4 = GSD( Info[k]['r_double_D']['N_bkg_doublexp_Blinded'],Info[k]['r_double_D']['N_bkg_doublexp_Blinded_errHi'],Info[k]['r_double_D']['N_bkg_doublexp_Blinded_errLo'] )            
            table+=' & $%.*f^{+%.*f}_{%.*f}$ '\
                    %(  tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
                
    if fit_to_perform['expo']:
        tuple1 = GSD( Info[k]['r_exp']['f_expo']      ,Info[k]['r_exp']['f_expo_errHi']    ,Info[k]['r_exp']['f_expo_errLo']    ,Info[k]['r_exp']['f_expo_err']     )
        tuple2 = GSD( Info[k]['r_exp']['k']*1e4       ,Info[k]['r_exp']['k_errHi']*1e4     ,Info[k]['r_exp']['k_errLo']*1e4     ,Info[k]['r_exp']['k_err']*1e4      )
        tuple3 = GSD( Info[k]['r_exp']['mean']        ,Info[k]['r_exp']['mean_errHi']      ,Info[k]['r_exp']['mean_errLo']      ,Info[k]['r_exp']['mean_err']       )
        tuple4 = GSD( Info[k]['r_exp']['ind']         ,Info[k]['r_exp']['ind_errHi']       ,Info[k]['r_exp']['ind_errLo']       ,Info[k]['r_exp']['ind_err']        )
        tuple5 = GSD( Info[k]['r_exp']['in_m_bins'][0],Info[k]['r_exp']['in_m_bins_err'][0],Info[k]['r_exp']['in_m_bins_err'][0],Info[k]['r_exp']['in_m_bins_err'][0])
        table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ '\
            %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
               ,tuple2[3], tuple2[0], tuple2[3], tuple2[1], tuple2[3], tuple2[2]
               ,tuple3[3], tuple3[0], tuple3[3], tuple3[1], tuple3[3], tuple3[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2]
               ,tuple5[3], tuple5[0], tuple5[3], tuple5[1], tuple5[3], tuple5[2])
    
    if fit_to_perform['lin']:
        tuple1 = GSD( Info[k]['r_lin']['c']*1e4, Info[k]['r_lin']['c_errHi']*1e4, Info[k]['r_lin']['c_errLo']*1e4 )
        tuple2 = GSD( Info[k]['r_lin']['N_bkg_lin_Bs'],Info[k]['r_lin']['N_bkg_lin_Bs_errHi'],Info[k]['r_lin']['N_bkg_lin_Bs_errLo'] )
        tuple3 = GSD( Info[k]['r_lin']['N_bkg_lin_B0'],Info[k]['r_lin']['N_bkg_lin_B0_errHi'],Info[k]['r_lin']['N_bkg_lin_B0_errLo'] )
        tuple4 = GSD( Info[k]['r_lin']['N_bkg_lin_Blinded'],Info[k]['r_lin']['N_bkg_lin_Blinded_errHi'],Info[k]['r_lin']['N_bkg_lin_Blinded_errLo'] )
        
        if BsB0_yields:
            table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ ' \
            %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
               ,tuple2[3], tuple2[0], tuple2[3], tuple2[1], tuple2[3], tuple2[2]
               ,tuple3[3], tuple3[0], tuple3[3], tuple3[1], tuple3[3], tuple3[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
        else:
            table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ ' \
            %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
            
        
    if fit_to_perform['expoRight']:
        tuple1 = GSD( Info[k]['r_right']['k']*1e4, Info[k]['r_right']['k_errHi']*1e4, Info[k]['r_right']['k_errLo']*1e4 )
        tuple2 = GSD( Info[k]['r_right']['N_bkg_exp_Bs'],Info[k]['r_right']['N_bkg_exp_Bs_errHi'],Info[k]['r_right']['N_bkg_exp_Bs_errLo'] )
        tuple3 = GSD( Info[k]['r_right']['N_bkg_exp_B0'],Info[k]['r_right']['N_bkg_exp_B0_errHi'],Info[k]['r_right']['N_bkg_exp_B0_errLo'] )
        tuple4 = GSD( Info[k]['r_right']['N_bkg_exp_Blinded'],Info[k]['r_right']['N_bkg_exp_Blinded_errHi'],Info[k]['r_right']['N_bkg_exp_Blinded_errLo'] )   
        
        if BsB0_yields:
            table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ '\
            %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
               ,tuple2[3], tuple2[0], tuple2[3], tuple2[1], tuple2[3], tuple2[2]
               ,tuple3[3], tuple3[0], tuple3[3], tuple3[1], tuple3[3], tuple3[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
        else:         
            table+=' & $%.*f^{+%.*f}_{%.*f}$ & $%.*f^{+%.*f}_{%.*f}$ '\
            %(  tuple1[3], tuple1[0], tuple1[3], tuple1[1], tuple1[3], tuple1[2]
               ,tuple4[3], tuple4[0], tuple4[3], tuple4[1], tuple4[3], tuple4[2])
            
        
    if withObserved:
        table+= ' & $'+str(Info[k]['tree'].GetEntries(blinded_cut))+'$ \\Tstrut\\\\\n'
    else:
        table+= '  \\Tstrut\\\\\n'

table += '\\hline\n'
table += '\\end{tabular}\n'
table += '}\n'
table += '\\end{table}\n'
table += '%\\end{sidewaystable}\n'

print table
name_  =  'table_Bkg_'+discriminantA[:-1]+'_'+datestamp+'.tex'
file = open(name_, 'wb')
file.write(table)
file.close()


#def LaTex1(Info, fit_to_perform):

list_to_perform = []
for key,val in fit_to_perform.items():
    if val : list_to_perform.append(key)
listA = []
for key in Info.keys():
    if 'A' in key : listA.append(key)
listB = []
for key in Info.keys():
    if 'B' in key : listB.append(key)
#GSD = get_significant_digit


print '\n\n\n\n'
table = '\n\n'
table += '%% Produced by Marco\'s '+__file__+' script on '+datestamp+'.\n'
table += '%\\begin{sidewaystable}[t]\n'
table += '\\begin{table}[t]\n'
table += '\\tabcaption{XX}\n'
table += '\\label{tab:XX}\n'
table += '\\centering\n'
table += '\\resizebox{18cm}{!}{\n'
table += '\\begin{tabular}{|lr|c|c|c|c|c|c|c|c|}\n'
table += '\\hline\n'
for bin_list in [listA, listB]:
    table += '& & bin1 & bin2 & bin3 & bin4 & bin5 & bin6 & bin7 & bin8 & bin9 & bin10 \\\\\n'
    table += '\\hline\n'

    if fit_to_perform['expo495'  ]:
        table+='exponential & '

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_495']['k']*1e4, Info[bin]['r_495']['k_errHi']*1e4, Info[bin]['r_495']['k_errLo']*1e4, Info[bin]['r_495']['k_err']*1e4 ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+='index '+'& $(%.*f^{+%.*f}_{%.*f})\\times 10^{-4}$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                %string_format

        table+='\cline{2-10}\n'

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_495']['in_m_bins'][0], Info[bin]['r_495']['in_m_bins_err'][0], Info[bin]['r_495']['in_m_bins_err'][0], Info[bin]['r_495']['in_m_bins_err'][0] ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+=' $[4.9, 5]$ and right& '
        table+='yield '+'& $(%.*f^{+%.*f}_{%.*f})$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                 %string_format
        table += '\\hline\n'


    if fit_to_perform['expo'     ]:
        table+='exponential &'

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_exp']['k']*1e4, Info[bin]['r_exp']['k_errHi']*1e4, Info[bin]['r_exp']['k_errLo']*1e4, Info[bin]['r_exp']['k_err']*1e4 ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+='index '+'& $(%.*f^{+%.*f}_{%.*f})\\times 10^{-4}$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                %string_format


        table+='\cline{2-10}\n'
        table+='both sidebands & '

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_exp']['in_m_bins'][0], Info[bin]['r_exp']['in_m_bins_err'][0], Info[bin]['r_exp']['in_m_bins_err'][0], Info[bin]['r_exp']['in_m_bins_err'][0] ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+='yield '+'& $(%.*f^{+%.*f}_{%.*f})$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                 %string_format
        table += '\\hline\n'


    if fit_to_perform['expoRight']:
        table+='exponential & '

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_right']['k']*1e4, Info[bin]['r_right']['k_errHi']*1e4, Info[bin]['r_right']['k_errLo']*1e4, Info[bin]['r_right']['k_err']*1e4 ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+='index '+'& $(%.*f^{+%.*f}_{%.*f})\\times 10^{-4}$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                 %string_format

        table+='\cline{2-10}\n'
        table+=' only right& '

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_right']['in_m_bins'][0], Info[bin]['r_right']['in_m_bins_err'][0], Info[bin]['r_right']['in_m_bins_err'][0], Info[bin]['r_right']['in_m_bins_err'][0] ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+='yield '+'& $(%.*f^{+%.*f}_{%.*f})$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                 %string_format
        table += '\\hline\n'

    if fit_to_perform['lin'      ]:
        table+='linear & '

        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_lin']['k']*1e4, Info[bin]['r_lin']['k_errHi']*1e4, Info[bin]['r_lin']['k_errLo']*1e4, Info[bin]['r_lin']['k_err']*1e4 ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)
                              
        table+='index '+'& $(%.*f^{+%.*f}_{%.*f})\\times 10^{-4}$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                 %string_format

        table+='\cline{2-10}\n'
        table+=' both sidebands& '


        string_format = []
        for bin in bin_list:
            gsd = GSD( Info[bin]['r_lin']['in_m_bins'][0], Info[bin]['r_lin']['in_m_bins_err'][0], Info[bin]['r_lin']['in_m_bins_err'][0], Info[bin]['r_lin']['in_m_bins_err'][0] ) 
            string_format.append( gsd[3]); string_format.append( gsd[0])
            string_format.append( gsd[3]); string_format.append( gsd[1])
            string_format.append( gsd[3]); string_format.append( gsd[2])
        string_format = tuple(string_format)

        table+='yield '+'& $(%.*f^{+%.*f}_{%.*f})$ '*len(bin_list)+'\\Bstrut\\Tstrut\\\\\n'\
                 %string_format
        table += '\\hline\n'


table += '\\end{tabular}\n'
table += '}\n'
table += '\\end{table}\n'
table += '%\\end{sidewaystable}\n'

print table
name_  =  'table_Bkg_other'+discriminantA[:-1]+'_'+datestamp+'.tex'
file = open(name_, 'wb')
file.write(table)
file.close()




import code; code.interact(local=locals())

if False:



    ## delta_mass = [400, 200]
    ## color = 4
    ## c, N = [],[]
    ## #for delta in delta_mass:
    ## delta = 200

    ## color += 1
    ## N_Bkg_lin.setVal(5.)
    ## mass.setRange("lsb_lin_"+str(delta), blind_region_low-delta, blind_region_low )
    ## mass.setRange("usb_lin_"+str(delta), blind_region_high, blind_region_high+delta )

    ## res =  polbkg.fitTo(  datas[3],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)))

    ## integral = polbkg.createIntegral( RooArgSet(mass), RF.Range('blinded'))
    ## print 'Integral ', integral.getVal()/ float(blind_region_high -  blind_region_low)
    ## integral.Delete()

    ## epdf_tmp = epdf_bkg_lin_600.clone('new_mass_'+str(delta))
    ## res =  epdf_tmp.fitTo(  datas[3],   RF.Extended(True), RF.Minos(False), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)))
    ## print 'XX for delta mass', delta
    ## print 'N_bkg ', N_Bkg_lin.getVal() , '+', N_Bkg_lin.getAsymErrorHi(), '-', N_Bkg_lin.getAsymErrorLo()
    ## print 'c  ', c_lin.getVal(), '+-', c_lin.getError()
    ## c.append(c_lin.getVal())
    ## N.append(N_Bkg_lin.getVal())
    ## epdf_tmp.plotOn(frame4_600, RF.Range('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)),RF.NormRange('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)),RF.LineColor(color))
    ## epdf_tmp.plotOn(frame4_600, RF.Range(blind_region_low-delta, blind_region_high+delta), RF.NormRange('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)),RF.LineStyle(kDashed),RF.LineColor(color))

    ## frame4_600.Draw()
    ## epdf_tmp.Delete()

    ## print 'c', c
    ## print 'N', N

    save_this(frame4_600, discriminant+'_4_600_multifit')

    ## double exponential

    indx1 = RooRealVar("k1", "k1", -5.e-03, -1., 0.)
    indx2 = RooRealVar("k2", "k2", -7.e-09, -1., 0.)
    N_1  = RooRealVar( 'N_{bkg}1', 'Number of Bkg 1',   25 , 0, t.GetEntries())
    N_2  = RooRealVar( 'N_{bkg}2', 'Number of Bkg 2',   2 , 0, t.GetEntries())
    N_Bkg  = RooRealVar('N_{bkg}', 'Number of Bkg',  0.5*typical_bkg_number , 0, typical_bkg_number)

    expbkg1 = RooExponential("expbkg1", " exp background pdf1", mass, indx1)
    expbkg2 = RooExponential("expbkg2", " exp background pdf2", mass, indx2)


    #RooAddPdf sum("sum","g1+g2+a",RooArgList(gauss1,gauss2,argus),RooArgList(g1frac,g2frac)) ;
    exp_sum = RooAddPdf('exp_sum', 'exp_sum', RooArgList(expbkg1,expbkg2), RooArgList(N_1,N_2))
    epdf_bkg_2exp = RooExtendPdf( 'epdf_bkg_2exp', 'epdf_bkg_2exp', exp_sum, N_Bkg, 'bswin' )


    indx1.setVal(-5.e-03)
    indx2.setVal(-7.e-09)
    res =  exp_sum.fitTo( datas[0], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True), RF.Verbose(False), RF.Range('lsb_BIG,usb_BIG'))
    res_2exp =  epdf_bkg_2exp.fitTo( datas[0], RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True), RF.Verbose(False), RF.Range('lsb_BIG,usb_BIG'))
    print 'N_bkg ', N_Bkg.getVal()

    frame1 = mass.frame()
    datas[0].plotOn(frame1, RF.CutRange('lsb_BIG,usb_BIG'), RF.Binning(40))
    exp_sum.plotOn(frame1, RF.Range('lsb_BIG,usb_BIG'),RF.NormRange('lsb_BIG,usb_BIG'))
    #exp_sum.plotOn(frame1, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb_BIG,usb_BIG'), RF.LineStyle(kDashed))
    #epdf_bkg_2exp.plotOn(frame1, RF.Range('lsb_BIG,usb_BIG'),RF.NormRange('lsb_BIG,usb_BIG'), RF.LineStyle(kDashed))
    epdf_bkg.paramOn(frame1, RF.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RF.Format("N", RF.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame1.Draw()

    #import code; code.interact(local=locals())


    indx1.setVal(-5.e-03)
    indx2.setVal(-7.e-09)
    res =  exp_sum.fitTo(  datas[1],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_BIG,usb_BIG'))
    print 'N_bkg ', N_Bkg.getVal()

    frame2 = mass.frame()
    datas[1].plotOn(frame2, RF.CutRange('lsb_BIG,usb_BIG'), RF.Binning(20))
    exp_sum.plotOn(frame2, RF.Range('lsb_BIG,usb_BIG'),RF.NormRange('lsb_BIG,usb_BIG'))
    exp_sum.plotOn(frame2, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb_BIG,usb_BIG'),RF.LineStyle(kDashed))
    epdf_bkg.paramOn(frame2, RF.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RF.Format("N", RF.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame2.Draw()



    indx1.setVal(-5.e-03)
    indx2.setVal(-7.e-09)
    res =  exp_sum.fitTo(  datas[2],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_BIG,usb_BIG'))
    print 'N_bkg ', N_Bkg.getVal()

    frame3 = mass.frame()
    datas[2].plotOn(frame3, RF.CutRange('lsb_BIG,usb_BIG'), RF.Binning(20))
    exp_sum.plotOn(frame3, RF.Range('lsb_BIG,usb_BIG'),RF.NormRange('lsb_BIG,usb_BIG'))
    exp_sum.plotOn(frame3, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb_BIG,usb_BIG'),RF.LineStyle(kDashed))
    epdf_bkg.paramOn(frame3, RF.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RF.Format("N", RF.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame3.Draw()


    indx1.setVal(-5.e-03)
    indx2.setVal(-7.e-09)
    res =  exp_sum.fitTo(  datas[3],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_BIG,usb_BIG'))
    print 'N_bkg ', N_Bkg.getVal()

    frame4 = mass.frame()
    datas[3].plotOn(frame4, RF.CutRange('lsb_BIG,usb_BIG'), RF.Binning(20))
    exp_sum.plotOn(frame4, RF.Range('lsb_BIG,usb_BIG'),RF.NormRange('lsb_BIG,usb_BIG'))
    exp_sum.plotOn(frame4, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb_BIG,usb_BIG'),RF.LineStyle(kDashed))
    epdf_bkg.paramOn(frame4, RF.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RF.Format("N", RF.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame3.Draw()


    #linear fit for background
    DeltaM = 100
    def get_crap(DeltaM):
        dm_lo_cut = ''+BMASS+'>'+str(5215.1-DeltaM)+' && '+BMASS+'<5215.1'
        dm_hi_cut = ''+BMASS+'>5423.1 && '+BMASS+'<'+str(5423.1+DeltaM)
        gl1_cut = 'GLKsm_MC10sb.>=0.   && GLKsm_MC10sb.<0.25'
        gl2_cut = 'GLKsm_MC10sb.>=0.25   && GLKsm_MC10sb.<0.5'
        gl3_cut = 'GLKsm_MC10sb.>=0.5   && GLKsm_MC10sb.<0.75'
        gl4_cut = 'GLKsm_MC10sb.>=0.75   && GLKsm_MC10sb.<1.'

        n_sb = [ t.GetEntries(dm_lo_cut+' && ' +gl1_cut ) + t.GetEntries(dm_hi_cut+' && ' +gl1_cut )
                ,t.GetEntries(dm_lo_cut+' && ' +gl2_cut ) + t.GetEntries(dm_hi_cut+' && ' +gl2_cut )
                ,t.GetEntries(dm_lo_cut+' && ' +gl3_cut ) + t.GetEntries(dm_hi_cut+' && ' +gl3_cut )
                ,t.GetEntries(dm_lo_cut+' && ' +gl4_cut ) + t.GetEntries(dm_hi_cut+' && ' +gl4_cut ) ]
        sn_sb = map(lambda x : sqrt(x), n_sb)

        for i in range(4):
            n__  =  n_sb[i]*208./2./DeltaM
            n__u = (n_sb[i]+sn_sb[i]) *208./2./DeltaM 
            n__d = (n_sb[i]-sn_sb[i]) *208./2./DeltaM
            n__u = abs(n__ - n__u)
            n__d = abs(n__ - n__d)
            print i+1,  n__, ' + ', n__u, ' - ', n__d


    import code; code.interact(local=locals())

    # same for b0window
    epdf_bkg_b0 = RooExtendPdf(  'epdf_bkg', 'extended bkg pdf', expbkg , N_Bkg, 'b0win' )
    epdf_bkg_b0_600 = RooExtendPdf(  'epdf_bkg_600', 'extended bkg pdf', expbkg_600 , N_Bkg, 'b0win' )

    res =  epdf_bkg_b0_600.fitTo(  datas[0],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb,usb'))
    print 'N_bkg ', N_Bkg.getVal()

    frame1 = mass.frame()
    datas[0].plotOn(frame1, RF.CutRange('lsb,usb'), RF.Binning(30))
    epdf_bkg_b0.plotOn(frame1, RF.Range('lsb,usb'),RF.NormRange('lsb,usb'))
    epdf_bkg_b0.plotOn(frame1, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb,usb'),RF.LineStyle(kDashed))
    epdf_bkg_b0.paramOn(frame1) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame1.Draw()


    res =  epdf_bkg_b0_600.fitTo(  datas[1],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb,usb'))
    print 'N_bkg ', N_Bkg.getVal()

    frame2 = mass.frame()
    datas[1].plotOn(frame2, RF.CutRange('lsb,usb'), RF.Binning(30))
    epdf_bkg_b0.plotOn(frame2, RF.Range('lsb,usb'),RF.NormRange('lsb,usb'))
    epdf_bkg_b0.plotOn(frame2, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb,usb'),RF.LineStyle(kDashed))
    epdf_bkg_b0.paramOn(frame2) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame2.Draw()


    res =  epdf_bkg_b0.fitTo(  datas[2],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_BIG,usb_BIG'))
    print 'N_bkg ', N_Bkg.getVal()

    frame3 = mass.frame()
    datas[2].plotOn(frame3, RF.CutRange('lsb,usb'), RF.Binning(10))
    epdf_bkg_b0.plotOn(frame3, RF.Range('lsb,usb'),RF.NormRange('lsb,usb'))
    epdf_bkg_b0.plotOn(frame3, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb,usb'),RF.LineStyle(kDashed))
    epdf_bkg_b0.paramOn(frame3) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame3.Draw()


    res =  epdf_bkg_b0.fitTo(  datas[3],   RF.Extended(True), RF.Minos(True), RF.Strategy(1), RF.Save(True),  RF.Verbose(False)  , RF.Range('lsb_BIG,usb_BIG'))
    print 'N_bkg ', N_Bkg.getVal()

    frame4 = mass.frame()
    datas[3].plotOn(frame4, RF.CutRange('lsb,usb'), RF.Binning(10))
    epdf_bkg_b0.plotOn(frame4, RF.Range('lsb,usb'),RF.NormRange('lsb,usb'))
    epdf_bkg_b0.plotOn(frame4, RF.Range(bsmass-600, bsmass+600), RF.NormRange('lsb,usb'),RF.LineStyle(kDashed))
    epdf_bkg_b0.paramOn(frame4) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
    frame4.Draw()



    # split in mass bins

    #Bs        [n event,   sym. error,    asym. error down, asym. error up ]
    bs_gl = [ [ r_495[0]['N_bkg_exp_Bs'],  r_495[0]['N_bkg_exp_Bs_err'],   r_495[0]['N_bkg_exp_Bs_errLo'],  r_495[0]['N_bkg_exp_Bs_errHi'] ]
             ,[ r_495[1]['N_bkg_exp_Bs'],  r_495[1]['N_bkg_exp_Bs_err'],   r_495[1]['N_bkg_exp_Bs_errLo'],  r_495[1]['N_bkg_exp_Bs_errHi'] ]
             ,[ r_495[2]['N_bkg_exp_Bs'],  r_495[2]['N_bkg_exp_Bs_err'],   r_495[2]['N_bkg_exp_Bs_errLo'],  r_495[2]['N_bkg_exp_Bs_errHi'] ]
             ,[ r_495[3]['N_bkg_exp_Bs'],  r_495[3]['N_bkg_exp_Bs_err'],   r_495[3]['N_bkg_exp_Bs_errLo'],  r_495[3]['N_bkg_exp_Bs_errHi'] ] ]



    b0_gl = [ [ r_495[0]['N_bkg_exp_B0'],  r_495[0]['N_bkg_exp_B0_err'],   r_495[0]['N_bkg_exp_B0_errLo'],  r_495[0]['N_bkg_exp_B0_errHi'] ]
             ,[ r_495[1]['N_bkg_exp_B0'],  r_495[1]['N_bkg_exp_B0_err'],   r_495[1]['N_bkg_exp_B0_errLo'],  r_495[1]['N_bkg_exp_B0_errHi'] ]
             ,[ r_495[2]['N_bkg_exp_B0'],  r_495[2]['N_bkg_exp_B0_err'],   r_495[2]['N_bkg_exp_B0_errLo'],  r_495[2]['N_bkg_exp_B0_errHi'] ]
             ,[ r_495[3]['N_bkg_exp_B0'],  r_495[3]['N_bkg_exp_B0_err'],   r_495[3]['N_bkg_exp_B0_errLo'],  r_495[3]['N_bkg_exp_B0_errHi'] ] ]

    ## #Bs        [n event,   sym. error,    asym. error down, asym. error up ]
    ## bs_gl = [[ 3.29187e+02,   6.40641e+00,  6.36622e+00,   6.44706e+00]
    ##          ,[7.35705e+00,   9.93963e-01,  9.52884e-01,   1.03580e+00]
    ##          ,[1.51084e+00,   3.77100e-01,  3.46432e-01,   4.08750e-01]
    ##          ,[8.09000e-02,   7.24835e-02,  5.02828e-02,   1.04361e-01]]

    ## b0_gl = [[ 3.51626e+02,   6.64085e+00,  6.60104e+00,   6.68078e+00]
    ##          ,[8.29409e+00,   1.03438e+00,  9.92793e-01,   1.07693e+00]
    ##          ,[1.85007e+00,   4.20798e-01,  3.91555e-01,   4.50713e-01]
    ##          ,[1.17776e-01,   9.65081e-02,  6.97859e-02,   1.30645e-01]]


    ## bs_gl = [[ 3.29154e+02, 6.40589e+00, 6.36371e+00, 6.44838e+00]
    ##          ,[7.36010e+00, 9.94101e-01, 9.56613e-01, 1.03190e+00]
    ##          ,[1.51226e+00, 3.77328e-01, 3.47959e-01, 4.07159e-01]
    ##          ,[8.08682e-02, 7.24495e-02, 5.02531e-02, 1.04378e-01]]
    ## #B0
    ## b0_gl = [[ 3.51549e+02, 6.63950e+00, 6.58143e+00, 6.69830e+00]
    ##          ,[8.29223e+00, 1.03422e+00, 9.92631e-01, 1.07676e+00]
    ##          ,[1.85010e+00, 4.20884e-01, 3.92026e-01, 4.50080e-01]
    ##          ,[1.17731e-01, 9.64801e-02, 6.97660e-02, 1.30596e-01]]



    ## bs_gl = [ [328.19, 6.20, 6.16, 6.24 ]  ## status at referess stage
    ##           ,[ 7.72, 0.95, 0.91, 0.99 ]
    ##           ,[ 1.87, 0.47, 0.43, 0.51 ]
    ##           ,[ 0.23, 0.17, 0.13, 0.21 ]
    ##           ]
    ## #B0
    ## b0_gl = [ [350.55, 6.62, 6.58, 6.66 ]
    ##           ,[ 8.25, 1.02, 0.97, 1.06 ]
    ##           ,[ 2.00, 0.50, 0.46, 0.54 ]
    ##           ,[ 0.25, 0.18, 0.14, 0.22 ]
    ##          ]

    mass_binning_bs = [bsmass-60, bsmass-40, bsmass-20, bsmass, bsmass+20, bsmass+40, bsmass+60]
    mass_binning_b0 = [b0mass-60, b0mass-40, b0mass-20, b0mass, b0mass+20, b0mass+40, b0mass+60]

    # from exponential fir of the sidebands:
    ## indx_exp_mass_bkg = -0.000748905   # status at referes version
    ## indx_exp_mass_bkg_error = 5.0168e-05
    ## ##                   [k ,            sym. error, asym. error down, asym. error up ]
    ## indx_exp_mass_bkg_gl =[[ -7.48482e-04, 5.07558e-05, 5.08123e-05, 5.07021e-05]
    ##                        ,[-1.35975e-03, 3.45278e-04, 3.51486e-04, 3.39977e-04]
    ##                        ,[-2.29392e-03, 2.82002e-04, 2.92094e-04, 2.72641e-04]
    ##                        ,[-4.15363e-03, 9.10040e-04, 9.71151e-04, 8.56391e-04]]

    ##                   [k ,            sym. error, asym. error down, asym. error up ]
    ## indx_exp_mass_bkg_gl = [ [-7.48e-04, 5.1e-05, 5.1e-05, 5.1e-05 ]
    ##                         ,[ -1.36e-03, 3.5e-04, 3.4e-04, 3.5e-04 ]
    ##                         ,[ -2.29e-03, 2.8e-04, 2.9e-04, 2.7e-04 ]
    ##                         ,[ -4.15e-03, 9.1e-04, 9.7e-04, 8.6e-04 ]]

    ##                   [k ,            sym. error, asym. error down, asym. error up ]
    indx_exp_mass_bkg_gl = [ [ r_495[0]['k'], r_495[0]['k_err'], r_495[0]['k_errLo'], r_495[0]['k_errHi'] ]
                            ,[ r_495[1]['k'], r_495[1]['k_err'], r_495[1]['k_errLo'], r_495[1]['k_errHi'] ]
                            ,[ r_495[2]['k'], r_495[2]['k_err'], r_495[2]['k_errLo'], r_495[2]['k_errHi'] ]
                            ,[ r_495[3]['k'], r_495[3]['k_err'], r_495[3]['k_errLo'], r_495[3]['k_errHi'] ]]




    to_treat = [ b0_gl, mass_binning_b0 ] # [ bs_gl, mass_binning_bs ] #

    from math import exp, sqrt

    bin_bkg_content = []
    bin_bkg_content_error = []
    bin_bkg_content_error_neg = []
    bin_bkg_content_error_pos = []
    bin_bkg_content_error_neg_neg = []
    bin_bkg_content_error_pos_pos = []

    for i in range(len(to_treat[0])):

        n_bkg_tot =           to_treat[0][i][0]
        n_bkg_tot_error =     to_treat[0][i][1]
        n_bkg_tot_error_neg = to_treat[0][i][2]
        n_bkg_tot_error_pos = to_treat[0][i][3]

        indx_exp_mass_bkg =       indx_exp_mass_bkg_gl[i][0]
        indx_exp_mass_bkg_error =     indx_exp_mass_bkg_gl[i][1]
        indx_exp_mass_bkg_error_neg = indx_exp_mass_bkg_gl[i][2]
        indx_exp_mass_bkg_error_pos = indx_exp_mass_bkg_gl[i][3]

        bin_bkg_content.append([])
        bin_bkg_content_error.append([])
        bin_bkg_content_error_neg.append([])
        bin_bkg_content_error_pos.append([])
        bin_bkg_content_error_neg_neg.append([])
        bin_bkg_content_error_pos_pos.append([])

        mass_binning = to_treat[1]

        # integral of exp inbetween bining values
        for i in range(len(mass_binning)-1):
            bin_bkg_content[-1].append( n_bkg_tot * (exp( indx_exp_mass_bkg * mass_binning[i+1]) - exp(indx_exp_mass_bkg * mass_binning[i]) ) / (exp( indx_exp_mass_bkg * mass_binning[-1]) - exp(indx_exp_mass_bkg * mass_binning[0]) )  )

            bin_bkg_content_error[-1].append( sqrt(
                (indx_exp_mass_bkg_error
                 * n_bkg_tot
                 * (
                +( mass_binning[i+1] - mass_binning[-1])* exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[-1] ))
                -( mass_binning[i+1] - mass_binning[0]) * exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[0] ))
                -(mass_binning[i]  - mass_binning[-1])  * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[-1] ))
                +( mass_binning[i] - mass_binning[0])   * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[0] ))
                )
                 / ( exp( indx_exp_mass_bkg * mass_binning[-1] ) -  exp( indx_exp_mass_bkg * mass_binning[0] ) )**2.
                 )**2.
                +
                (n_bkg_tot_error
                *(exp( indx_exp_mass_bkg * mass_binning[i+1] ) - exp( indx_exp_mass_bkg * mass_binning[i]))
                /(exp( indx_exp_mass_bkg * mass_binning[-1] ) - exp( indx_exp_mass_bkg * mass_binning[0]))
                 )**2.
                ))

            bin_bkg_content_error_neg[-1].append( sqrt(
                (indx_exp_mass_bkg_error
                 * n_bkg_tot
                 * (
                +( mass_binning[i+1] - mass_binning[-1])* exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[-1] ))
                -( mass_binning[i+1] - mass_binning[0]) * exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[0] ))
                -(mass_binning[i]  - mass_binning[-1])  * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[-1] ))
                +( mass_binning[i] - mass_binning[0])   * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[0] ))
                )
                 / ( exp( indx_exp_mass_bkg * mass_binning[-1] ) -  exp( indx_exp_mass_bkg * mass_binning[0] ) )**2.
                 )**2.
                +
                (n_bkg_tot_error_neg
                *(exp( indx_exp_mass_bkg * mass_binning[i+1] ) - exp( indx_exp_mass_bkg * mass_binning[i]))
                /(exp( indx_exp_mass_bkg * mass_binning[-1] ) - exp( indx_exp_mass_bkg * mass_binning[0]))
                 )**2.
                ))

            bin_bkg_content_error_pos[-1].append( sqrt(
                (indx_exp_mass_bkg_error
                 * n_bkg_tot
                 * (
                +( mass_binning[i+1] - mass_binning[-1])* exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[-1] ))
                -( mass_binning[i+1] - mass_binning[0]) * exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[0] ))
                -(mass_binning[i]  - mass_binning[-1])  * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[-1] ))
                +( mass_binning[i] - mass_binning[0])   * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[0] ))
                )
                 / ( exp( indx_exp_mass_bkg * mass_binning[-1] ) -  exp( indx_exp_mass_bkg * mass_binning[0] ) )**2.
                 )**2.
                +
                (n_bkg_tot_error_pos
                *(exp( indx_exp_mass_bkg * mass_binning[i+1] ) - exp( indx_exp_mass_bkg * mass_binning[i]))
                /(exp( indx_exp_mass_bkg * mass_binning[-1] ) - exp( indx_exp_mass_bkg * mass_binning[0]))
                 )**2.
                ))

            bin_bkg_content_error_pos_pos[-1].append( sqrt(
                (indx_exp_mass_bkg_error_pos
                 * n_bkg_tot
                 * (
                +( mass_binning[i+1] - mass_binning[-1])* exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[-1] ))
                -( mass_binning[i+1] - mass_binning[0]) * exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[0] ))
                -(mass_binning[i]  - mass_binning[-1])  * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[-1] ))
                +( mass_binning[i] - mass_binning[0])   * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[0] ))
                )
                 / ( exp( indx_exp_mass_bkg * mass_binning[-1] ) -  exp( indx_exp_mass_bkg * mass_binning[0] ) )**2.
                 )**2.
                +
                (n_bkg_tot_error_pos
                *(exp( indx_exp_mass_bkg * mass_binning[i+1] ) - exp( indx_exp_mass_bkg * mass_binning[i]))
                /(exp( indx_exp_mass_bkg * mass_binning[-1] ) - exp( indx_exp_mass_bkg * mass_binning[0]))
                 )**2.
                ))

            bin_bkg_content_error_neg_neg[-1].append( sqrt(
                (indx_exp_mass_bkg_error_neg
                 * n_bkg_tot
                 * (
                +( mass_binning[i+1] - mass_binning[-1])* exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[-1] ))
                -( mass_binning[i+1] - mass_binning[0]) * exp( indx_exp_mass_bkg * (mass_binning[i+1] + mass_binning[0] ))
                -(mass_binning[i]  - mass_binning[-1])  * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[-1] ))
                +( mass_binning[i] - mass_binning[0])   * exp( indx_exp_mass_bkg * (mass_binning[i] + mass_binning[0] ))
                )
                 / ( exp( indx_exp_mass_bkg * mass_binning[-1] ) -  exp( indx_exp_mass_bkg * mass_binning[0] ) )**2.
                 )**2.
                +
                (n_bkg_tot_error_neg
                *(exp( indx_exp_mass_bkg * mass_binning[i+1] ) - exp( indx_exp_mass_bkg * mass_binning[i]))
                /(exp( indx_exp_mass_bkg * mass_binning[-1] ) - exp( indx_exp_mass_bkg * mass_binning[0]))
                 )**2.
                ))


        print '\n\nfor GL bin with total number event ', n_bkg_tot
        print 'bin_bkg_content', bin_bkg_content[-1]
        print 'bin_bkg_content_error sym', bin_bkg_content_error[-1]
        print 'bin_bkg_content_error neg', bin_bkg_content_error_neg[-1]
        print 'bin_bkg_content_error pos', bin_bkg_content_error_pos  [-1]   
        print 'bin_bkg_content_error neg neg', bin_bkg_content_error_neg_neg[-1]
        print 'bin_bkg_content_error pos pos', bin_bkg_content_error_pos_pos [-1]    
        print 'check sum in bins ', sum(bin_bkg_content[-1])

    # building latex table

    table = ''
    for i in range(len(mass_binning)-1):
        table+=' & $%(n1).4f^{+%(n1_u).4f}_{-%(n1_d).4f}$ & $%(n2).4f^{+%(n2_u).4f}_{-%(n2_d).4f}$ & $%(n3).4f^{+%(n3_u).4f}_{-%(n3_d).4f}$ & $%(n4).4f^{+%(n4_u).4f}_{-%(n4_d).4f}$ \\\\' %\
                    {'n1': bin_bkg_content[0][i], 'n2': bin_bkg_content[1][i], 'n3': bin_bkg_content[2][i], 'n4': bin_bkg_content[3][i]
                     ,'n1_d': bin_bkg_content_error_neg[0][i], 'n2_d': bin_bkg_content_error_neg[1][i], 'n3_d': bin_bkg_content_error_neg[2][i], 'n4_d': bin_bkg_content_error_neg[3][i]
                     ,'n1_u': bin_bkg_content_error_pos[0][i], 'n2_u': bin_bkg_content_error_pos[1][i], 'n3_u': bin_bkg_content_error_pos[2][i], 'n4_u': bin_bkg_content_error_pos[3][i]}
        table+='\n'

    print table


    table = ''
    for i in range(len(mass_binning)-1):
        table+=' & $%(n1).4f^{+%(n1_u).4f}_{-%(n1_d).4f}$ & $%(n2).4f^{+%(n2_u).4f}_{-%(n2_d).4f}$ & $%(n3).4f^{+%(n3_u).4f}_{-%(n3_d).4f}$ & $%(n4).4f^{+%(n4_u).4f}_{-%(n4_d).4f}$ \\TTstrut\\\\' %\
                    {'n1': bin_bkg_content[0][i], 'n2': bin_bkg_content[1][i], 'n3': bin_bkg_content[2][i], 'n4': bin_bkg_content[3][i]
                     ,'n1_d': bin_bkg_content_error_neg_neg[0][i], 'n2_d': bin_bkg_content_error_neg_neg[1][i], 'n3_d': bin_bkg_content_error_neg_neg[2][i], 'n4_d': bin_bkg_content_error_neg_neg[3][i]
                     ,'n1_u': bin_bkg_content_error_pos_pos[0][i], 'n2_u': bin_bkg_content_error_pos_pos[1][i], 'n3_u': bin_bkg_content_error_pos_pos[2][i], 'n4_u': bin_bkg_content_error_pos_pos[3][i]}
        table+='\n'


    print table
