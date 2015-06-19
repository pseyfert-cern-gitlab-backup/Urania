from ROOT import *
from ROOT import TBrowser
gSystem.Load("libRooFit")
gROOT.ProcessLine(".x lhcbstyle.C")

from ROOT import TFile, RooFit, RooExtendPdf, RooRealVar, RooAddPdf, RooArgList, RooExponential
from ROOT import RooDataSet , RooArgSet, RooBinning, TPaveText, RooPolynomial, TFeldmanCousins
from datetime import date
from array import array

datestamp = date.today().strftime('%Y%m%d')


def get_graph( h, t , lines=None ):
    """ lines = [ bs-60, bs+60, b0-60, b0+60]
    """
    for i in range(t.GetEntries()):
        t.GetEntry(i)
        h.Fill(t.Bmass)
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
    g.GetXaxis().SetRangeUser(bsmass_pdg-600, 6000)
    g.GetXaxis().SetTitle('m_{#mu#mu} (MeV/c^{2})')
    binW = int(h.GetBinWidth(0)*100)/1/100.
    g.GetYaxis().SetTitle('Events/('+str(binW)+' MeV/c^{2})')
    
    
    if lines != None:
        min = g.GetYaxis().GetXmin()
        max = g.GetYaxis().GetXmax()
        l_Bs_d = TLine( lines[0], min, lines[0], max )
        l_Bs_u = TLine( lines[1], min, lines[1], max )
        l_B0_d = TLine( lines[2], min, lines[2], max )
        l_B0_u = TLine( lines[3], min, lines[3], max )
        l_Bs_d.SetLineWidth(4) ; l_Bs_d.SetLineColor(807) ; l_Bs_d.SetLineStyle(2)
        l_Bs_u.SetLineWidth(4) ; l_Bs_u.SetLineColor(807) ; l_Bs_u.SetLineStyle(2)
        l_B0_d.SetLineWidth(4) ; l_B0_d.SetLineColor(418) ; l_B0_d.SetLineStyle(9)
        l_B0_u.SetLineWidth(4) ; l_B0_u.SetLineColor(418) ; l_B0_u.SetLineStyle(9)
        return h, g, [l_Bs_d, l_Bs_u], [l_B0_d, l_B0_u]
    else:
        return h, g

def plot_exp(canvas, h, k, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    fexp   = TF1( 'fun_exp', '[0]*TMath::Exp([1]*x)' , bsmass_pdg-600, 6000 )
    fexp.SetParameters(h.GetBinWidth(0) * k * Nsb / ( exp(k*SB2) - exp(k*SB1) + exp(k*SB4) - exp(k*SB3) ), k )
    fexp.SetLineColor(color);fexp.SetLineWidth(4)    
    fexp.SetRange(SB1,SB2);fexp.SetLineStyle(1);fexp.DrawCopy('SAME')
    fexp.SetRange(SB3,SB4);fexp.SetLineStyle(1);fexp.DrawCopy('SAME')
    fexp.SetRange(bsmass_pdg-600,6000);fexp.SetLineStyle(2);fexp.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_lin(canvas, h, c, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    flin = TF1( 'fun_lin', '([0]+[1]*x)*[2]' , bsmass_pdg-600, 6000 )
    #flin = TF1( 'fun_lin', '[0]+[1]*x' , bsmass_pdg-600, 6000 )
    flin.SetParameters( Nsb-c*0.5*(SB2*SB2+SB4*SB4-SB1*SB1-SB3*SB3)/(SB2+SB4-SB1-SB3), c , 1./h.GetBinWidth(0) )
    #flin.SetParameters( Nsb-c*0.5*(SB2*SB2+SB4*SB4-SB1*SB1-SB3*SB3)/(SB2+SB4-SB1-SB3), c )
    flin.SetLineColor(color);flin.SetLineWidth(4)
    flin.SetRange(SB1,SB2);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(SB3,SB4);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(bsmass_pdg-600,6000);flin.SetLineStyle(2);flin.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_lin_Giacomo(canvas, h, c, Nsb, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    flin = TF1( 'fun_lin', '([0]+[1]*x)*[2]' , bsmass_pdg-600, 6000 )
    #flin = TF1( 'fun_lin', '[0]+[1]*x' , bsmass_pdg-600, 6000 )
    flin.SetParameters( (1-c*0.5*(SB4*SB4-SB1*SB1))/(SB4-SB1), c , Nsb*h.GetBinWidth(0) )
    #flin.SetParameters( Nsb-c*0.5*(SB2*SB2+SB4*SB4-SB1*SB1-SB3*SB3)/(SB2+SB4-SB1-SB3), c )
    flin.SetLineColor(color);flin.SetLineWidth(4)
    flin.SetRange(SB1,SB2);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(SB3,SB4);flin.SetLineStyle(1);flin.DrawCopy('SAME')
    flin.SetRange(bsmass_pdg-600,6000);flin.SetLineStyle(2);flin.DrawCopy('SAME')
    canvas.Update()
    return canvas

def plot_root(canvas, h, SB1, SB2, SB3, SB4, color):
    canvas.cd()
    
    h1 = TH1F()
    h.Copy(h1)
    
    for i in range(h1.GetNbinsX()):
        if h1.GetBinCenter(i+1)>SB2 and h1.GetBinCenter(i+1)<SB3:
            h1.SetBinError(i+1, h1.GetBinError(i+1)*1000. )
    
    f_lin_root = TF1( 'fun_lin', '[0]+[1]*x' , SB1, SB4 )
    h1.Fit(f_lin_root, 'N')
    f_lin_root.SetLineColor(color);f_lin_root.SetLineWidth(4)
    f_lin_root.SetRange(bsmass_pdg-600,b0mass-60);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(bsmass+60,6000);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(bsmass_pdg-600,6000);f_lin_root.SetLineStyle(2);f_lin_root.DrawCopy('SAME')
    
    h1.Delete()
    canvas.Update()
    return canvas

def plot_root_(canvas, h, SB1, SB2, SB3, SB4, color):
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
    f_lin_root.SetRange(bsmass_pdg-600,b0mass-60);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(bsmass+60,6000);f_lin_root.SetLineStyle(1);f_lin_root.DrawCopy('SAME')
    f_lin_root.SetRange(bsmass_pdg-600,6000);f_lin_root.SetLineStyle(2);f_lin_root.DrawCopy('SAME')
    
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
    c1.SaveAs(name+'.root')
    c1.Delete()

##C this flags drives the saving of the plots
plot_all = True


##C loading of the ntuple
who = 'diego' #'flavio'
if who == 'flavio':
    discriminant =  'BDTflat'#'gl' #
    if discriminant == 'BDTflat':
        f = TFile('/afs/cern.ch/lhcb/group/physics/bsmumu/ntuples/2011/Blind_150pb/Datareco10_original_newVar_wide.root')
        t = f.Get('ntpl')
    else:
       f = TFile('/afs/cern.ch/lhcb/group/physics/bsmumu/ntuples/2011/Blind_150pb/data_gl_6var_newVar_wide.root') 
       t = f.Get('ntpl')
    
    Ismuon1 = 'ism1'
    Ismuon2 = 'ism2' 
else:
    f = TFile('/afs/cern.ch/user/d/diegoms/vol5/NTuples/BsKstKst_300pb.root')# it is Bsmumu!
    #('/afs/cern.ch/user/d/diegoms/vol5/NTuples/stp13_300_blind_on_the_run.root')
    #('/afs/cern.ch/lhcb/group/physics/bsmumu/ntuples/2011/Blind_300pb/stp13_300_blind.root')
    #('/afs/cern.ch/lhcb/group/physics/bsmumu/ntuples/2011/Blind_150pb/stp13_cern_bsmm_BDT.root.root') #stp13_dms.root')
    t = f.Get('Bs2MuMu')#'B2hh')#
    discriminant = 'BDTflat' #'GL11sb'###'GLKsm_MC10sb.' #'BDTflat'
    Ismuon1 = 'mu1ismu'
    Ismuon2 = 'mu2ismu'


##C definition of some of the parameters
c_lin = RooRealVar("c", "c", 0., -10., 10.)
N_Bkg_lin  = RooRealVar( 'N_{bkg}_lin', 'Number of Bkg linear fit',  0.5*t.GetEntries() , 0, t.GetEntries())

indx       = RooRealVar("k", "k", -1.e-04, -1., 0.1)
indx_modSB = RooRealVar("k_modSB", "k_modSB", -1.e-04, -1., 0.1)
indx_right = RooRealVar("k_right", "k_right", -1.e-04, -1., 0.1)
N_Bkg  = RooRealVar( 'N_{bkg}', 'Number of Bkg',  0.5*t.GetEntries() , 0, t.GetEntries())
N_Bkg_modSB  = RooRealVar( 'N_{bkg}_modSB', 'Number of Bkg_modSB',  0.5*t.GetEntries() , 0, t.GetEntries())
N_Bkg_right  = RooRealVar( 'N_{bkg}_right', 'Number of Bkg_right',  0.5*t.GetEntries() , 0, t.GetEntries())

mu1ismu = RooRealVar(Ismuon1, Ismuon1, 0, 1)
mu2ismu = RooRealVar(Ismuon2, Ismuon2, 0, 1)
GLKsm = RooRealVar("GL", "GL", 0., 1.)

## double exponential
indx1 = RooRealVar("k1", "k1", -5.e-03, -1., 0.)
indx2 = RooRealVar("k2", "k2", -7.e-09, -1., 0.)
N_1  = RooRealVar( 'N_{bkg}1', 'Number of Bkg 1',   25 , 0, t.GetEntries())
N_2  = RooRealVar( 'N_{bkg}2', 'Number of Bkg 2',   2 , 0, t.GetEntries())
N_Bkg_doublexp  = RooRealVar('N_{bkg}', 'Number of Bkg',  0.5*t.GetEntries() , 0, t.GetEntries())


##C mean of the mass for Bs and Bd
bsmass = 5358  #5363.1
b0mass = 5272  #5275.01 #5275.1

bsmass_pdg = 5366.3
b0mass_pdg = 5279.5

blind_region_low  = 5212 #5207 #5179 #b0mass-60
blind_region_high = 5418 #5423 #5466 #bsmass+60

mass = RooRealVar('Bmass', 'm_{#mu#mu}', bsmass_pdg-1200, bsmass_pdg+1200, 'MeV/c^{2}')
mass_600 = RooRealVar('Bmass', 'm_{#mu#mu}', bsmass_pdg-600, 6000, 'MeV/c^{2}')#, bsmass_pdg+600, 'MeV/c^{2}')
mass_600.setRange("lsb", bsmass_pdg-600, blind_region_low )
mass_600.setRange("usb", blind_region_high, 6000)#bsmass_pdg+600 )
mass_600.setRange("lsb49005000", 4900, 5000 )

mass_600.setRange("lsb_400", bsmass_pdg-400, blind_region_low )
mass_600.setRange("usb_400", blind_region_high, bsmass_pdg+400 )

mass.setRange("lsb_BIG", bsmass_pdg-1200, blind_region_low )
mass.setRange("usb_BIG", blind_region_high, bsmass_pdg+1200 )

mass_600.setRange("bswin", bsmass-60, bsmass+60)
mass_600.setRange("b0win", b0mass-60, b0mass+60)
mass.setRange("bswin", bsmass-60, bsmass+60)
mass.setRange("b0win", b0mass-60, b0mass+60)
mass.setRange("blinded", blind_region_low , blind_region_high )

mass.setRange("bswin1", bsmass-60, bsmass-40)
mass.setRange("bswin2", bsmass-40, bsmass-20)
mass.setRange("bswin3", bsmass-20, bsmass)
mass.setRange("bswin4", bsmass,    bsmass+20)
mass.setRange("bswin5", bsmass+20, bsmass+40)
mass.setRange("bswin6", bsmass+40, bsmass+60)

mass.setRange("b0win1", b0mass-60, b0mass-40)
mass.setRange("b0win2", b0mass-40, b0mass-20)
mass.setRange("b0win3", b0mass-20, b0mass)
mass.setRange("b0win4", b0mass,    b0mass+20)
mass.setRange("b0win5", b0mass+20, b0mass+40)
mass.setRange("b0win6", b0mass+40, b0mass+60)

lsb_cut = 'Bmass>'+str(bsmass_pdg-600)+' && Bmass<'+str(blind_region_low)
lsb_cut_4900_5000 =  'Bmass>4900 && Bmass<5000'
usb_cut = 'Bmass>'+str(blind_region_high)+' && Bmass<6000'#+str(bsmass_pdg+600)
lsb_BIG_cut = 'Bmass>'+str(bsmass_pdg-1200)+' && Bmass<'+str(blind_region_low)
usb_BIG_cut = 'Bmass>'+str(blind_region_high)+' && Bmass<'+str(b0mass_pdg+1200)



##C futher cuts, giampi_cut:= fiducial cuts
##C              ultra_blind was to get a blind sample from Diego's partially blind one
giampi_cut = True; giampi_cut_str=''
if giampi_cut:
    giampi_cut_str = "  && Bpt >500 && Blife_ps_r < 7.36 && mu1ptot<1e06 && mu2ptot<1e06"

ultra_blind = False; ultra_str = ''
if ultra_blind :
    ultra_str = "  && (Bmass<"+str(blind_region_low)+" || Bmass>"+str(blind_region_high)+" )"


fout = TFile('/localscratch/mbettler/Root_crap.root', "RECREATE")
fout.cd()


##C separation of the data per bin and construction of the RooDataSets
t1 =  t.CopyTree(discriminant+'>=0.   && '+discriminant+'<0.25 && '+Ismuon1+'==1 && '+Ismuon2+'==1 && Bmass>3800 && Bmass<6500'+giampi_cut_str+ultra_str)
t2 =  t.CopyTree(discriminant+'>=0.25 && '+discriminant+'<0.5  && '+Ismuon1+'==1 && '+Ismuon2+'==1 && Bmass>3800 && Bmass<6500'+giampi_cut_str+ultra_str)
t3 =  t.CopyTree(discriminant+'>=0.5  && '+discriminant+'<0.75 && '+Ismuon1+'==1 && '+Ismuon2+'==1 && Bmass>3800 && Bmass<6500'+giampi_cut_str+ultra_str)
t4 =  t.CopyTree(discriminant+'>=0.75 && '+discriminant+'<=1.  && '+Ismuon1+'==1 && '+Ismuon2+'==1 && Bmass>3800 && Bmass<6500'+giampi_cut_str+ultra_str)
#t34 = t.CopyTree(discriminant+'>=0.5  && '+discriminant+'<=1.  && '+Ismuon1+'==1 && '+Ismuon2+'==1 && Bmass>3800 && Bmass<6500'+giampi_cut_str+ultra_str)

#data = RooDataSet("data","data", t, RooArgSet(mass, mu1ismu, mu2ismu), Ismuon1+"==1 && "+Ismuon2+"==1")
#data_600 = RooDataSet("data600","data600", t, RooArgSet(mass, mu1ismu, mu2ismu), "Bmass>4766.3 && Bmass<5966.3 && "+Ismuon1+"==1 && "+Ismuon2+"==1")
data1 = RooDataSet("data1","data1", t1, RooArgSet(mass, mu1ismu, mu2ismu),     Ismuon1+"==1 && "+Ismuon2+"==1")
data2 = RooDataSet("data2","data2", t2, RooArgSet(mass, mu1ismu, mu2ismu),     Ismuon1+"==1 && "+Ismuon2+"==1")
data3 = RooDataSet("data3","data3", t3, RooArgSet(mass, mu1ismu, mu2ismu),     Ismuon1+"==1 && "+Ismuon2+"==1")
data4 = RooDataSet("data4","data4", t4, RooArgSet(mass, mu1ismu, mu2ismu),     Ismuon1+"==1 && "+Ismuon2+"==1")
#data34 = RooDataSet("data34","data34", t34, RooArgSet(mass, mu1ismu, mu2ismu), Ismuon1+"==1 && "+Ismuon2+"==1")


##C definition of the pdf and extended pdfs
##C 
##C  
##C
##C
##C
##C


polbkg = RooPolynomial("polbkg", "polbkg pdf", mass, RooArgList( c_lin ) )
polbkg_600 = RooPolynomial("polbkg600", "polbkg600 pdf", mass_600, RooArgList( c_lin ) )

epdf_bkg_lin     = RooExtendPdf(  'epdf_bkg_lin', 'extended bkg pdf_lin'        , polbkg , N_Bkg_lin, 'blinded' )#'bswin' )
epdf_bkg_lin_600_bs = RooExtendPdf(  'epdf_bkg_lin_600', 'extended bkg pdf_lin 600', polbkg_600 , N_Bkg_lin, 'bswin' )
epdf_bkg_lin_600_b0 = RooExtendPdf(  'epdf_bkg_lin_600', 'extended bkg pdf_lin 600', polbkg_600 , N_Bkg_lin, 'b0win' )

expbkg = RooExponential("expbkg", " exp background pdf", mass, indx)
expbkg_600 = RooExponential("expbkg_600", " exp background pdf_600", mass_600, indx )
expbkg_600_modSB = RooExponential("expbkg_600", " exp background pdf_600", mass_600, indx_modSB )
expbkg_600_right = RooExponential("expbkg_600", " exp background pdf_600", mass_600, indx_right )


epdf_bkg = RooExtendPdf(  'epdf_bkg', 'extended bkg pdf', expbkg , N_Bkg, 'blinded')#'bswin' )
epdf_bkg_600_bs = RooExtendPdf(  'epdf_bkg_600', 'extended bkg pdf 600', expbkg_600 , N_Bkg, 'bswin' )
epdf_bkg_600_b0 = RooExtendPdf(  'epdf_bkg_600', 'extended bkg pdf 600', expbkg_600 , N_Bkg, 'b0win' )
epdf_bkg_600_bs_modSB = RooExtendPdf(  'epdf_bkg_600_modSB', 'extended bkg pdf 600_modSB', expbkg_600_modSB, N_Bkg_modSB, 'bswin' )
epdf_bkg_600_b0_modSB = RooExtendPdf(  'epdf_bkg_600_modSB', 'extended bkg pdf 600_modSB', expbkg_600_modSB, N_Bkg_modSB, 'b0win' )
epdf_bkg_600_bs_rightSB = RooExtendPdf(  'epdf_bkg_600_rightSB', 'extended bkg pdf 600_rightSB', expbkg_600_right, N_Bkg_right, 'bswin' )
epdf_bkg_600_b0_rightSB = RooExtendPdf(  'epdf_bkg_600_rightSB', 'extended bkg pdf 600_rightSB', expbkg_600_right, N_Bkg_right, 'b0win' )


expbkg1 = RooExponential("expbkg1", " exp background pdf1", mass, indx1)
expbkg2 = RooExponential("expbkg2", " exp background pdf2", mass, indx2)

#RooAddPdf sum("sum","g1+g2+a",RooArgList(gauss1,gauss2,argus),RooArgList(g1frac,g2frac)) ;
exp_sum = RooAddPdf('exp_sum', 'exp_sum', RooArgList(expbkg1,expbkg2), RooArgList(N_1,N_2))




## res = epdf_bkg.fitTo( data, RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True), RooFit.Verbose(False), RooFit.Range('lsb_BIG,usb_BIG'))

## res = epdf_bkg.fitTo( data_600, RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True), RooFit.Verbose(False), RooFit.Range('lsb_BIG,usb_BIG'))

## frame = mass.frame()

## data.plotOn(frame, RooFit.Range('lsb_BIG,usb_BIG'))#, RooFit.Binning(custom_bin))

## epdf_bkg.plotOn(frame, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
## epdf_bkg.plotOn(frame, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'),RooFit.LineStyle(kDashed))
## #epdf_bkg.plotOn(frame,RooFit.NormRange('lsb,usb'))
## epdf_bkg.paramOn(frame, RooFit.Layout(0.556034, 0.909483, 0.917373))
## frame.Draw()

## lhcb = do_lhcb_label(0.20, 0.85, .90, 0.9)
## lhcb.Draw()

#save_this(frame, 'Bkg_mass_fit_AllGLRange')


##C these list will contains the relevant informations from the fits to follow
r_exp   = []
r_lin   = []
r_495   = []
r_right = []

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


indx.setConstant(False)
res =  epdf_bkg_600_bs.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant()
r_exp.append({'Operator':discriminant, 'Bin':1, 'N_bkg_exp_Bs':N_Bkg.getVal(), 'N_bkg_exp_Bs_err': N_Bkg.getError(),'N_bkg_exp_Bs_errHi':N_Bkg.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg.getAsymErrorLo(), 'k': indx.getVal(), 'k_err':indx.getError(), 'k_errHi':indx.getAsymErrorHi(), 'k_errLo':indx.getAsymErrorLo()})

res =  epdf_bkg_600_b0.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant(False)
r_exp[-1]['N_bkg_exp_B0'] = N_Bkg.getVal(); r_exp[-1]['N_bkg_exp_B0_err'] = N_Bkg.getError(); r_exp[-1]['N_bkg_exp_B0_errHi'] = N_Bkg.getAsymErrorHi(); r_exp[-1]['N_bkg_exp_B0_errLo'] = N_Bkg.getAsymErrorLo()


N_Bkg_lin.setVal(1000)
c_lin.setVal(-0.00014)
c_lin.setMin(-0.01)
c_lin.setMax(0.)
c_lin.setConstant(False)
res =  epdf_bkg_lin_600_bs.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant()
r_lin.append({}); r_lin[-1]['N_bkg_lin_Bs'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_Bs_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_Bs_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_Bs_errLo'] = N_Bkg_lin.getAsymErrorLo(); r_lin[-1]['c'] = c_lin.getVal(); r_lin[-1]['c_err'] = c_lin.getError(); r_lin[-1]['c_errHi'] = c_lin.getAsymErrorHi(); r_lin[-1]['c_errLo'] = c_lin.getAsymErrorLo()

res =  epdf_bkg_lin_600_b0.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant(False)
r_lin[-1]['N_bkg_lin_B0'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_B0_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_B0_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_B0_errLo'] = N_Bkg_lin.getAsymErrorLo()


indx_modSB.setConstant(False)
res =  epdf_bkg_600_bs_modSB.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant()
r_495.append({'SB':'lsb49005000,usb' , 'Operator':discriminant, 'Bin':1, 'N_bkg_exp_Bs':N_Bkg_modSB.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_modSB.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_modSB.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_modSB.getAsymErrorLo(), 'k': indx_modSB.getVal(), 'k_err':indx_modSB.getError(), 'k_errHi':indx_modSB.getAsymErrorHi(), 'k_errLo':indx_modSB.getAsymErrorLo()})

res =  epdf_bkg_600_b0_modSB.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant(False)
r_495[-1]['N_bkg_exp_B0'] = N_Bkg_modSB.getVal(); r_495[-1]['N_bkg_exp_B0_err'] = N_Bkg_modSB.getError(); r_495[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_modSB.getAsymErrorHi(); r_495[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_modSB.getAsymErrorLo()


indx_right.setConstant(False)
res =  epdf_bkg_600_bs_rightSB.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant()
r_right.append({'SB':'usb' , 'Operator':discriminant, 'Bin':1, 'N_bkg_exp_Bs':N_Bkg_right.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_right.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_right.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_right.getAsymErrorLo(), 'k': indx_right.getVal(), 'k_err':indx_right.getError(), 'k_errHi':indx_right.getAsymErrorHi(), 'k_errLo':indx_right.getAsymErrorLo()})

res =  epdf_bkg_600_b0_rightSB.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant(False)
r_right[-1]['N_bkg_exp_B0'] = N_Bkg_right.getVal(); r_right[-1]['N_bkg_exp_B0_err'] = N_Bkg_right.getError(); r_right[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_right.getAsymErrorHi(); r_right[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_right.getAsymErrorLo()



###
##C then the fits are plotted via two different methods.
##C One is custom made, the other is using roofit (seems buggy when the binning is
##C specified  in data1.plotOn(frame1) )


t= t1
bins = 40
h = TH1F("Bin1","Bin1",bins,bsmass_pdg-600, 6000)
h, g, ls, l0 = get_graph( h, t, lines= [bsmass-60, bsmass+60, b0mass-60, b0mass+60] )

can = TCanvas('_', '_', 800,600)
g.Draw('AP')
ls[0].Draw()
ls[1].Draw()
l0[0].Draw()
l0[1].Draw()

can = plot_exp(can, h, r_495[-1]['k'], t.GetEntries(lsb_cut_4900_5000)+t.GetEntries(usb_cut), 4900, 5000, bsmass+60, 6000, 3)
if plot_all:
    can = plot_exp(can, h, r_exp[-1]['k'], t.GetEntries(lsb_cut)+t.GetEntries(usb_cut), bsmass_pdg-600, b0mass-60, bsmass+60, 6000, 4)
    can = plot_exp(can, h, r_right[-1]['k'], t.GetEntries(usb_cut), 0, 0, bsmass+60, 6000, 6)
    can = plot_root(can, h, bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 2)



lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305)
lhcb.Draw()

can.SaveAs(discriminant+'_Root_1_600_'+datestamp+'.png')
can.SaveAs(discriminant+'_Root_1_600_'+datestamp+'.pdf')
can.SaveAs(discriminant+'_Root_1_600_'+datestamp+'.root')

h.Delete()


#can = plot_lin(can, r_lin[-1]['c'], t.GetEntries(lsb_cut)+t.GetEntries(usb_cut), bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 2)




###
frame1 = mass_600.frame()
data1.plotOn(frame1)#, RooFit.CutRange('lsb,usb'))

## int_modSB = epdf_bkg_600_bs_modSB.createIntegral( RooArgSet(mass), RooFit.Range('lsb49005000,usb'))
## int_modSB.getVal()

## int_exp = epdf_bkg_600_bs.createIntegral( RooArgSet(mass), RooFit.Range('lsb,usb'))
## int_exp.getVal()

## epdf_bkg_600_bs_modSB.plotOn(frame1,Normalization(1.0,RooAbsReal::RelativeExtended),RooFit.LineColor(3))

epdf_bkg_600_bs_modSB.plotOn(frame1, RooFit.Range('lsb49005000,usb'), RooFit.NormRange('lsb49005000,usb'),RooFit.LineColor(3))
epdf_bkg_600_bs_modSB.plotOn(frame1, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb49005000,usb'),RooFit.LineStyle(kDashed),RooFit.LineColor(3))

epdf_bkg_600_bs.plotOn(frame1, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_600_bs.plotOn(frame1, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed))

epdf_bkg_lin_600_bs.plotOn(frame1, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'),RooFit.LineColor(2))
epdf_bkg_lin_600_bs.plotOn(frame1, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(2))


epdf_bkg_600_bs_rightSB.plotOn(frame1, RooFit.Range('usb'),RooFit.NormRange('usb'),RooFit.LineColor(3))
epdf_bkg_600_bs_rightSB.plotOn(frame1, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(3))

frame1.Draw()
lhcb = do_lhcb_label(0.175287, 0.23, 0.389368, 0.31 , prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
save_this(frame1, discriminant+'_1_600_'+datestamp, lhcb)


frame1 = mass.frame()
data1.plotOn(frame1, RooFit.Binning(40))#, RooFit.CutRange('lsb,usb'))
frame1.Draw()
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305)
lhcb.Draw()
save_this(frame1, discriminant+'_1_1200_'+datestamp, lhcb)



############## second bin


indx.setConstant(False)
res =  epdf_bkg_600_bs.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant()
r_exp.append({'Bin':2, 'N_bkg_exp_Bs':N_Bkg.getVal(), 'N_bkg_exp_Bs_err': N_Bkg.getError(),'N_bkg_exp_Bs_errHi':N_Bkg.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg.getAsymErrorLo(), 'k': indx.getVal(), 'k_err':indx.getError(), 'k_errHi':indx.getAsymErrorHi(), 'k_errLo':indx.getAsymErrorLo()})

res =  epdf_bkg_600_b0.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant(False)
r_exp[-1]['N_bkg_exp_B0'] = N_Bkg.getVal(); r_exp[-1]['N_bkg_exp_B0_err'] = N_Bkg.getError(); r_exp[-1]['N_bkg_exp_B0_errHi'] = N_Bkg.getAsymErrorHi(); r_exp[-1]['N_bkg_exp_B0_errLo'] = N_Bkg.getAsymErrorLo()


c_lin.setConstant(False)
res =  epdf_bkg_lin_600_bs.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant()
r_lin.append({});  r_lin[-1]['N_bkg_lin_Bs'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_Bs_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_Bs_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_Bs_errLo'] = N_Bkg_lin.getAsymErrorLo(); r_lin[-1]['c'] = c_lin.getVal(); r_lin[-1]['c_err'] = c_lin.getError(); r_lin[-1]['c_errHi'] = c_lin.getAsymErrorHi(); r_lin[-1]['c_errLo'] = c_lin.getAsymErrorLo()

res =  epdf_bkg_lin_600_b0.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant(False)
r_lin[-1]['N_bkg_lin_B0'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_B0_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_B0_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_B0_errLo'] = N_Bkg_lin.getAsymErrorLo()

indx_modSB.setConstant(False)
res =  epdf_bkg_600_bs_modSB.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant()
r_495.append({'SB':'lsb49005000,usb' , 'Operator':discriminant, 'Bin':2, 'N_bkg_exp_Bs':N_Bkg_modSB.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_modSB.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_modSB.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_modSB.getAsymErrorLo(), 'k': indx_modSB.getVal(), 'k_err':indx_modSB.getError(), 'k_errHi':indx_modSB.getAsymErrorHi(), 'k_errLo':indx_modSB.getAsymErrorLo()})

res =  epdf_bkg_600_b0_modSB.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant(False)
r_495[-1]['N_bkg_exp_B0'] = N_Bkg_modSB.getVal(); r_495[-1]['N_bkg_exp_B0_err'] = N_Bkg_modSB.getError(); r_495[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_modSB.getAsymErrorHi(); r_495[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_modSB.getAsymErrorLo()


indx_right.setConstant(False)
res =  epdf_bkg_600_bs_rightSB.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant()
r_right.append({'SB':'usb' , 'Operator':discriminant, 'Bin':2, 'N_bkg_exp_Bs':N_Bkg_right.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_right.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_right.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_right.getAsymErrorLo(), 'k': indx_right.getVal(), 'k_err':indx_right.getError(), 'k_errHi':indx_right.getAsymErrorHi(), 'k_errLo':indx_right.getAsymErrorLo()})

res =  epdf_bkg_600_b0_rightSB.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant(False)
r_right[-1]['N_bkg_exp_B0'] = N_Bkg_right.getVal(); r_right[-1]['N_bkg_exp_B0_err'] = N_Bkg_right.getError(); r_right[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_right.getAsymErrorHi(); r_right[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_right.getAsymErrorLo()


t= t2
bins = 30
h = TH1F("Bin1","Bin1",bins,bsmass_pdg-600, 6000)
h, g, ls, l0 = get_graph( h, t, lines= [bsmass-60, bsmass+60, b0mass-60, b0mass+60] )

can = TCanvas('_', '_', 800,600)
g.Draw('AP')
can = plot_exp(can, h, r_495[-1]['k'], t.GetEntries(lsb_cut_4900_5000)+t.GetEntries(usb_cut), 4900, 5000, bsmass_pdg+60, 6000, 3)
ls[0].Draw()
ls[1].Draw()
l0[0].Draw()
l0[1].Draw()

if plot_all:
    can = plot_exp(can, h, r_exp[-1]['k'], t.GetEntries(lsb_cut)+t.GetEntries(usb_cut), bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 4)
    can = plot_exp(can, h, r_right[-1]['k'], t.GetEntries(usb_cut), 0, 0, bsmass_pdg+60, 6000, 6)

    can = plot_root(can, h, bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 2)

lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
can.SaveAs(discriminant+'_Root_2_600_'+datestamp+'.png')
can.SaveAs(discriminant+'_Root_2_600_'+datestamp+'.pdf')
can.SaveAs(discriminant+'_Root_2_600_'+datestamp+'.root')

h.Delete()



frame2 = mass_600.frame()
data2.plotOn(frame2, RooFit.Binning(30))#, RooFit.CutRange('lsb,usb'), RooFit.Binning(20))
epdf_bkg_600_bs.plotOn(frame2, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_600_bs.plotOn(frame2, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed))

epdf_bkg_lin_600_bs.plotOn(frame2, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'),RooFit.LineColor(2))
epdf_bkg_lin_600_bs.plotOn(frame2, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed),RooFit.LineColor(2))

epdf_bkg_600_bs_modSB.plotOn(frame2, RooFit.Range('lsb49005000,usb'),RooFit.NormRange('lsb49005000,usb'),RooFit.LineColor(3))
epdf_bkg_600_bs_modSB.plotOn(frame2, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb49005000,usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(3))

epdf_bkg_600_bs_rightSB.plotOn(frame2, RooFit.Range('usb'),RooFit.NormRange('usb'),RooFit.LineColor(6))
epdf_bkg_600_bs_rightSB.plotOn(frame2, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(6))

#epdf_bkg_600.paramOn(frame2, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#)
frame2.Draw()
lhcb = do_lhcb_label(0.175287, 0.23, 0.389368, 0.31 , prelim=True)#(0.278736, 0.811441, 0.492816, 0.889831, prelim=True )#0.765805, 0.813559, 0.979885, 0.898305, prelim=True )
lhcb.Draw()
save_this(frame2, discriminant+'_2_600_'+datestamp, lhcb)

frame2 = mass.frame()
data2.plotOn(frame2, RooFit.Binning(30))#, RooFit.CutRange('lsb,usb'))
frame2.Draw()
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
save_this(frame2, discriminant+'_2_1200_'+datestamp, lhcb)


##### third bin

## res =  epdf_bkg.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
## print 'N_bkg ', N_Bkg.getVal()

## frame3 = mass.frame()
## data3.plotOn(frame3, RooFit.Binning(20), RooFit.CutRange('lsb_BIG,usb_BIG'))
## epdf_bkg.plotOn(frame3, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
## epdf_bkg.plotOn(frame3, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'),RooFit.LineStyle(kDashed))
## epdf_bkg.paramOn(frame3, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
## frame3.Draw()
## lhcb = do_lhcb_label(0.658046, 0.654, 0.872126, 0.739, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
## lhcb.Draw()
## save_this(frame3, discriminant+'_3_1200')

# third 600MeV

indx.setConstant(False)
res =  epdf_bkg_600_bs.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant()
r_exp.append({'Bin':3, 'N_bkg_exp_Bs':N_Bkg.getVal(), 'N_bkg_exp_Bs_err': N_Bkg.getError(),'N_bkg_exp_Bs_errHi':N_Bkg.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg.getAsymErrorLo(), 'k': indx.getVal(), 'k_err':indx.getError(), 'k_errHi':indx.getAsymErrorHi(), 'k_errLo':indx.getAsymErrorLo()})

res =  epdf_bkg_600_b0.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant(False)
r_exp[-1]['N_bkg_exp_B0'] = N_Bkg.getVal(); r_exp[-1]['N_bkg_exp_B0_err'] = N_Bkg.getError(); r_exp[-1]['N_bkg_exp_B0_errHi'] = N_Bkg.getAsymErrorHi(); r_exp[-1]['N_bkg_exp_B0_errLo'] = N_Bkg.getAsymErrorLo()


c_lin.setConstant(False)
res =  epdf_bkg_lin_600_bs.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant()
r_lin.append({}); r_lin[-1]['N_bkg_lin_Bs'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_Bs_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_Bs_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_Bs_errLo'] = N_Bkg_lin.getAsymErrorLo(); r_lin[-1]['c'] = c_lin.getVal(); r_lin[-1]['c_err'] = c_lin.getError(); r_lin[-1]['c_errHi'] = c_lin.getAsymErrorHi(); r_lin[-1]['c_errLo'] = c_lin.getAsymErrorLo()

res =  epdf_bkg_lin_600_b0.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant(False)
r_lin[-1]['N_bkg_lin_B0'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_B0_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_B0_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_B0_errLo'] = N_Bkg_lin.getAsymErrorLo()


indx_modSB.setConstant(False)
res =  epdf_bkg_600_bs_modSB.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant()
r_495.append({'SB':'lsb49005000,usb' , 'Operator':discriminant, 'Bin':3, 'N_bkg_exp_Bs':N_Bkg_modSB.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_modSB.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_modSB.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_modSB.getAsymErrorLo(), 'k': indx_modSB.getVal(), 'k_err':indx_modSB.getError(), 'k_errHi':indx_modSB.getAsymErrorHi(), 'k_errLo':indx_modSB.getAsymErrorLo()})

res =  epdf_bkg_600_b0_modSB.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant(False)
r_495[-1]['N_bkg_exp_B0'] = N_Bkg_modSB.getVal(); r_495[-1]['N_bkg_exp_B0_err'] = N_Bkg_modSB.getError(); r_495[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_modSB.getAsymErrorHi(); r_495[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_modSB.getAsymErrorLo()


indx_right.setConstant(False)
res =  epdf_bkg_600_bs_rightSB.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant()
r_right.append({'SB':'usb' , 'Operator':discriminant, 'Bin':2, 'N_bkg_exp_Bs':N_Bkg_right.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_right.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_right.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_right.getAsymErrorLo(), 'k': indx_right.getVal(), 'k_err':indx_right.getError(), 'k_errHi':indx_right.getAsymErrorHi(), 'k_errLo':indx_right.getAsymErrorLo()})

res =  epdf_bkg_600_b0_rightSB.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant(False)
r_right[-1]['N_bkg_exp_B0'] = N_Bkg_right.getVal(); r_right[-1]['N_bkg_exp_B0_err'] = N_Bkg_right.getError(); r_right[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_right.getAsymErrorHi(); r_right[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_right.getAsymErrorLo()



t= t3
bins = 30
h = TH1F("Bin1","Bin1",bins,bsmass_pdg-600, 6000)
h, g, ls, l0 = get_graph( h, t, lines= [bsmass-60, bsmass+60, b0mass-60, b0mass+60] )

can = TCanvas('_', '_', 800,600)
g.Draw('AP')
ls[0].Draw()
ls[1].Draw()
l0[0].Draw()
l0[1].Draw()

can = plot_exp(can, h, r_495[-1]['k'], t.GetEntries(lsb_cut_4900_5000)+t.GetEntries(usb_cut), 4900, 5000, bsmass_pdg+60, 6000, 3)
if plot_all:
    can = plot_exp(can, h, r_exp[-1]['k'], t.GetEntries(lsb_cut)+t.GetEntries(usb_cut), bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 4)
    can = plot_exp(can, h, r_right[-1]['k'], t.GetEntries(usb_cut), 0, 0, bsmass_pdg+60, 6000, 6)
    #can = plot_root(can, h, bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 2)

lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()

can.SaveAs(discriminant+'_Root_3_600_'+datestamp+'.png')
can.SaveAs(discriminant+'_Root_3_600_'+datestamp+'.pdf')
can.SaveAs(discriminant+'_Root_3_600_'+datestamp+'.root')

h.Delete()


frame3_600 = mass_600.frame()
data3.plotOn(frame3_600,RooFit.Binning(30))
epdf_bkg_600_bs.plotOn(frame3_600, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_600_bs.plotOn(frame3_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb')
                ,RooFit.LineStyle(kDashed))

epdf_bkg_lin_600_bs.plotOn(frame3_600, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'),RooFit.LineColor(2))
epdf_bkg_lin_600_bs.plotOn(frame3_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(2))

epdf_bkg_600_bs_modSB.plotOn(frame3_600, RooFit.Range('lsb49005000,usb'),RooFit.NormRange('lsb49005000,usb'),RooFit.LineColor(3))

epdf_bkg_600_bs_modSB.plotOn(frame3_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb49005000,usb'),RooFit.LineStyle(kDashed),RooFit.LineColor(3))

epdf_bkg_600_bs_rightSB.plotOn(frame3_600, RooFit.Range('usb'),RooFit.NormRange('usb'),RooFit.LineColor(6))
epdf_bkg_600_bs_rightSB.plotOn(frame3_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(6))

#epdf_bkg_600.paramOn(frame3_600, RooFit.Layout(0.573, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#, ShowConstant(True)) 
frame3_600.Draw()
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
save_this(frame3_600, discriminant+'_3_600_'+datestamp, lhcb)

#import code; code.interact(local=locals())

frame3 = mass.frame()
data3.plotOn(frame3, RooFit.Binning(40))#, RooFit.CutRange('lsb,usb'))
frame3.Draw()
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
save_this(frame3, discriminant+'_3_1200_'+datestamp, lhcb)


# fourth bin


## res =  epdf_bkg.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
## print 'N_bkg ', N_Bkg.getVal()

## frame4 = mass.frame()
## data4.plotOn(frame4, RooFit.CutRange('lsb_BIG,usb_BIG'), RooFit.Binning(20))
## epdf_bkg.plotOn(frame4, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
## epdf_bkg.plotOn(frame4, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'),RooFit.LineStyle(kDashed))
## epdf_bkg.paramOn(frame4, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
## frame4.Draw()
## lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
## lhcb.Draw()

## save_this(frame4, discriminant+'_4_1200')


# fourth 600MeV

indx.setConstant(False)
res =  epdf_bkg_600_bs.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant()
r_exp.append({'Bin':4, 'N_bkg_exp_Bs':N_Bkg.getVal(), 'N_bkg_exp_Bs_err': N_Bkg.getError(),'N_bkg_exp_Bs_errHi':N_Bkg.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg.getAsymErrorLo(), 'k': indx.getVal(), 'k_err':indx.getError(), 'k_errHi':indx.getAsymErrorHi(), 'k_errLo':indx.getAsymErrorLo()})

res =  epdf_bkg_600_b0.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
indx.setConstant(False)
r_exp[-1]['N_bkg_exp_B0'] = N_Bkg.getVal(); r_exp[-1]['N_bkg_exp_B0_err'] = N_Bkg.getError(); r_exp[-1]['N_bkg_exp_B0_errHi'] = N_Bkg.getAsymErrorHi(); r_exp[-1]['N_bkg_exp_B0_errLo'] = N_Bkg.getAsymErrorLo()

indx_right.setVal(indx.getVal())
indx_modSB.setVal(indx.getVal())
c_lin.setConstant(False)
#res =  polbkg_600.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
res =  epdf_bkg_lin_600_bs.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant()
r_lin.append({}); r_lin[-1]['N_bkg_lin_Bs'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_Bs_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_Bs_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_Bs_errLo'] = N_Bkg_lin.getAsymErrorLo(); r_lin[-1]['c'] = c_lin.getVal(); r_lin[-1]['c_err'] = c_lin.getError(); r_lin[-1]['c_errHi'] = c_lin.getAsymErrorHi(); r_lin[-1]['c_errLo'] = c_lin.getAsymErrorLo()

res =  epdf_bkg_lin_600_b0.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
c_lin.setConstant(False)
r_lin[-1]['N_bkg_lin_B0'] = N_Bkg_lin.getVal(); r_lin[-1]['N_bkg_lin_B0_err'] = N_Bkg_lin.getError(); r_lin[-1]['N_bkg_lin_B0_errHi'] = N_Bkg_lin.getAsymErrorHi(); r_lin[-1]['N_bkg_lin_B0_errLo'] = N_Bkg_lin.getAsymErrorLo()


indx_modSB.setConstant(False)
res =  epdf_bkg_600_bs_modSB.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant()
r_495.append({'SB':'lsb49005000,usb' , 'Operator':discriminant, 'Bin':4, 'N_bkg_exp_Bs':N_Bkg_modSB.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_modSB.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_modSB.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_modSB.getAsymErrorLo(), 'k': indx_modSB.getVal(), 'k_err':indx_modSB.getError(), 'k_errHi':indx_modSB.getAsymErrorHi(), 'k_errLo':indx_modSB.getAsymErrorLo()})

res =  epdf_bkg_600_b0_modSB.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb49005000,usb'))
indx_modSB.setConstant(False)
r_495[-1]['N_bkg_exp_B0'] = N_Bkg_modSB.getVal(); r_495[-1]['N_bkg_exp_B0_err'] = N_Bkg_modSB.getError(); r_495[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_modSB.getAsymErrorHi(); r_495[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_modSB.getAsymErrorLo()


indx_right.setConstant(False)
res =  epdf_bkg_600_bs_rightSB.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant()
r_right.append({'SB':'usb' , 'Operator':discriminant, 'Bin':4, 'N_bkg_exp_Bs':N_Bkg_right.getVal(), 'N_bkg_exp_Bs_err': N_Bkg_right.getError(),'N_bkg_exp_Bs_errHi':N_Bkg_right.getAsymErrorHi(),'N_bkg_exp_Bs_errLo':N_Bkg_right.getAsymErrorLo(), 'k': indx_right.getVal(), 'k_err':indx_right.getError(), 'k_errHi':indx_right.getAsymErrorHi(), 'k_errLo':indx_right.getAsymErrorLo()})

res =  epdf_bkg_600_b0_rightSB.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('usb'))
indx_right.setConstant(False)
r_right[-1]['N_bkg_exp_B0'] = N_Bkg_right.getVal(); r_right[-1]['N_bkg_exp_B0_err'] = N_Bkg_right.getError(); r_right[-1]['N_bkg_exp_B0_errHi'] = N_Bkg_right.getAsymErrorHi(); r_right[-1]['N_bkg_exp_B0_errLo'] = N_Bkg_right.getAsymErrorLo()



t= t4
bins = 30
h = TH1F("Bin1","Bin1",bins,bsmass_pdg-600, 6000)
h, g, ls, l0 = get_graph( h, t, lines= [bsmass-60, bsmass+60, b0mass-60, b0mass+60] )

can = TCanvas('_', '_', 800,600)
g.Draw('AP')
ls[0].Draw()
ls[1].Draw()
l0[0].Draw()
l0[1].Draw()

can = plot_exp(can, h, r_495[-1]['k'],   t.GetEntries(lsb_cut_4900_5000)+t.GetEntries(usb_cut), 4900, 5000, bsmass_pdg+60, 6000, 3)
if plot_all:
    can = plot_exp(can, h, r_exp[-1]['k'],   t.GetEntries(lsb_cut)+t.GetEntries(usb_cut)          , bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 4)
    can = plot_exp(can, h, r_right[-1]['k'], t.GetEntries(usb_cut)                                , 0, 0, bsmass_pdg+60, 6000, 6)
    #can = plot_root(can, h, bsmass_pdg-600, b0mass_pdg-60, bsmass_pdg+60, 6000, 2)
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
can.SaveAs(discriminant+'_Root_4_600_'+datestamp+'.png')
can.SaveAs(discriminant+'_Root_4_600_'+datestamp+'.pdf')
can.SaveAs(discriminant+'_Root_4_600_'+datestamp+'.root')

h.Delete()


frame4_600 = mass_600.frame()
data4.plotOn(frame4_600, RooFit.Binning(30))#, RooFit.CutRange('lsb,usb'))


#polbkg_600.plotOn(frame4_600)

epdf_bkg_600_bs.plotOn(frame4_600, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_600_bs.plotOn(frame4_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb')
                ,RooFit.LineStyle(kDashed))
epdf_bkg_lin_600_bs.plotOn(frame4_600, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'),RooFit.LineColor(2))
epdf_bkg_lin_600_bs.plotOn(frame4_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(2))
epdf_bkg_600_bs_modSB.plotOn(frame4_600, RooFit.Range('lsb49005000,usb'),RooFit.NormRange('lsb49005000,usb'),RooFit.LineColor(3))
epdf_bkg_600_bs_modSB.plotOn(frame4_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb49005000,usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(3))
epdf_bkg_600_bs_rightSB.plotOn(frame4_600, RooFit.Range('usb'),RooFit.NormRange('usb'),RooFit.LineColor(6))
epdf_bkg_600_bs_rightSB.plotOn(frame4_600, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('usb')
                ,RooFit.LineStyle(kDashed),RooFit.LineColor(6))
#epdf_bkg_600.paramOn(frame4_600, RooFit.Layout(0.573, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#, ShowConstant(True)) 
frame4_600.Draw()
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
save_this(frame4_600, discriminant+'_4_600_'+datestamp, lhcb)


frame4 = mass.frame()
data4.plotOn(frame4, RooFit.Binning(40))#, RooFit.CutRange('lsb,usb'))
frame4.Draw()
lhcb = do_lhcb_label(0.655172, 0.65161, 0.869253, 0.741, prelim=True)#0.765805, 0.813559, 0.979885, 0.898305 )
lhcb.Draw()
save_this(frame4, discriminant+'_4_1200_'+datestamp, lhcb)


#print results

table = ''
table += '\\begin{tabular}{|c|ccc|ccc|ccc|ccc|}\n'
table += '\\hline\n'
table += '&  \\multicolumn{3}{c|}{exponential}  & \\multicolumn{3}{c|}{linear} & \\multicolumn{3}{c|}{expo, 4.9-5, right} & \\multicolumn{3}{c|}{expo, right}  \\\\\n'
table += 'Bin & $k$ & $B_s$& $B_0$  & $c$  & $B_s$& $B_0$ & $k$ & $B_s$& $B_0$ & $k$ & $B_s$& $B_0$ \\\\\n'
table += '\hline\n'

for i in range(4):
    table+='%(bin).1i & '%{'bin':r_exp[i]['Bin']}
    table+='$%(k).7f^{+%(k_u).7f}_{%(k_d).7f}$ & $%(bs_e).4f^{+%(bs_e_u).4f}_{%(bs_e_d).4f}$ & $%(b0_e).4f^{+%(b0_e_u).4f}_{%(b0_e_d).4f}$ &'\
            %{'k':r_exp[i]['k'], 'k_u':r_exp[i]['k_errHi'], 'k_d':r_exp[i]['k_errLo']
              ,'bs_e':r_exp[i]['N_bkg_exp_Bs'], 'bs_e_u':r_exp[i]['N_bkg_exp_Bs_errHi'], 'bs_e_d':r_exp[i]['N_bkg_exp_Bs_errLo']
              ,'b0_e':r_exp[i]['N_bkg_exp_B0'], 'b0_e_u':r_exp[i]['N_bkg_exp_B0_errHi'], 'b0_e_d':r_exp[i]['N_bkg_exp_B0_errLo']}
    table+='$%(c).7f^{+%(c_u).7f}_{%(c_d).7f}$ & $%(bs_l).4f^{+%(bs_l_u).4f}_{%(bs_l_d).4f}$ & $%(b0_l).4f^{+%(b0_l_u).4f}_{%(b0_l_d).4f}$ &' \
            %{'c':r_lin[i]['c'], 'c_u':r_lin[i]['c_errHi'], 'c_d':r_lin[i]['c_errLo']
              ,'bs_l':r_lin[i]['N_bkg_lin_Bs'], 'bs_l_u':r_lin[i]['N_bkg_lin_Bs_errHi'], 'bs_l_d':r_lin[i]['N_bkg_lin_Bs_errLo']
              ,'b0_l':r_lin[i]['N_bkg_lin_B0'], 'b0_l_u':r_lin[i]['N_bkg_lin_B0_errHi'], 'b0_l_d':r_lin[i]['N_bkg_lin_B0_errLo']}
    table+='$%(k).7f^{+%(k_u).7f}_{%(k_d).7f}$ & $%(bs_e).4f^{+%(bs_e_u).4f}_{%(bs_e_d).4f}$ & $%(b0_e).4f^{+%(b0_e_u).4f}_{%(b0_e_d).4f}$ &'\
            %{'k':r_495[i]['k'], 'k_u':r_495[i]['k_errHi'], 'k_d':r_495[i]['k_errLo']
              ,'bs_e':r_495[i]['N_bkg_exp_Bs'], 'bs_e_u':r_495[i]['N_bkg_exp_Bs_errHi'], 'bs_e_d':r_495[i]['N_bkg_exp_Bs_errLo']
              ,'b0_e':r_495[i]['N_bkg_exp_B0'], 'b0_e_u':r_495[i]['N_bkg_exp_B0_errHi'], 'b0_e_d':r_495[i]['N_bkg_exp_B0_errLo']}
    table+='$%(k).7f^{+%(k_u).7f}_{%(k_d).7f}$ & $%(bs_e).4f^{+%(bs_e_u).4f}_{%(bs_e_d).4f}$ & $%(b0_e).4f^{+%(b0_e_u).4f}_{%(b0_e_d).4f}$ '\
            %{'k':r_right[i]['k'], 'k_u':r_right[i]['k_errHi'], 'k_d':r_right[i]['k_errLo']
              ,'bs_e':r_right[i]['N_bkg_exp_Bs'], 'bs_e_u':r_right[i]['N_bkg_exp_Bs_errHi'], 'bs_e_d':r_right[i]['N_bkg_exp_Bs_errLo']
              ,'b0_e':r_right[i]['N_bkg_exp_B0'], 'b0_e_u':r_right[i]['N_bkg_exp_B0_errHi'], 'b0_e_d':r_right[i]['N_bkg_exp_B0_errLo']}
    table+= '  \\\\\n'

table += '\\hline\n'
table += '\\end{tabular}\n'

print table



table = ''
table += '\\begin{tabular}{|lr|c|c|c|c|}\n'
table += '\\hline\n'
table += '& &  $[0, 0.25]$   & $[0.25, 0.5]$ & $[0.5, 0.75]$ & $[0.75, 1]$ \\\\\n'
table += '\\hline\n'

table+='exponential & '
table+='index & $(%(k1).2f^{+%(k1_u).2f}_{%(k1_d).2f})\\times 10^{-4}$ & $(%(k2).2f^{+%(k2_u).2f}_{%(k2_d).2f})\\times 10^{-4}$ & $(%(k3).2f^{+%(k3_u).2f}_{%(k3_d).2f})\\times 10^{-4}$ & $(%(k4).2f^{+%(k4_u).2f}_{%(k4_d).2f})\\times 10^{-4}$ \\\\\n'\
            %{ 'k1':r_495[0]['k']*1e4, 'k1_u':r_495[0]['k_errHi']*1e4, 'k1_d':r_495[0]['k_errLo']*1e4
              ,'k2':r_495[1]['k']*1e4, 'k2_u':r_495[1]['k_errHi']*1e4, 'k2_d':r_495[1]['k_errLo']*1e4
              ,'k3':r_495[2]['k']*1e4, 'k3_u':r_495[2]['k_errHi']*1e4, 'k3_d':r_495[2]['k_errLo']*1e4
              ,'k4':r_495[3]['k']*1e4, 'k4_u':r_495[3]['k_errHi']*1e4, 'k4_d':r_495[3]['k_errLo']*1e4}
table+='\cline{2-6}\n'
table+=' $[4.9, 5]$ and right& '
table+='yield &  $%(bs1).4f^{+%(bs1_u).4f}_{%(bs1_d).4f}$ & $%(bs2).4f^{+%(bs2_u).4f}_{%(bs2_d).4f}$ & $%(bs3).4f^{+%(bs3_u).4f}_{%(bs3_d).4f}$ &$%(bs4).4f^{+%(bs4_u).4f}_{%(bs4_d).4f}$ \\\\\n'\
%{ 'bs1':r_495[0]['N_bkg_exp_Bs'], 'bs1_u':r_495[0]['N_bkg_exp_Bs_errHi'], 'bs1_d':r_495[0]['N_bkg_exp_Bs_errLo']
  ,'bs2':r_495[1]['N_bkg_exp_Bs'], 'bs2_u':r_495[1]['N_bkg_exp_Bs_errHi'], 'bs2_d':r_495[1]['N_bkg_exp_Bs_errLo']
  ,'bs3':r_495[2]['N_bkg_exp_Bs'], 'bs3_u':r_495[2]['N_bkg_exp_Bs_errHi'], 'bs3_d':r_495[2]['N_bkg_exp_Bs_errLo']
  ,'bs4':r_495[3]['N_bkg_exp_Bs'], 'bs4_u':r_495[3]['N_bkg_exp_Bs_errHi'], 'bs4_d':r_495[3]['N_bkg_exp_Bs_errLo']}
table += '\\hline\n'

table+='exponential & '
table+='index & $(%(k1).2f^{+%(k1_u).2f}_{%(k1_d).2f})\\times 10^{-4}$ & $(%(k2).2f^{+%(k2_u).2f}_{%(k2_d).2f})\\times 10^{-4}$ & $(%(k3).2f^{+%(k3_u).2f}_{%(k3_d).2f})\\times 10^{-4}$ & $(%(k4).2f^{+%(k4_u).2f}_{%(k4_d).2f})\\times 10^{-4}$ \\\\\n'\
            %{ 'k1':r_exp[0]['k']*1e4, 'k1_u':r_exp[0]['k_errHi']*1e4, 'k1_d':r_exp[0]['k_errLo']*1e4
              ,'k2':r_exp[1]['k']*1e4, 'k2_u':r_exp[1]['k_errHi']*1e4, 'k2_d':r_exp[1]['k_errLo']*1e4
              ,'k3':r_exp[2]['k']*1e4, 'k3_u':r_exp[2]['k_errHi']*1e4, 'k3_d':r_exp[2]['k_errLo']*1e4
              ,'k4':r_exp[3]['k']*1e4, 'k4_u':r_exp[3]['k_errHi']*1e4, 'k4_d':r_exp[3]['k_errLo']*1e4}
table+='\cline{2-6}\n'
table+='both sidebands & '
table+='yield &  $%(bs1).4f^{+%(bs1_u).4f}_{%(bs1_d).4f}$ & $%(bs2).4f^{+%(bs2_u).4f}_{%(bs2_d).4f}$ & $%(bs3).4f^{+%(bs3_u).4f}_{%(bs3_d).4f}$ &$%(bs4).4f^{+%(bs4_u).4f}_{%(bs4_d).4f}$ \\\\\n'\
%{ 'bs1':r_exp[0]['N_bkg_exp_Bs'], 'bs1_u':r_exp[0]['N_bkg_exp_Bs_errHi'], 'bs1_d':r_exp[0]['N_bkg_exp_Bs_errLo']
  ,'bs2':r_exp[1]['N_bkg_exp_Bs'], 'bs2_u':r_exp[1]['N_bkg_exp_Bs_errHi'], 'bs2_d':r_exp[1]['N_bkg_exp_Bs_errLo']
  ,'bs3':r_exp[2]['N_bkg_exp_Bs'], 'bs3_u':r_exp[2]['N_bkg_exp_Bs_errHi'], 'bs3_d':r_exp[2]['N_bkg_exp_Bs_errLo']
  ,'bs4':r_exp[3]['N_bkg_exp_Bs'], 'bs4_u':r_exp[3]['N_bkg_exp_Bs_errHi'], 'bs4_d':r_exp[3]['N_bkg_exp_Bs_errLo']}
table += '\\hline\n'

table+='exponential & '
table+='index & $(%(k1).2f^{+%(k1_u).2f}_{%(k1_d).2f})\\times 10^{-4}$ & $(%(k2).2f^{+%(k2_u).2f}_{%(k2_d).2f})\\times 10^{-4}$ & $(%(k3).2f^{+%(k3_u).2f}_{%(k3_d).2f})\\times 10^{-4}$ & $(%(k4).2f^{+%(k4_u).2f}_{%(k4_d).2f})\\times 10^{-4}$ \\\\\n'\
            %{ 'k1':r_right[0]['k']*1e4, 'k1_u':r_right[0]['k_errHi']*1e4, 'k1_d':r_right[0]['k_errLo']*1e4
              ,'k2':r_right[1]['k']*1e4, 'k2_u':r_right[1]['k_errHi']*1e4, 'k2_d':r_right[1]['k_errLo']*1e4
              ,'k3':r_right[2]['k']*1e4, 'k3_u':r_right[2]['k_errHi']*1e4, 'k3_d':r_right[2]['k_errLo']*1e4
              ,'k4':r_right[3]['k']*1e4, 'k4_u':r_right[3]['k_errHi']*1e4, 'k4_d':r_right[3]['k_errLo']*1e4}
table+='\cline{2-6}\n'
table+=' only right& '
table+='yield &  $%(bs1).4f^{+%(bs1_u).4f}_{%(bs1_d).4f}$ & $%(bs2).4f^{+%(bs2_u).4f}_{%(bs2_d).4f}$ & $%(bs3).4f^{+%(bs3_u).4f}_{%(bs3_d).4f}$ &$%(bs4).4f^{+%(bs4_u).4f}_{%(bs4_d).4f}$ \\\\\n'\
%{ 'bs1':r_right[0]['N_bkg_exp_Bs'], 'bs1_u':r_right[0]['N_bkg_exp_Bs_errHi'], 'bs1_d':r_right[0]['N_bkg_exp_Bs_errLo']
  ,'bs2':r_right[1]['N_bkg_exp_Bs'], 'bs2_u':r_right[1]['N_bkg_exp_Bs_errHi'], 'bs2_d':r_right[1]['N_bkg_exp_Bs_errLo']
  ,'bs3':r_right[2]['N_bkg_exp_Bs'], 'bs3_u':r_right[2]['N_bkg_exp_Bs_errHi'], 'bs3_d':r_right[2]['N_bkg_exp_Bs_errLo']
  ,'bs4':r_right[3]['N_bkg_exp_Bs'], 'bs4_u':r_right[3]['N_bkg_exp_Bs_errHi'], 'bs4_d':r_right[3]['N_bkg_exp_Bs_errLo']}
table += '\\hline\n'

table+='linear & '
table+='index & $(%(k1).4f^{+%(k1_u).4f}_{%(k1_d).4f})\\times 10^{-4}$ & $(%(k2).4f^{+%(k2_u).4f}_{%(k2_d).4f})\\times 10^{-4}$ & $(%(k3).4f^{+%(k3_u).4f}_{%(k3_d).4f})\\times 10^{-4}$ & $(%(k4).4f^{+%(k4_u).4f}_{%(k4_d).4f})\\times 10^{-4}$ \\\\\n'\
            %{ 'k1':r_lin[0]['c']*1e4, 'k1_u':r_lin[0]['c_errHi']*1e4, 'k1_d':r_lin[0]['c_errLo']*1e4
              ,'k2':r_lin[1]['c']*1e4, 'k2_u':r_lin[1]['c_errHi']*1e4, 'k2_d':r_lin[1]['c_errLo']*1e4
              ,'k3':r_lin[2]['c']*1e4, 'k3_u':r_lin[2]['c_errHi']*1e4, 'k3_d':r_lin[2]['c_errLo']*1e4
              ,'k4':r_lin[3]['c']*1e4, 'k4_u':r_lin[3]['c_errHi']*1e4, 'k4_d':r_lin[3]['c_errLo']*1e4}
table+='\cline{2-6}\n'
table+=' both sidebands& '
table+='yield &  $%(bs1).4f^{+%(bs1_u).4f}_{%(bs1_d).4f}$ & $%(bs2).4f^{+%(bs2_u).4f}_{%(bs2_d).4f}$ & $%(bs3).4f^{+%(bs3_u).4f}_{%(bs3_d).4f}$ &$%(bs4).4f^{+%(bs4_u).4f}_{%(bs4_d).4f}$ \\\\\n'\
%{ 'bs1':r_lin[0]['N_bkg_lin_Bs'], 'bs1_u':r_lin[0]['N_bkg_lin_Bs_errHi'], 'bs1_d':r_lin[0]['N_bkg_lin_Bs_errLo']
  ,'bs2':r_lin[1]['N_bkg_lin_Bs'], 'bs2_u':r_lin[1]['N_bkg_lin_Bs_errHi'], 'bs2_d':r_lin[1]['N_bkg_lin_Bs_errLo']
  ,'bs3':r_lin[2]['N_bkg_lin_Bs'], 'bs3_u':r_lin[2]['N_bkg_lin_Bs_errHi'], 'bs3_d':r_lin[2]['N_bkg_lin_Bs_errLo']
  ,'bs4':r_lin[3]['N_bkg_lin_Bs'], 'bs4_u':r_lin[3]['N_bkg_lin_Bs_errHi'], 'bs4_d':r_lin[3]['N_bkg_lin_Bs_errLo']}
table += '\\hline\n'
table += '\\end{tabular}\n'

print table





# N_left and N_right

print '         N_left       N_right       N_side_tot'
print 'bin1_4900_5000     ', t1.GetEntries(lsb_cut_4900_5000),'       ',t1.GetEntries(usb_cut),'       ',t1.GetEntries(lsb_cut_4900_5000)+t1.GetEntries(usb_cut)
print 'bin2_4900_5000     ', t2.GetEntries(lsb_cut_4900_5000),'       ',t2.GetEntries(usb_cut),'       ',t2.GetEntries(lsb_cut_4900_5000)+t2.GetEntries(usb_cut)
print 'bin3_4900_5000     ', t3.GetEntries(lsb_cut_4900_5000),'       ',t3.GetEntries(usb_cut),'       ',t3.GetEntries(lsb_cut_4900_5000)+t3.GetEntries(usb_cut)
print 'bin4_4900_5000     ', t4.GetEntries(lsb_cut_4900_5000),'       ',t4.GetEntries(usb_cut),'       ',t4.GetEntries(lsb_cut_4900_5000)+t4.GetEntries(usb_cut)

print 'bin1     ', t1.GetEntries(lsb_cut),'       ',t1.GetEntries(usb_cut),'       ',t1.GetEntries(lsb_cut)+t1.GetEntries(usb_cut)
print 'bin2     ', t2.GetEntries(lsb_cut),'       ',t2.GetEntries(usb_cut),'       ',t2.GetEntries(lsb_cut)+t2.GetEntries(usb_cut)
print 'bin3     ', t3.GetEntries(lsb_cut),'       ',t3.GetEntries(usb_cut),'       ',t3.GetEntries(lsb_cut)+t3.GetEntries(usb_cut)
print 'bin4     ', t4.GetEntries(lsb_cut),'       ',t4.GetEntries(usb_cut),'       ',t4.GetEntries(lsb_cut)+t4.GetEntries(usb_cut)

print 'bin1_BIG ', t1.GetEntries(lsb_BIG_cut),'   ',t1.GetEntries(usb_BIG_cut),'   ',t1.GetEntries(lsb_BIG_cut)+t1.GetEntries(usb_BIG_cut)
print 'bin2_BIG ', t2.GetEntries(lsb_BIG_cut),'   ',t2.GetEntries(usb_BIG_cut),'   ',t2.GetEntries(lsb_BIG_cut)+t2.GetEntries(usb_BIG_cut)
print 'bin3_BIG ', t3.GetEntries(lsb_BIG_cut),'   ',t3.GetEntries(usb_BIG_cut),'   ',t3.GetEntries(lsb_BIG_cut)+t3.GetEntries(usb_BIG_cut)
print 'bin4_BIG ', t4.GetEntries(lsb_BIG_cut),'   ',t4.GetEntries(usb_BIG_cut),'   ',t4.GetEntries(lsb_BIG_cut)+t4.GetEntries(usb_BIG_cut)



import code; code.interact(local=locals())





## delta_mass = [400, 200]
## color = 4
## c, N = [],[]
## #for delta in delta_mass:
## delta = 200

## color += 1
## N_Bkg_lin.setVal(5.)
## mass.setRange("lsb_lin_"+str(delta), blind_region_low-delta, blind_region_low )
## mass.setRange("usb_lin_"+str(delta), blind_region_high, blind_region_high+delta )

## res =  polbkg.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)))

## integral = polbkg.createIntegral( RooArgSet(mass), RooFit.Range('blinded'))
## print 'Integral ', integral.getVal()/ float(blind_region_high -  blind_region_low)
## integral.Delete()
  
## epdf_tmp = epdf_bkg_lin_600.clone('new_mass_'+str(delta))
## res =  epdf_tmp.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(False), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)))
## print 'XX for delta mass', delta
## print 'N_bkg ', N_Bkg_lin.getVal() , '+', N_Bkg_lin.getAsymErrorHi(), '-', N_Bkg_lin.getAsymErrorLo()
## print 'c  ', c_lin.getVal(), '+-', c_lin.getError()
## c.append(c_lin.getVal())
## N.append(N_Bkg_lin.getVal())
## epdf_tmp.plotOn(frame4_600, RooFit.Range('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)),RooFit.NormRange('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)),RooFit.LineColor(color))
## epdf_tmp.plotOn(frame4_600, RooFit.Range(blind_region_low-delta, blind_region_high+delta), RooFit.NormRange('lsb_lin_'+str(delta)+',usb_lin_'+str(delta)),RooFit.LineStyle(kDashed),RooFit.LineColor(color))

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
N_Bkg  = RooRealVar('N_{bkg}', 'Number of Bkg',  0.5*t.GetEntries() , 0, t.GetEntries())

expbkg1 = RooExponential("expbkg1", " exp background pdf1", mass, indx1)
expbkg2 = RooExponential("expbkg2", " exp background pdf2", mass, indx2)


#RooAddPdf sum("sum","g1+g2+a",RooArgList(gauss1,gauss2,argus),RooArgList(g1frac,g2frac)) ;
exp_sum = RooAddPdf('exp_sum', 'exp_sum', RooArgList(expbkg1,expbkg2), RooArgList(N_1,N_2))
epdf_bkg_2exp = RooExtendPdf( 'epdf_bkg_2exp', 'epdf_bkg_2exp', exp_sum, N_Bkg, 'bswin' )


indx1.setVal(-5.e-03)
indx2.setVal(-7.e-09)
res =  exp_sum.fitTo( data1, RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True), RooFit.Verbose(False), RooFit.Range('lsb_BIG,usb_BIG'))
res_2exp =  epdf_bkg_2exp.fitTo( data1, RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True), RooFit.Verbose(False), RooFit.Range('lsb_BIG,usb_BIG'))
print 'N_bkg ', N_Bkg.getVal()

frame1 = mass.frame()
data1.plotOn(frame1, RooFit.CutRange('lsb_BIG,usb_BIG'), RooFit.Binning(40))
exp_sum.plotOn(frame1, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
#exp_sum.plotOn(frame1, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'), RooFit.LineStyle(kDashed))
#epdf_bkg_2exp.plotOn(frame1, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'), RooFit.LineStyle(kDashed))
epdf_bkg.paramOn(frame1, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame1.Draw()



indx1.setVal(-5.e-03)
indx2.setVal(-7.e-09)
res =  exp_sum.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
print 'N_bkg ', N_Bkg.getVal()

frame2 = mass.frame()
data2.plotOn(frame2, RooFit.CutRange('lsb_BIG,usb_BIG'), RooFit.Binning(20))
exp_sum.plotOn(frame2, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
exp_sum.plotOn(frame2, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'),RooFit.LineStyle(kDashed))
epdf_bkg.paramOn(frame2, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame2.Draw()



indx1.setVal(-5.e-03)
indx2.setVal(-7.e-09)
res =  exp_sum.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
print 'N_bkg ', N_Bkg.getVal()

frame3 = mass.frame()
data3.plotOn(frame3, RooFit.CutRange('lsb_BIG,usb_BIG'), RooFit.Binning(20))
exp_sum.plotOn(frame3, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
exp_sum.plotOn(frame3, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'),RooFit.LineStyle(kDashed))
epdf_bkg.paramOn(frame3, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame3.Draw()


indx1.setVal(-5.e-03)
indx2.setVal(-7.e-09)
res =  exp_sum.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
print 'N_bkg ', N_Bkg.getVal()

frame4 = mass.frame()
data4.plotOn(frame4, RooFit.CutRange('lsb_BIG,usb_BIG'), RooFit.Binning(20))
exp_sum.plotOn(frame4, RooFit.Range('lsb_BIG,usb_BIG'),RooFit.NormRange('lsb_BIG,usb_BIG'))
exp_sum.plotOn(frame4, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb_BIG,usb_BIG'),RooFit.LineStyle(kDashed))
epdf_bkg.paramOn(frame4, RooFit.Layout(0.573, 0.909483, 0.917373))#(0.652299, 0.909483, 0.917373))#, RooFit.Format("N", RooFit.AutoPrecision(1)))#) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame3.Draw()


#linear fit for background
DeltaM = 100
def get_crap(DeltaM):
    dm_lo_cut = 'Bmass>'+str(5215.1-DeltaM)+' && Bmass<5215.1'
    dm_hi_cut = 'Bmass>5423.1 && Bmass<'+str(5423.1+DeltaM)
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

res =  epdf_bkg_b0_600.fitTo(  data1,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
print 'N_bkg ', N_Bkg.getVal()

frame1 = mass.frame()
data1.plotOn(frame1, RooFit.CutRange('lsb,usb'), RooFit.Binning(30))
epdf_bkg_b0.plotOn(frame1, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_b0.plotOn(frame1, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed))
epdf_bkg_b0.paramOn(frame1) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame1.Draw()


res =  epdf_bkg_b0_600.fitTo(  data2,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb,usb'))
print 'N_bkg ', N_Bkg.getVal()

frame2 = mass.frame()
data2.plotOn(frame2, RooFit.CutRange('lsb,usb'), RooFit.Binning(30))
epdf_bkg_b0.plotOn(frame2, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_b0.plotOn(frame2, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed))
epdf_bkg_b0.paramOn(frame2) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame2.Draw()


res =  epdf_bkg_b0.fitTo(  data3,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
print 'N_bkg ', N_Bkg.getVal()

frame3 = mass.frame()
data3.plotOn(frame3, RooFit.CutRange('lsb,usb'), RooFit.Binning(10))
epdf_bkg_b0.plotOn(frame3, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_b0.plotOn(frame3, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed))
epdf_bkg_b0.paramOn(frame3) #Layout(Double_t xmin, Double_t xmax, Double_t ymax)
frame3.Draw()


res =  epdf_bkg_b0.fitTo(  data4,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range('lsb_BIG,usb_BIG'))
print 'N_bkg ', N_Bkg.getVal()

frame4 = mass.frame()
data4.plotOn(frame4, RooFit.CutRange('lsb,usb'), RooFit.Binning(10))
epdf_bkg_b0.plotOn(frame4, RooFit.Range('lsb,usb'),RooFit.NormRange('lsb,usb'))
epdf_bkg_b0.plotOn(frame4, RooFit.Range(bsmass-600, bsmass+600), RooFit.NormRange('lsb,usb'),RooFit.LineStyle(kDashed))
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
